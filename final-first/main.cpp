#include <iostream>
#include <optional>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <array>
#include <map>

#include "test_runner.h"

class Database {
private:
    std::map<int, std::array<std::array<int, 31>, 12>> _data;
public:
    void printAllEvents(std::ostream& stream) {
        for (const auto& [year, month] : _data) {

        }
    }
};

std::optional<std::string> getString(std::stringstream& stream) {
    if (!stream.eof()) {
        std::string result;
        stream >> result;
        return std::move(result);
    }
    return {};
}

struct Date {
    int year;
    int month;
    int day;
};

Date parseDate(const std::string& input) {
    Date date;
    std::stringstream stream;
    stream << input;

    stream >> date.year;

    if (stream.eof() || stream.peek() != '-') throw ("Wrong date format: " + input);
    stream.ignore(1);
    stream >> date.month;

    if (stream.eof() || stream.peek() != '-') throw ("Wrong date format: " + input);
    stream.ignore(1);
    stream >> date.day;
    if (stream.fail() || !stream.eof()) throw ("Wrong date format: " + input);

    return date;
}

void checkValidDate(const Date& date) {
    if (date.month < 1 || date.month > 12) {
        std::stringstream error;
        error << "Month value is invalid " << date.month;
        throw error.str();
    }
    if (date.day < 1 || date.day > 31) {
        std::stringstream error;
        error << "Day value is invalid: " << date.day;
        throw error.str();
    }
}

void parseRequest(std::istream& stream) {
    std::stringstream input;
    std::string inputText;
    std::getline(stream, inputText);
    input << inputText;

    auto type = getString(input);
    auto date = getString(input);
    auto event = getString(input);

    if (type.value() == "Print") {
        std::cout << "Print all events!" << '\n';
    } else if (type.value() == "Add") {
        std::cout << "Add \"" << date.value() << "\" \"" << event.value() << "\"\n";
    } else if (type.value() == "Del") {
        if (event) {
            std::cout << "Del \"" << date.value() << "\" \"" << event.value() << "\"\n";
        } else {
            std::cout << "Del \"" << date.value() << "\" without event\n";
        }
    }
}

int main() {
    std::string date;
    std::cin >> date;
    parseDate(date);

    return 0;
}