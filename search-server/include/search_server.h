#pragma once

#include <istream>
#include <ostream>
#include <set>
#include <list>
#include <vector>
#include <map>
#include <string>
#include <numeric>
#include <mutex>
using namespace std;

class InvertedIndex {
public:
  void Add(const string& document);
  vector<pair<size_t, size_t>> Lookup(const string& word) const;

  size_t GetSize() const {
    return docs.size();
  }

private:
  map<string, vector<pair<size_t, size_t>>> index;
  vector<string> docs;
};

class SearchServer {
public:
  SearchServer() = default;
  explicit SearchServer(istream& document_input);
  void UpdateDocumentBase(istream& document_input);
  void AddQueriesStream(istream& query_input, ostream& search_results_output);

private:
  InvertedIndex index;
};
