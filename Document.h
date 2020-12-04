#ifndef SEARCH_ENGINE_DOCUMENT_H
#define SEARCH_ENGINE_DOCUMENT_H
#include <string>
#include <forward_list>
#include <unordered_set>
using namespace std;
class Document {
private:
    int numTimesInTitle;
    int numTimesInAbstract;
    int numTimesInBody;
    string Title;
    string docName;
    unordered_set<string> docAuthor;
    string publisher;
    string publishDate;
public:
    // Document();
    string getTitle(){return Title;}
    void setTitle(string a){Title=a;}
    Document(int,int,int,string,unordered_set<string>);
    int getTimesInTitle(){return numTimesInTitle;}
    void setTimesInTitle(int num){numTimesInTitle=num;}
    int getTimesInAbstract(){return numTimesInAbstract;}
    void setTimesInAbstract(int num){numTimesInAbstract=num;}
    int getTimesInBody(){return numTimesInBody;}
    void setTimesInBody(int num){numTimesInBody=num;}
    string getDocName(){return docName;}
    void setDocName(string name){docName=name;}
    unordered_set<string> getAuthors(){return docAuthor;}
    void setAuthors(unordered_set<string> temp){docAuthor=temp;}
    void increaseBody(){numTimesInBody=numTimesInBody+1;}
    bool operator<(const Document&);
    bool operator>(const Document&);
    bool operator<=(const Document&);
    bool operator>=(const Document&);
    bool operator==(const Document&);

};


#endif //SEARCH_ENGINE_DOCUMENT_H