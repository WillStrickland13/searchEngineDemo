#include "Word.h"
#include <iostream>
#include <cctype>
Word::Word(){
    word= "";
}
Word::Word(const Word& from) {
    word=from.word;
    //docs=from.docs;
}
bool Word::operator<(const Word & other) {
    if(this->getWord()<other.word){
        return true;
    }
    return false;
}
bool Word::operator>(const Word& other){
    if(this->getWord()>other.word){
        return true;
    }
    return false;
}
bool Word::operator<=(const Word & other) {
    if(this->getWord()<=other.word){
        return true;
    }
    return false;
}
bool Word::operator>=(const Word& other){
    if(this->getWord()>=other.word){
        return true;
    }
    return false;
}
bool Word::operator==(const Word& other){
    if(this->word==other.word) {
        //cout<<this->word<< " EQUALS "<<other.word<<endl;
        return true;
    }

    return false;
}
ostream& operator<<(ostream& out,const Word & toPrint){
    out<<toPrint.word;
    return out;
}
bool Word::doesFileExist(string doc) {
    forward_list<Document>::iterator iter;

    for (iter = docs.begin(); iter != docs.end(); ++iter) {
        if(iter->getDocName()==doc){
            return true;
        }
    }
    return false;
}
Document Word::getDoc(string docName) {
    forward_list<Document>::iterator iter;

    for (iter = docs.begin(); iter != docs.end(); ++iter) {
        if(iter->getDocName()==docName){
            iter->increaseBody();
            return *iter;
        }
    }
    return *iter;
}