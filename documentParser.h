//
// Created by leopa on 11/16/2020.
//

#ifndef SEARCH_ENGINE_DOCUMENTPARSER_H
#define SEARCH_ENGINE_DOCUMENTPARSER_H
#include "simdjson.h"
#include <string>
#include <string_view>
#include <dirent.h>
#include <sys/types.h>
#include <vector>
#include "Index.h"
#include <iostream>
#include <fstream>
#include <set>
#include "HashTable.h"
#include "porter2_stemmer.h"
//#include <filesystem>
using namespace std;
class documentParser {

private:
    set<string> stopWords;
    Index tree;
public:

    list<string> removeStopWords(list<string> words);//remove stop words from list of words
    void fillStopWords(string);//takes in a string representing file name
    list<string> splitString(const string &str);//splits up given string and return list of parsed strings
    HashTable<string> getStopWords();
    void printWithNoStopWords(list<string>const &);
    vector<string> getAllFileNamesInFolder(string folder);
    void loadTree(string fileName);
    forward_list<Document> findWord(Word);
};


#endif //SEARCH_ENGINE_DOCUMENTPARSER_H
