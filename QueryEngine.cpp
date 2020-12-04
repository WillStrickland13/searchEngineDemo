#include "QueryEngine.h"
vector<string> QueryEngine::analyzeQuery(string search) {
    transform(search.begin(), search.end(), search.begin(), ::tolower);
    ANDorOR=0;
    vector<string> final;
    istringstream iss(search);
    vector<string> vstrings=splitString(search);
    NOT = false;

    for(int i=0;i<vstrings.size();i++){
        cout<<vstrings[i];
        if(vstrings[i]=="not"){
            NOT=true;
            notWord=vstrings[i+1];
            vstrings.erase(vstrings.begin()+i);
        }
        else if(vstrings[i]=="or"){
            ANDorOR=1;
            // vstrings.erase(vstrings.begin()+i);
        }
        else if(vstrings[i]=="and"){
            ANDorOR=2;
            //vstrings.erase(vstrings.begin()+i);

        }
        else if(vstrings[i]=="author"){
            author=vstrings[i+1];
            //vstrings.erase(vstrings.begin()+i);
        }
        else
            final.push_back(vstrings[i]);
    }
    cout<<endl;
    for(int i = 0; i<final.size();i++){
        Porter2Stemmer::trim(final[i]);
        Porter2Stemmer::stem(final[i]);
        // cout<<final[i];
    }
    return final;
}
vector<Document> QueryEngine::getResults(string wordToFind) {
    vector<string> searchWords;
    Word toFind;
    searchWords=analyzeQuery(wordToFind);
    if(ANDorOR==0){
        oneWord(searchWords[0]);
    }
    if(ANDorOR==1){
        Or(searchWords[0],searchWords[1]);
    }
    if(ANDorOR==2){
        And(searchWords[0],searchWords[1]);
    }
    if(NOT){
        //  cout<<endl<<"NOT WORD = "<<notWord<<endl;
        Not();
    }

    printResults();
    return finalDocs;
}
void QueryEngine::parseDocs(string fileName) {
    docParser.loadTree(fileName);
}
void QueryEngine::Not() {
    transform(notWord.begin(), notWord.end(), notWord.begin(), ::tolower);
    Porter2Stemmer::trim(notWord);
    Porter2Stemmer::stem(notWord);
    cout<<notWord;
    Word w1;
    w1.setWord(notWord);
    forward_list<Document> w1Docs=docParser.findWord(w1);
    forward_list<Document>::iterator iter1;
//    cout<<endl<<"HERE ARE THE DOCS THAT CONTAIN THE NOT WORD"<<endl;
//    for(int i = 0; i<finalDocs.size();i++){
//        for(iter1=w1Docs.begin();iter1!=w1Docs.end();++iter1){
//            if(finalDocs[i]==iter1->getDocName()){
//                finalDocs.erase(finalDocs.begin()+i);
//            }
//        }
//    }
    for(iter1=w1Docs.begin();iter1!=w1Docs.end();++iter1){
        // cout<<iter1->getDocName()<<endl;
        for(int i=0;i<finalDocs.size();i++){
            if(finalDocs[i].getDocName()==iter1->getDocName()){
                finalDocs.erase(finalDocs.begin()+i);
            }
        }
    }
}
void QueryEngine::Or(string word1, string word2) {
    transform(word1.begin(), word1.end(), word1.begin(), ::tolower);
    transform(word2.begin(), word2.end(), word2.begin(), ::tolower);
    Porter2Stemmer::trim(word1);
    Porter2Stemmer::stem(word1);
    Porter2Stemmer::trim(word2);
    Porter2Stemmer::stem(word2);
    Word w1,w2;
    w1.setWord(word1);
    w2.setWord(word2);
    forward_list<Document> word1Docs=docParser.findWord(w1);
    forward_list<Document> word2Docs=docParser.findWord(w2);
    forward_list<Document>::iterator iter2;
    forward_list<Document>::iterator iter1;
    //cout<<endl<<"Here are the documents containing your search terms"<<endl;
    for (iter1= word1Docs.begin(); iter1 != word1Docs.end(); ++iter1) {
        finalDocs.push_back(*iter1);
        //cout<<iter1->getDocName()<<endl;
    }
    bool t=true;
    for (iter2= word1Docs.begin(); iter2 != word1Docs.end(); ++iter2) {
        for(int i = 0;i<finalDocs.size();i++){
            if(iter2->getDocName()==finalDocs[i].getDocName()){
                t=false;
            }
        }
        if(t==true){
            finalDocs.push_back(*iter2);
            //cout<<iter2->getDocName()<<endl;
        }
    }
    //cout<<"Enter another word to search for, or enter 1 to exit."<<endl;
}
void QueryEngine::oneWord(string wordToFind) {
    transform(wordToFind.begin(), wordToFind.end(), wordToFind.begin(), ::tolower);
    Porter2Stemmer::trim(wordToFind);
    Porter2Stemmer::stem(wordToFind);
    Word w1;
    w1.setWord(wordToFind);
    forward_list<Document> w1Docs=docParser.findWord(w1);
    forward_list<Document>::iterator iter1;
    //cout<<"Here are the documents containing your search terms"<<endl;
    for (iter1= w1Docs.begin(); iter1 != w1Docs.end(); ++iter1) {
        finalDocs.push_back(*iter1);
        //cout<<iter1->getDocName()<<endl;
    }
    //cout<<"Enter another word to search for, or enter 1 to exit."<<endl;
}
void QueryEngine::And(string word1, string word2) {
    transform(word1.begin(), word1.end(), word1.begin(), ::tolower);
    transform(word2.begin(), word2.end(), word2.begin(), ::tolower);
    Porter2Stemmer::trim(word1);
    Porter2Stemmer::stem(word1);
    Porter2Stemmer::trim(word2);
    Porter2Stemmer::stem(word2);
    Word w1,w2;
    w1.setWord(word1);
    w2.setWord(word2);
    forward_list<Document> word1Docs=docParser.findWord(w1);
    forward_list<Document> word2Docs=docParser.findWord(w2);
    forward_list<Document>::iterator iter2;
    forward_list<Document>::iterator iter1;
    //cout<<endl<<"Here are the documents containing your search terms"<<endl;
    for(iter1=word1Docs.begin();iter1!=word1Docs.end();++iter1) {
        for (iter2 = word2Docs.begin(); iter2 != word2Docs.end(); ++iter2) {
            if (iter1->getDocName()==iter2->getDocName()) {
                finalDocs.push_back(*iter1);
                //cout<<iter1->getDocName()<<endl;
            }
        }
    }
    //cout<<"Enter another word to search for, or enter 1 to exit."<<endl;
}
void QueryEngine::printResults() {
    sortResults();

    cout << endl << "Here are the documents containing your search terms" << endl;
    for (int i = 0; i < finalDocs.size()&&i<15; i++) {
        cout << i + 1 << ")" << finalDocs[i].getTitle() << " " << finalDocs[i].getTimesInBody() << endl;
    }
    printArticle();
    cout << "Enter another word to search for, or enter 1 to exit." << endl;
}
vector<string> QueryEngine::splitString(const string &str) {
    vector<string> output;
    string::size_type start = 0; // Where to start
    string::size_type last = str.find_first_of(" "); // Finds the first space

    // npos means that the find_first_of wasn't able to find what it was looking for
    // in this case it means it couldn't find another space so we are at the end of the
    // words in the string.
    while (last != string::npos)
    {
        // If last is greater then start we have a word ready
        if (last > start)
        {
            output.push_back(str.substr(start, last - start)); // Puts the word into a vector look into how the method substr() works
        }

        start = ++last; // Reset start to the first character of the next word
        last = str.find_first_of(" ", last); // This means find the first space and we start searching at the first character of the next word
    }

    // This will pickup the last word in the file since it won't be added to the vector inside our loop
    output.push_back(str.substr(start));
    return output;
}
void QueryEngine::clear() {
    finalDocs.clear();
}
void QueryEngine::sortResults() {
    sort(finalDocs.begin(),finalDocs.end());
}
void QueryEngine::printArticle() {
    int id;
    cout<<endl<<"Enter the number of the article you would like to print"<<endl;
    cin>>id;
    cout<<endl;
    documentParser docParser;
    unordered_set<string> authors;
    Document toAddToWord(0,0,0,"",authors);
    Word toAdd;
    simdjson::dom::parser parser;
    simdjson::dom::element doc;
    vector<string> fileNames = docParser.getAllFileNamesInFolder("C:\\Users\\leopa\\Downloads\\timing_demo_data_sets\\ds_02\\");
    list<string>::iterator iter;

    for(int i=2;i<fileNames.size()-1;i++) {

        doc = parser.load(fileNames[i]);
        toAddToWord.setDocName(fileNames[i]);
        toAdd.addDocument(toAddToWord);
        //printing out abstracts
        string_view abstractText;
        string realAbstract;
        if(fileNames[i]==finalDocs[id].getDocName()){
            for (auto abstract:doc["abstract"]) {
            abstractText = abstract["text"];
            realAbstract = (string) abstractText;

            list<string> abstractList = docParser.splitString(realAbstract);
            abstractList = docParser.removeStopWords(abstractList);
                for (iter = abstractList.begin(); iter != abstractList.end(); ++iter) {
                cout << *iter<<" ";
                i++;
                }
                break;
            }
        }
    }
}
