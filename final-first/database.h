#include <map>
#include <vector>
#include <algorithm>

#include "date.h"

#ifndef __DATABASE_H__
#define __DATABASE_H__

/* TODO Заменить все algorithm на циклы

*/

class Database {
private:
    std::map<Date, std::vector<std::string>> data;
public:
    void printAllEvents(std::ostream& stream);
    void addEvent(const Date& date, const std::string& event);
    bool deleteEvent(const Date& date, const std::string& event);
    int deleteEvents(const Date& date);
    void findEvents(const Date& date, std::ostream& stream);
};

#endif // __DATABASE_H__