#include "database.h"

void Database::Print(std::ostream& stream) {
    for (auto& [date, events] : data) {
        for (const auto& event : events) {
            stream << date << ' ' << event << std::endl;
        }
    }
}
void Database::Add(const Date& date, const std::string& event) {
    auto& events = data[date];
    if (!std::count(events.begin(), events.end(), event)) {
        events.push_back(event);
    }
}

int Database::RemoveIf(std::function<bool(const Date& date, const std::string& event)> func) {
    int counter = 0;
    for (auto& [date, events] : data) {
        auto it = std::remove_if(events.begin(), events.end(), [&, d = std::ref(date)](auto event) {
            return func(d, event);
        });
        counter += std::distance(it, events.end());
        data[date] = { events.begin(), it };
    }
    return counter;
}

std::string Database::Last(const Date& date) {
    auto result = std::find_if(data.rbegin(), data.rend(), [&](auto info) {return (info.first < date || info.first == date) && info.second.size() != 0;});
    if (result != data.rend()) {
        std::stringstream output;
        output << result->first << " " << result->second.back();
        return output.str();
    }
    return "No entries";
}

std::vector<std::string> Database::FindIf(std::function<bool(const Date& date, const std::string& event)> func) {
    std::vector<std::string> results;
    for (const auto& [date, events] : data) {
        for (const auto& event : events) {
            if (func(date, event)) {
                std::stringstream output;
                output << date << " " << event;
                results.push_back(output.str());
            }
        }
    }
    return results;
}

