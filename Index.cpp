#include "Index.h"
forward_list<Document> Index::printDocumentNames(Word word) {
    forward_list<Document>::iterator iter;
    if(invertedIndex.find(word)==nullptr) {
        //cout << "WORD NOT FOUND" << endl;
        return invertedIndex.find(word)->key.getDocuments();
    }
    else {
        //cout << "FOUND" << endl;
        for (iter = invertedIndex.find(word)->key.getDocuments().begin();
             iter != invertedIndex.find(word)->key.getDocuments().end(); ++iter) {

            //cout << iter->getDocName() << endl;
        }
    }
    return invertedIndex.find(word)->key.getDocuments();
}
void Index::addToAVLTree(Word word, Document docName) {
    AVLTree<Word>::Node *node = invertedIndex.find(word);
    if(node==nullptr) {
        word.addDocument(docName);
        invertedIndex.insert(word);
        //node->key.getDoc(docName.getDocName());
    }
    else if (node != nullptr && !node->key.doesFileExist(docName.getDocName())) {
        node->key.addDocument(docName);
        node->key.getDoc(docName.getDocName());
    }
    else{
            node->key.getDoc(docName.getDocName());
    }
}

void Index::print() {
    invertedIndex.inOrder();
}