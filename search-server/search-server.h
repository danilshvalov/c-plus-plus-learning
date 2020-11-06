#include <iostream>

using namespace std;

#ifndef __SEARCH-SERVER_H__
#define __SEARCH-SERVER_H__

class SearchServer {
public:
    SearchServer() = default;
    explicit SearchServer(istream& document_input);

    void UpdateDocumentBase(istream& document_input);
    void AddQueriesStream(istream& query_input, ostream& search_results_output);
};
#endif // __SEARCH-SERVER_H__