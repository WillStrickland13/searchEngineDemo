#ifndef SEARCH_ENGINE_HASHTABLE_H
#define SEARCH_ENGINE_HASHTABLE_H
#include <list>
#include <functional>
#include <iostream>
#include <algorithm>
#include<bits/stdc++.h>

using namespace std;
template <typename T>
class HashTable {
private:
    int buckets;
    list<T> *table;
public:
    HashTable(int size){
        this->buckets=size;
        table=new list<T>[buckets];
    }
//    int hashFunc(T value){
//        return value%buckets;
//    }
    int hashFunc(string word){
        int sum = 0;
        for (int k = 0; k < word.length(); k++)
            sum = sum + int(word[k]);
        return  sum % buckets;
    }
    void insertItem(T value){
        int index=hashFunc(value);
        table[index].push_back(value);
    }
    void deleteItem(T key){
        int index=hashFunc(key);
        list<int>::iterator iter;
        for(iter=table[index].begin();iter!=table[index].end();iter++){
            if(iter==key)
                break;
        }
        if (iter != table[index].end())
            table[index].erase(iter);
    }
    void displayHash(){
        for (int i = 0; i < buckets; i++) {
            cout << i;
            for (auto x : table[i])
                cout << " --> " << x;
            cout << endl;
        }
    }
    bool hasValue(T key){
        int index=hashFunc(key);
        list<string>::iterator iter;
        for(iter=table[index].begin();iter!=table[index].end();iter++){
            if(*iter==key)
                return true;
        }

        return false;
    }
};


#endif //SEARCH_ENGINE_HASHTABLE_H
