#ifndef SEARCH_ENGINE_WORD_H
#define SEARCH_ENGINE_WORD_H
#include <string>
#include <vector>
#include <forward_list>
#include "Document.h"
using namespace std;

class Word {
private:
    string word;
    forward_list<Document> docs;
public:
    // ~Word();
    Word();
    Word(const Word&);
    string getWord(){return word;}
    void setWord(string w){word=w;}
    void addDocument(Document doc){docs.emplace_front(doc);}
    forward_list<Document> getDocuments(){return docs;}
    bool operator<(const Word&);
    bool operator>(const Word&);
    bool operator<=(const Word&);
    bool operator>=(const Word&);
    bool operator==(const Word&);
    friend ostream& operator<<(ostream&,const Word&);
    bool doesFileExist(string doc);
    Document getDoc(string);
};


#endif //SEARCH_ENGINE_WORD_H