#include <iostream>
#include <sstream>
#include <map>

#include "date.h"
#include "exceptions.h"
#include "database.h"

void parseRequest(Database& db, std::istream& input, std::ostream& output, const std::string& command) {
    if (command == "Print") {
        db.printAllEvents(output);
    } else if (command == "Add") {
        std::string event, date;
        input >> date >> event;
        db.addEvent(parseDate(date), event);
    } else if (command == "Del") {
        std::string date;
        input >> date;
        if (!input.eof() && input.peek() != '\n') {
            std::string event;
            input >> event;
            if (db.deleteEvent(parseDate(date), event)) {
                output << "Deleted successfully" << std::endl;
            } else {
                output << "Event not found" << std::endl;
            }
        } else {
            int deletedCount = db.deleteEvents(parseDate(date));
            output << "Deleted " << deletedCount  << " events" << std::endl;
        }
    } else if (command == "Find") {
        std::string date;
        input >> date;
        db.findEvents(parseDate(date), output);
    } else {
        unknownCommandException(command);
    }
}

int main() {
    Database db;
    std::string input;
    while (std::getline(std::cin, input)) {
        std::stringstream stream;
        stream << input;
        std::string request;
        stream >> request;
        if (request.size()) {
            try {
                parseRequest(db, stream, std::cout, request);
            } catch (std::exception& e) {
                std::cout << e.what();
                break;
            }
        }
    }
    return 0;
}