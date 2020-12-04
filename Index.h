#ifndef SEARCH_ENGINE_INDEX_H
#define SEARCH_ENGINE_INDEX_H
#include "AVLTree.h"
#include "Word.h"
class Index {
private:
    AVLTree<Word> invertedIndex;
public:
    Word getWord(Word);
    void addWord(Word);
    bool doesWordExist(Word);
    void addDocumentToWord(string,Word);
    forward_list<Document> printDocumentNames(Word);
    void addToAVLTree(Word, Document);
    void print();
};


#endif //SEARCH_ENGINE_INDEX_H
