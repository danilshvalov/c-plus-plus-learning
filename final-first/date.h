#include <tuple>

#ifndef __DATE_H__

struct Date {
    int year;
    int month;
    int day;
    friend bool operator<(const Date& lhs, const Date& rhs);
    friend bool operator>(const Date& lhs, const Date& rhs);
    friend bool operator==(const Date& lhs, const Date& rhs);
};

#endif
#define __DATE_H__


// __DATE_H__