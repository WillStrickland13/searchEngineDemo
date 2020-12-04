#include "simdjson.h"
#include <iostream>
#include <algorithm>
#include <string>
#include "documentParser.h"
#include "PorterStemming.cpp"
#include "QueryEngine.h"
using namespace simdjson;
using namespace std;

int main() {
    cout<<"Welcome to Wyatt and Will's Search Engine, we are currently parsing the documents, please wait."<<endl;
    QueryEngine queryEngine;
    queryEngine.parseDocs("C:\\Users\\leopa\\Downloads\\timing_demo_data_sets\\ds_02\\");
    string wordToFind;
    cout<<"Enter Search Term: ";
    getline(cin,wordToFind);
    while(wordToFind!="1") {
        queryEngine.getResults(wordToFind);
        queryEngine.clear();
        getline(cin,wordToFind);
    }
    cout<<"Exiting, thank you for using our search engine"<<endl;
}