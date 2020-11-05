#include "date.h"

bool operator<(const Date& lhs, const Date& rhs) {
    return std::tie(lhs.year, lhs.month, lhs.day) < std::tie(rhs.year, rhs.month, rhs.day);
}

bool operator>(const Date& lhs, const Date& rhs) {
    return std::tie(lhs.year, lhs.month, lhs.day) > std::tie(rhs.year, rhs.month, rhs.day);
}

bool operator==(const Date& lhs, const Date& rhs) {
    return std::tie(lhs.year, lhs.month, lhs.day) == std::tie(rhs.year, rhs.month, rhs.day);
}

std::ostream& operator<<(std::ostream& stream, const Date& date) {
    return stream << std::setw(4) << std::setfill('0') << date.year << '-' << std::setw(2) << date.month << '-' << std::setw(2) << date.day;
}

void checkValidDate(const Date& date) {
    if (date.month < 1 || date.month > 12) {
        monthValueException(std::to_string(date.month));
    }
    if (date.day < 1 || date.day > 31) {
        dayValueException(std::to_string(date.day));
    }
}

Date parseDate(const std::string& input) {
    Date date;
    std::stringstream stream;
    stream << input;

    stream >> date.year;

    if (stream.eof() || stream.peek() != '-') dateFormatException(input);
    stream.ignore(1);
    stream >> date.month;

    if (stream.eof() || stream.peek() != '-') dateFormatException(input);
    stream.ignore(1);
    stream >> date.day;
    if (stream.fail() || !stream.eof()) dateFormatException(input);

    checkValidDate(date);

    return date;
}