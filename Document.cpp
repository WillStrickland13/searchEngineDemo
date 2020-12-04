
#include "Document.h"

//Document::Document() {
//    numTimesInBody=0;
//    numTimesInAbstract=0;
//    numTimesInTitle=0;
//    docName=nullptr;
//    publishDate=nullptr;
//    publisher=nullptr;
//}
Document::Document(int body, int abstract, int title, string docName,unordered_set<string> authors) {
    numTimesInBody=body;
    numTimesInAbstract=abstract;
    numTimesInTitle=title;
    this->docName=docName;
    docAuthor=authors;
}
bool Document::operator>(const Document & other) {
    if(this->numTimesInBody<other.numTimesInBody){
        return true;
    }
    return false;
}
bool Document::operator<(const Document& other){
    if(this->numTimesInBody>other.numTimesInBody){
        return true;
    }
    return false;
}
bool Document::operator<=(const Document & other) {
    if(this->numTimesInBody<=other.numTimesInBody){
        return true;
    }
    return false;
}
bool Document::operator>=(const Document& other){
    if(this->numTimesInBody>=other.numTimesInBody){
        return true;
    }
    return false;
}
bool Document::operator==(const Document& other){
    if(this->numTimesInBody==other.numTimesInBody) {
        //cout<<this->Document<< " EQUALS "<<other.Document<<endl;
        return true;
    }

    return false;
}