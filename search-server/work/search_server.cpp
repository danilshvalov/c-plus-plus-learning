#include "search_server.h"
#include "iterator_range.h"
#include "test_runner.h"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>

vector<string> SplitIntoWords(const string& line) {
  istringstream words_input(line);
  return { istream_iterator<string>(words_input), istream_iterator<string>() };
}

SearchServer::SearchServer(istream& document_input) {
  UpdateDocumentBase(document_input);
}

void SearchServer::UpdateDocumentBase(istream& document_input) {
  InvertedIndex new_index;

  for (string current_document; getline(document_input, current_document); ) {
    new_index.Add(move(current_document));
  }

  index = move(new_index);
}

void SearchServer::AddQueriesStream(
  istream& query_input, ostream& search_results_output
) {
  vector<pair<size_t, size_t>> docid_count(index.GetSize());
  for (string current_query; getline(query_input, current_query); ) {
    for (size_t i = 0; i < docid_count.size(); ++i) {
      docid_count[i] = { i, 0 };
    }
    for (const auto& word : SplitIntoWords(current_query)) {
      for (const auto& info : index.Lookup(word)) {
        docid_count[info.first].second += info.second;
      }
    }

    partial_sort(
      begin(docid_count),
      begin(docid_count) + min(5, (int)distance(begin(docid_count), end(docid_count))),
      end(docid_count),
      [](pair<size_t, size_t> lhs, pair<size_t, size_t> rhs) {
        return(lhs.second > rhs.second) || (lhs.second == rhs.second) && (lhs.first < rhs.first);

      });

    search_results_output << current_query << ':';
    for (const auto& [docid, hitcount] : Head(docid_count, 5)) {
      if (hitcount == 0) break;
      search_results_output << " {"
        << "docid: " << docid << ", "
        << "hitcount: " << hitcount << '}';
    }

    search_results_output << endl;
  }
}

void InvertedIndex::Add(const string& document) {
  docs.push_back(document);

  const size_t docid = docs.size() - 1;
  unordered_map<string, size_t> wordsCount;
  for (const auto& word : SplitIntoWords(document)) {
    ++wordsCount[word];
  }
  for (const auto& [word, countOfWord] : wordsCount) {
    index[word].push_back(make_pair(docid, countOfWord));
  }
}

vector<pair<size_t, size_t>> InvertedIndex::Lookup(const string& word) const {
  if (auto it = index.find(word); it != index.end()) {
    return it->second;
  } else {
    return {};
  }
}
