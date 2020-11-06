#include <map>
#include <vector>
#include <algorithm>

#include "date.h"

#ifndef __DATABASE_H__
#define __DATABASE_H__


class Database {
private:
    std::map<Date, std::vector<std::string>> data;
public:
    void Print(std::ostream& stream) const;
    void Add(const Date& date, const std::string& event);
    std::string Last(const Date& date) const;
    template <typename Predicate>
    int RemoveIf(const Predicate& predicate) {
        int counter = 0;
        for (auto& [date, events] : data) {
            auto it = std::remove_if(events.begin(), events.end(), [&, d = std::ref(date)](auto event) {
                return predicate(d, event);
            });
            counter += std::distance(it, events.end());
            events.erase(it, events.end());
        }
        return counter;
    }
    template <typename Predicate>
    std::vector<std::string> FindIf(const Predicate& predicate) const {
        std::vector<std::string> results;
        for (const auto& [date, events] : data) {
            for (const auto& event : events) {
                if (predicate(date, event)) {
                    std::stringstream output;
                    output << date << " " << event;
                    results.push_back(output.str());
                }
            }
        }
        return results;
    }

};

#endif // __DATABASE_H__