#include "database.h"

void Database::Print(std::ostream& stream) const {
    for (auto& [date, events] : data) {
        for (const auto& event : events) {
            stream << date << ' ' << event << std::endl;
        }
    }
}
void Database::Add(const Date& date, const std::string& event) {
    auto& events = data[date];
    if (std::find(events.begin(), events.end(), event) == events.end()) {
        events.push_back(event);
    }
}

std::string Database::Last(const Date& date) const {
    auto result = std::find_if(data.rbegin(), data.rend(), [&](auto info) {return (info.first < date || info.first == date) && info.second.size() != 0;});
    if (result != data.rend()) {
        std::stringstream output;
        output << result->first << " " << result->second.back();
        return output.str();
    }
    return "No entries";
}


