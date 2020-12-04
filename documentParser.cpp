#include "documentParser.h"
list<string> documentParser::removeStopWords(list<string> words) {
    list<string>::iterator iter;
    for(iter=words.begin();iter!=words.end();++iter){
        if(stopWords.find(*iter)!=stopWords.end()){
            words.erase(iter);
        }
    }
    return words;

}
forward_list<Document> documentParser::findWord(Word w) {
    return tree.printDocumentNames(w);
}
vector<string> documentParser::getAllFileNamesInFolder(string folder) {
    vector<string> names;
    DIR* dirp = opendir(folder.c_str());
    int i=0;
    struct dirent * dp;
    while ((dp = readdir(dirp)) != NULL) {
        string fullPath=folder;
        fullPath+=dp->d_name;
        names.push_back(fullPath);
        //cout<<fullPath<<endl;
    }
    closedir(dirp);
    return names;
}
void documentParser::fillStopWords(string fileName) {
    ifstream file(fileName);
    string next;
    char n[50];
    while(!file.eof()){
        file>>next;
        stopWords.insert(next);
        file>>next;//remove \n
    }
}

list<string> documentParser::splitString(const string &str)
{
    list<string> output;
    string::size_type start = 0; // Where to start
    string::size_type last = str.find_first_of(" "); // Finds the first space

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
void documentParser::printWithNoStopWords(const list<string> &words) {
    for (auto const& i: words) {
        cout << i << " ";
    }
}
void documentParser::loadTree(string fileName) {

    documentParser docParser;
    docParser.fillStopWords("stopWords.txt");
    unordered_set<string> authors;
    Document toAddToWord(0,0,0,"",authors);
    Word toAdd;
    simdjson::dom::parser parser;
    simdjson::dom::element doc;
    vector<string> fileNames = docParser.getAllFileNamesInFolder(fileName);
    list<string>::iterator iter;

    for(int i=2;i<fileNames.size()-1;i++) {

        doc = parser.load(fileNames[i]);
        toAddToWord.setDocName(fileNames[i]);
        toAdd.addDocument(toAddToWord);
        //getting title
        string_view Title = doc["metadata"]["title"];
        string realTitle = (string) Title;
        toAddToWord.setTitle(realTitle);
        //printing out Authors first and last names
        string_view first, last;
        string realfirst, reallast;
        for (auto Authors:doc["metadata"]["authors"]) {
            first = Authors["first"];
            realfirst = (string) first;
            last = Authors["last"];
            reallast = (string) last;
        }

        //printing out abstracts
        string_view abstractText;
        string realAbstract;
        for (auto abstract:doc["abstract"]) {
            abstractText = abstract["text"];
            realAbstract = (string) abstractText;

            list<string> abstractList = docParser.splitString(realAbstract);
            abstractList=docParser.removeStopWords(abstractList);

            for (iter = abstractList.begin(); iter != abstractList.end(); ++iter) {
                transform(iter->begin(), iter->end(), iter->begin(), ::tolower);
                Porter2Stemmer::trim(*iter);
                Porter2Stemmer::stem(*iter);
                toAdd.setWord(*iter);
                tree.addToAVLTree(toAdd,toAddToWord);
            }
        }

        //printing out body texts
        string_view bodyText;
        string bodyT;
        for (auto body:doc["body_text"]) {
            //get body text string
            bodyText = body["text"];
            bodyT = (string) bodyText;

            //remove stop words
            list<string> bodyList = docParser.splitString(bodyT);
            bodyList = docParser.removeStopWords(bodyList);

            //trim and stem
            for (iter = bodyList.begin(); iter != bodyList.end(); ++iter) {
                transform(iter->begin(), iter->end(), iter->begin(), ::tolower);
                Porter2Stemmer::trim(*iter);
                Porter2Stemmer::stem(*iter);
                toAdd.setWord(*iter);
                tree.addToAVLTree(toAdd,toAddToWord);
            }
        }
    }
}