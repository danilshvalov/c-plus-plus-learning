#include "database.h"
#include "date.h"
#include "condition_parser.h"
#include "node.h"
#include "test_runner.h"

#include <iostream>
#include <stdexcept>

using namespace std;

string ParseEvent(istream& is) {
    while (!is.eof() && is.peek() == ' ') is.ignore(1);
    string words;
    getline(is, words);
    return words;
}

void TestAll();

void RunDatabase(istream& input, ostream& output) {
    Database db;

    for (string line; getline(input, line); ) {
        istringstream is(line);

        string command;
        is >> command;

        if (command == "Add") {
            const auto date = ParseDate(is);
            const auto event = ParseEvent(is);
            db.Add(date, event);
        } else if (command == "Print") {
            db.Print(output);
        } else if (command == "Del") {
            auto condition = ParseCondition(is);
            auto predicate = [condition](const Date& date, const string& event) {
                return condition->Evaluate(date, event);
            };
            int count = db.RemoveIf(predicate);
            output << "Removed " << count << " entries" << endl;
        } else if (command == "Find") {
            auto condition = ParseCondition(is);
            auto predicate = [condition](const Date& date, const string& event) {
                return condition->Evaluate(date, event);
            };

            const auto entries = db.FindIf(predicate);
            for (const auto& entry : entries) {
                output << entry << endl;
            }
            output << "Found " << entries.size() << " entries" << endl;
        } else if (command == "Last") {
            try {
                output << db.Last(ParseDate(is)) << endl;
            } catch (invalid_argument&) {
                output << "No entries" << endl;
            }
        } else if (command.empty()) {
            continue;
        } else {
            throw logic_error("Unknown command: " + command);
        }
    }
}

int main() {
    TestAll();

    RunDatabase(cin, cout);


    return 0;
}

void TestParseEvent() {
    {
        istringstream is("event");
        AssertEqual(ParseEvent(is), "event", "Parse event without leading spaces");
    }
    {
        istringstream is("   sport event ");
        AssertEqual(ParseEvent(is), "sport event ", "Parse event with leading spaces");
    }
    {
        istringstream is("  first event  \n  second event");
        vector<string> events;
        events.push_back(ParseEvent(is));
        events.push_back(ParseEvent(is));
        AssertEqual(events, vector<string>{"first event  ", "second event"}, "Parse multiple events");
    }
}

void SimpleTests() {
    {
        istringstream is("Add 2017-06-01 1st of June\nAdd 2017-07-08 8th of July\nAdd 2017-07-08 Someone's birthday\nDel date == 2017-07-08");
        ostringstream os;
        RunDatabase(is, os);
        AssertEqual(os.str(), "Removed 2 entries\n", "Simple add and deleting");
    }
    {
        istringstream is("Add 2017-01-01 Holiday\nAdd 2017-03-08 Holiday\nAdd 2017-1-1 New Year\nAdd 2017-1-1 New Year\nPrint");
        ostringstream os;
        RunDatabase(is, os);
        AssertEqual(os.str(), "2017-01-01 Holiday\n2017-01-01 New Year\n2017-03-08 Holiday\n", "Simple Print");
    }
    {
        istringstream is("Add 2017-01-01 Holiday\nAdd 2017-03-08 Holiday\nAdd 2017-01-01 New Year\nFind event != \"working day\"\nAdd 2017-05-09 Holiday");
        ostringstream os;
        RunDatabase(is, os);
        AssertEqual(os.str(), "2017-01-01 Holiday\n2017-01-01 New Year\n2017-03-08 Holiday\nFound 3 entries\n", "Simple Find");
    }
    {
        istringstream is("Add 2017-01-01 New Year\nAdd 2017-03-08 Holiday\nAdd 2017-01-01 Holiday\nLast 2016-12-31\nLast 2017-01-01\nLast 2017-06-01\nAdd 2017-05-09 Holiday");
        ostringstream os;
        RunDatabase(is, os);
        AssertEqual(os.str(), "No entries\n2017-01-01 Holiday\n2017-03-08 Holiday\n", "Simple Last");
    }
    {
        istringstream is("Add 2017-11-21 Tuesday\nAdd 2017-11-20 Monday\nAdd 2017-11-21 Weekly meeting\nPrint\nFind event != \"Weekly meeting\"\nLast 2017-11-30\nDel date > 2017-11-20\nLast 2017-11-30\nLast 2017-11-01");
        ostringstream os;
        RunDatabase(is, os);
        AssertEqual(os.str(), "2017-11-20 Monday\n2017-11-21 Tuesday\n2017-11-21 Weekly meeting\n2017-11-20 Monday\n2017-11-21 Tuesday\nFound 2 entries\n2017-11-21 Weekly meeting\nRemoved 2 entries\n2017-11-20 Monday\nNo entries\n", "All inclusive");
    }
}

