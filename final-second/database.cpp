#include "database.h"

void Database::Print(std::ostream& stream) const {
    for (auto& [date, events] : vectorContainer) {
        for (const auto& event : events) {
            stream << date << ' ' << event << std::endl;
        }
    }
}
void Database::Add(const Date& date, const std::string& event) {
    auto& eventsFromSet = setContainer[date];
    if (eventsFromSet.find(event) == eventsFromSet.end()) {
        auto& eventsFromVector = vectorContainer[date];
        eventsFromSet.insert(event);
        eventsFromVector.push_back(event);
    }
}

std::string Database::Last(const Date& date) const {
    auto result = vectorContainer.upper_bound(date);
    if (result != vectorContainer.begin()) {
        result = std::prev(result);
        while (result != vectorContainer.begin() && result->second.size() == 0) {
            result = std::prev(result);
        }
        if (result->second.size() != 0) {
            std::stringstream output;
            output << result->first << " " << result->second.back();
            return output.str();
        }
    }
    return "No entries";
}


