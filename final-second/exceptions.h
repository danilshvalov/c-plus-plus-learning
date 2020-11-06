#include <exception>
#include <sstream>

#ifndef __EXCEPTIONS_H__
#define __EXCEPTIONS_H__

void DateFormatException(const std::string& msg);
void MonthValueException(const std::string& msg);
void DayValueException(const std::string& msg);
void UnknownCommandException(const std::string& msg);

#endif // __EXCEPTIONS_H__