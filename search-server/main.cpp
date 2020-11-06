#include <iostream>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <set>
#include <algorithm>

#include "test_runner.h"

using namespace std;

struct DocumentInfo {
    string name;
    int count;
    friend bool operator<(const DocumentInfo& lhs, const DocumentInfo& rhs) {
        return lhs.count < rhs.count;
    }
};

void UpdateDocumentBase(istream& document_input, vector<unordered_map<string, int>>& db) {
    while (!document_input.eof()) {
        string document;
        getline(document_input, document);
        stringstream stream(document);
        unordered_map<string, int> result;
        while (!stream.eof()) {
            string word;
            stream >> word;
            if (word.length()) {
                ++result[word];
            }
        }
        db.push_back(move(result));
    }
}

vector<string> getIntersection(const vector<string>& lhs, const vector<string>& rhs) {
    vector<string> result;
    result.reserve(lhs.size() + rhs.size());
    set_intersection(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), back_inserter(result));
    return result;
}

vector<string> getKeys(const vector<vector<string>>& sortedKeys) {
    vector<string> result = getIntersection(sortedKeys.front(), sortedKeys.back());
    for (auto it = sortedKeys.begin(); it != sortedKeys.end(); ++it) {
        result = getIntersection(result, *it);
    }
    return result;
}



int main() {
    vector<unordered_map<string, int>> data;
    string docs;
    docs += "london is the new capital of great britain\n";
    // документ содержит 7 слов
    docs += "moscow is the new capital of the russian federation\n";
    // документ содержит 6 слов
    docs += "paris is the capital of france";
    // документ содержит 3 слова

    istringstream document_input(docs);
    UpdateDocumentBase(document_input, data);
    vector<vector<string>> sortedKeys;

    transform(data.begin(), data.end(), back_inserter(sortedKeys), [](auto table) {
        vector<string> elems;
        transform(table.begin(), table.end(), back_inserter(elems), [](auto pair) {return pair.first;});
        return elems;
        });

    auto result = getKeys(sortedKeys);
    cout << result;




    return 0;
}
