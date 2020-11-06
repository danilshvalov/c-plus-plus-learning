#include <map>
#include <vector>
#include <algorithm>

#include "date.h"

#ifndef __DATABASE_H__
#define __DATABASE_H__


class Database {
private:
    std::map<Date, std::vector<std::string>> data;
public:
    void Print(std::ostream& stream);
    void Add(const Date& date, const std::string& event);
    int RemoveIf(std::function<bool (const Date& date, const std::string& event)> func);
    std::string Last(const Date& date);
    std::vector<std::string> FindIf(std::function<bool (const Date& date, const std::string& event)> func);
};

#endif // __DATABASE_H__