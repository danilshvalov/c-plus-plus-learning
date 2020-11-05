#include <exception>
#include <sstream>

#ifndef __EXCEPTIONS_H__
#define __EXCEPTIONS_H__

void dateFormatException(const std::string& msg);
void monthValueException(const std::string& msg);
void dayValueException(const std::string& msg);
void unknownCommandException(const std::string& msg);

#endif // __EXCEPTIONS_H__