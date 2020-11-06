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

void CheckValidDate(const Date& date);

Date ParseDate(std::istream& os);

#endif
#define __DATE_H__


// __DATE_H__