#include "exceptions.h"

void dateFormatException(const std::string& msg) {
    std::stringstream stream;
    stream << "Wrong date format: " << msg << std::endl;
    throw std::runtime_error(stream.str());
}
void monthValueException(const std::string& msg) {
    std::stringstream stream;
    stream << "Month value is invalid: " << msg << std::endl;
    throw std::runtime_error(stream.str());
}
void dayValueException(const std::string& msg) {
    std::stringstream stream;
    stream << "Day value is invalid: " << msg << std::endl;
    throw std::runtime_error(stream.str());
}
void unknownCommandException(const std::string& msg) {
    std::stringstream stream;
    stream << "Unknown command: " << msg << std::endl;
    throw std::runtime_error(stream.str());
}