#include "database.h"

void Database::Print(std::ostream& stream) const {
    for (auto& [date, events] : data) {
        for (const auto& event : events) {
            stream << date << ' ' << event << std::endl;
        }
    }
}
void Database::Add(const Date& date, const std::string& event) {
    auto& eventsForCheck = dataForSearch[date];
    if (eventsForCheck.find(event) == eventsForCheck.end()) {
        auto& events = data[date];
        eventsForCheck.insert(event);
        events.push_back(event);
    }
}

std::string Database::Last(const Date& date) const {
    auto result = data.upper_bound(date);
    if (result != data.begin()) {
        result = std::prev(result);
        while (result != data.begin() && result->second.size() == 0) {
            result = std::prev(result);
        }
        if (result->second.size() != 0) {
            std::stringstream output;
            output << result->first << " " << result->second.back();
            return output.str();
        }
    }


    // auto result = data.upper_bound(date);
    // if (result != data.begin()) {
    //     result = std::prev(result);
    //     while (result != data.begin() && result->second.size() == 0) {
    //         result = std::prev(result);
    //     }
    //     if (result->second.size() != 0) {
    //         std::stringstream output;
    //         output << result->first << " " << result->second.back();
    //         return output.str();
    //     }
    // }
    return "No entries";
}


