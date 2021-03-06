#include <tuple>
#include <iostream>
#include <iomanip>

#include "exceptions.h"

#ifndef __DATE_H__

struct Date {
    int year;
    int month;
    int day;
    friend bool operator<(const Date& lhs, const Date& rhs);
    friend bool operator>(const Date& lhs, const Date& rhs);
    friend bool operator==(const Date& lhs, const Date& rhs);
    friend std::ostream& operator<<(std::ostream& stream, const Date& date);
};

void checkValidDate(const Date& date);

Date parseDate(const std::string& input);

#endif
#define __DATE_H__


// __DATE_H__