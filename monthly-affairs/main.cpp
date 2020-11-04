#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <array>

#include "database.h"

using namespace std;

template<typename T>
ostream& operator<<(ostream& stream, const vector<T>& v) {
    stream << "[";
    for (int i = 0; i < v.size(); ++i) {
        stream << v[i];
        if (i != v.size() - 1) {
            stream << ", ";
        }
    }
    stream << "]";

    return stream;
}

const  std::array<int, 12> MONTH = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

class Database {
private:
    std::vector<std::vector<std::string>> data;
    uint currentMonth = 0;
public:
    Database() {
        data.resize(MONTH[currentMonth]);
    }
    void nextMonth() {
        int nextMonth = (currentMonth + 1) % MONTH.size();
        int currentMonthSize = MONTH[currentMonth];
        int nextMonthSize = MONTH[nextMonth];
        if (currentMonthSize > nextMonthSize) {
            for (int j = 0; j < currentMonthSize - nextMonthSize; ++j) {
                data.emplace_back(data[currentMonthSize - j - 1]);
            }
        }
        data.resize(nextMonthSize);
        currentMonth = nextMonth;
    }
    void addWork(uint day, const std::string& work) {
        data[--day].push_back(work);
    }
    const std::vector<std::string>& getDump(uint day) {
        return data[--day];
    }
    void printDump(ostream& stream, const std::vector<std::string>& values) {
        stream << values.size() << " ";
        stream << accumulate(values.begin(), values.end(), std::string(), [](std::string& current, const std::string& value) {
            return current += " " + value;
            });
        stream << "\n";
    }
};



int main() {
    Database data;


    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        string request;
        cin >> request;

        if (request == "NEXT") {
            data.nextMonth();
        } else {
            int day;
            cin >> day;
            if (request == "ADD") {
                string action;
                cin >> action;
                data.addWork(day, action);
            } else if (request == "DUMP") {
                data.printDump(cout, data.getDump(day));
            }
        }
    }

    return 0;
}