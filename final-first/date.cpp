#include "date.h"

bool operator<(const Date& lhs, const Date& rhs) {
    return std::make_tuple(lhs.year, lhs.month, lhs.day) < std::make_tuple(rhs.year, rhs.month, rhs.day);
}

bool operator>(const Date& lhs, const Date& rhs) {
    return std::make_tuple(lhs.year, lhs.month, lhs.day) > std::make_tuple(rhs.year, rhs.month, rhs.day);
}

bool operator==(const Date& lhs, const Date& rhs) {
    return std::make_tuple(lhs.year, lhs.month, lhs.day) == std::make_tuple(rhs.year, rhs.month, rhs.day);
}