#include <iostream>
#include <optional>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <array>
#include <map>
#include <tuple>
#include <set>

#include "test_runner.h"
#include "date.h"

class Exceptions {
public:
    static void dateFormatException(const std::string& msg) {
        std::stringstream stream;
        stream << "Wrong format date: " << msg;
        throw stream.str();
    }
    static void monthValueException(const std::string& msg) {
        std::stringstream stream;
        stream << "Month value is invalid: " << msg;
        throw stream.str();
    }
    static void dayValueException(const std::string& msg) {
        std::stringstream stream;
        stream << "Day value is invalid: " << msg;
        throw stream.str();
    }
};

Exceptions exceptions;



class Database {
private:
    std::set<Date> _data;
public:
    void printAllEvents(std::ostream& stream) {

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



Date parseDate(const std::string& input) {
    Date date;
    std::stringstream stream;
    stream << input;

    stream >> date.year;

    if (stream.eof() || stream.peek() != '-') exceptions.dateFormatException(input);
    stream.ignore(1);
    stream >> date.month;

    if (stream.eof() || stream.peek() != '-') exceptions.dateFormatException(input);
    stream.ignore(1);
    stream >> date.day;
    if (stream.fail() || !stream.eof()) exceptions.dateFormatException(input);

    return date;
}

void checkValidDate(const Date& date) {
    if (date.month < 1 || date.month > 12) {
        exceptions.monthValueException(std::to_string(date.month));
    }
    if (date.day < 1 || date.day > 31) {
        exceptions.dayValueException(std::to_string(date.day));
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