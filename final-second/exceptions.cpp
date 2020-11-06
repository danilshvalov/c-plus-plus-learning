#include "exceptions.h"

void DateFormatException(const std::string& msg) {
    std::stringstream stream;
    stream << "Wrong date format: " << msg << std::endl;
    throw std::runtime_error(stream.str());
}
void MonthValueException(const std::string& msg) {
    std::stringstream stream;
    stream << "Month value is invalid: " << msg << std::endl;
    throw std::runtime_error(stream.str());
}
void DayValueException(const std::string& msg) {
    std::stringstream stream;
    stream << "Day value is invalid: " << msg << std::endl;
    throw std::runtime_error(stream.str());
}
void UnknownCommandException(const std::string& msg) {
    std::stringstream stream;
    stream << "Unknown command: " << msg << std::endl;
    throw std::runtime_error(stream.str());
}