
#ifndef SEARCH_ENGINE_QUERYENGINE_H
#define SEARCH_ENGINE_QUERYENGINE_H
#include <vector>
#include <iostream>
#include <istream>
#include <sstream>
#include <iterator>
#include <string_view>
#include <numeric>
#include "porter2_stemmer.h"
#include "documentParser.h"
using namespace std;
class QueryEngine {
private:
    int ANDorOR;//0 signifies neither, 1 signifies or, 2 signifies and
    string query;
    bool NOT;
    string notWord;
    string author;
    documentParser docParser;
    vector<Document> finalDocs;
    void Or(string,string);
    void And(string,string);
    void oneWord(string);
    void Not();
    vector<string> splitString(const string&);
    void printResults();
    void sortResults();
    void printArticle();


public:
    void clear();
    vector<string> analyzeQuery(string);
    vector<Document> getResults(string);
    void parseDocs(string);
};


#endif //SEARCH_ENGINE_QUERYENGINE_H