void IncludesTests() {
    {
        Database db;
        int n = 0;
        AssertEqual(db.Last(Date(1, 1, 1)), "No entries", ("test" + to_string(++n)));
        db.Add(Date(1, 10, 1), "C3");
        db.Add(Date(2, 1, 1), "B3");
        db.Add(Date(3, 1, 1), "A3");
        AssertEqual(db.Last(Date(1, 1, 1)), "No entries", ("test" + to_string(++n)));
        AssertEqual(db.Last(Date(1, 10, 1)), "0001-10-01 C3", ("test" + to_string(++n)));
        AssertEqual(db.Last(Date(1, 12, 1)), "0001-10-01 C3", ("test" + to_string(++n)));
        AssertEqual(db.Last(Date(2, 1, 1)), "0002-01-01 B3", ("test" + to_string(++n)));
        AssertEqual(db.Last(Date(2, 5, 1)), "0002-01-01 B3", ("test" + to_string(++n)));
        AssertEqual(db.Last(Date(3, 1, 1)), "0003-01-01 A3", ("test" + to_string(++n)));
        AssertEqual(db.Last(Date(4, 10, 1)), "0003-01-01 A3", ("test" + to_string(++n)));
        db.Add(Date(3, 1, 1), "A1");
        db.Add(Date(2, 1, 1), "B1");
        db.Add(Date(1, 10, 1), "C1");
        db.Add(Date(2, 1, 1), "B2");
        db.Add(Date(1, 10, 1), "C2");
        db.Add(Date(3, 1, 1), "A2");
        AssertEqual(db.Last(Date(1, 1, 1)), "No entries", ("test" + to_string(++n)));
        AssertEqual(db.Last(Date(1, 10, 1)), "0001-10-01 C2", ("test" + to_string(++n)));
        AssertEqual(db.Last(Date(1, 12, 1)), "0001-10-01 C2", ("test" + to_string(++n)));
        AssertEqual(db.Last(Date(2, 1, 1)), "0002-01-01 B2", ("test" + to_string(++n)));
        AssertEqual(db.Last(Date(2, 5, 1)), "0002-01-01 B2", ("test" + to_string(++n)));
        AssertEqual(db.Last(Date(3, 1, 1)), "0003-01-01 A2", ("test" + to_string(++n)));
        AssertEqual(db.Last(Date(4, 10, 1)), "0003-01-01 A2", ("test" + to_string(++n)));
    }
}

void IncludesSecondTests() {
    {
        Database db;
        vector<string> events = {
            "a", "z", "b", "y", "c", "x", "d", "w", "e", "v"
        };
        for (const auto& e : events) { db.Add(Date(4, 5, 6), e); }

        // I am going to delete every second event to get the following sequence
        vector<string> filtered = { "a", "b", "c", "d", "e" };

        stringstream true_answer;
        for (const auto& e : filtered) {
            true_answer << Date(4, 5, 6) << " " << e << endl;
        }

        int count = db.RemoveIf(
            [](const Date& d, const string& e) { return e > "m"; });

        stringstream my_answer;
        db.Print(my_answer);

        AssertEqual(count, 5, "test 8-1");
        AssertEqual(my_answer.str(), true_answer.str(), "test 8-2"); // <-- this can fail
    }
}

void TestAll() {
    TestRunner tr;
    tr.RunTest(TestParseEvent, "TestParseEvent");
    tr.RunTest(TestParseCondition, "TestParseCondition");
    tr.RunTest(SimpleTests, "SimpleTests");
    tr.RunTest(IncludesTests, "IncludesTests");
    tr.RunTest(IncludesSecondTests, "IncludesSecondTests");
}