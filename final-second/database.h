#include <map>
#include <vector>
#include <algorithm>
#include <set>

#include "date.h"

#ifndef __DATABASE_H__
#define __DATABASE_H__


class Database {
private:
    std::map<Date, std::vector<std::string>> vectorContainer;
    std::map<Date, std::set<std::string>> setContainer;
public:
    void Print(std::ostream& stream) const;
    void Add(const Date& date, const std::string& event);
    std::string Last(const Date& date) const;
    template <typename Predicate>
    int RemoveIf(const Predicate& predicate) {
        int counter = 0;
        std::vector<Date> removingKeys;
        
        for (auto& [date, events] : vectorContainer) {
            auto it = std::remove_if(events.begin(), events.end(), [&, refDate = std::ref(date)](const auto& event) {return predicate(refDate, event);});
            counter += std::distance(it, events.end());
            if (it == events.begin()) {
                removingKeys.push_back(date);
            } else {
                events.erase(it, events.end());
                setContainer[date] = { events.begin(), events.end() };
            }
        }

        for (const auto& key : removingKeys) {
            vectorContainer.erase(key);
            setContainer.erase(key);
        }
        return counter;
    }
    template <typename Predicate>
    std::vector<std::string> FindIf(const Predicate& predicate) const {
        std::vector<std::string> results;
        for (const auto& [date, events] : vectorContainer) {
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