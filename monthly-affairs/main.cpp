#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <array>

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

int main() {
    array<int, 12> MONTH = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    int currentMonth = 0;
    vector<vector<string>> database;

    database.resize(MONTH[currentMonth]);

    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        string request;
        cin >> request;

        if (request == "NEXT") {
            int nextMonth = (currentMonth + 1) % MONTH.size();
            int currentMonthSize = MONTH[currentMonth];
            int nextMonthSize = MONTH[nextMonth];
            if (currentMonthSize > nextMonthSize) {
                for (int j = 0; j < currentMonthSize - nextMonthSize; ++j) {
                    for (const auto& item : database[currentMonthSize - j - 1]) {
                        database[nextMonthSize - 1].push_back(item);
                    }
                }
            }
            database.resize(nextMonthSize);
            currentMonth = nextMonth;
        } else {
            int day;
            cin >> day;
            if (request == "ADD") {
                string action;
                cin >> action;
                database[day - 1].push_back(action);
            } else if (request == "DUMP") {
                cout << database[day - 1].size() << " ";
                for (const auto& data : database[day - 1]) {
                    cout << data << " ";
                }
                cout << endl;
            }
        }
    }

    return 0;
}