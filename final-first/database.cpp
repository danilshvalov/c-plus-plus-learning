#include "database.h"

void Database::printAllEvents(std::ostream& stream) {
    for (auto& [date, events] : data) {
        std::sort(events.begin(), events.end());
        for (const auto& event : events) {
            stream << date << ' ' << event << std::endl;
        }
    }
}
void Database::addEvent(const Date& date, const std::string& event) {
    auto& events = data[date];
    if (!std::count(events.begin(), events.end(), event)) {
        events.push_back(event);
    }
}
bool Database::deleteEvent(const Date& date, const std::string& event) {
    if (data.count(date)) {
        auto& events = data[date];
        auto it = std::find(events.begin(), events.end(), event);
        if (it != events.end()) {
            events.erase(it);
            return true;
        }
    }
    return false;
}
int Database::deleteEvents(const Date& date) {
    int eventsCount = 0;
    if (data.count(date)) {
        auto& events = data[date];
        eventsCount = events.size();
        events.clear();
    }
    return eventsCount;
}
void Database::findEvents(const Date& date, std::ostream& stream) {
    if (data.count(date)) {
        auto& events = data[date];
        std::sort(events.begin(), events.end());
        for (size_t i = 0; i < events.size(); ++i) {
            stream << events[i] << std::endl;
        }
    }
}