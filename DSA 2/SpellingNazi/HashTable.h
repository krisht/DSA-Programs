#ifndef SPELLINGNAZI_HASHTABLE_H
#define SPELLINGNAZI_HASHTABLE_H

#include <vector>
#include <iostream>
#include <string>

using namespace std;

class HashTable {
public:
    HashTable(int size = 0);
    bool insert(const string &key, void *pv = NULL);
    bool contains(const string &key);
    void *getPointer(const string &key, bool *b = NULL);
    bool setPointer(const string &key, void *pv);
    bool remove(const string &key);
    void printTable();

private:
    class HashItem {
    public:
        string key;
        bool isOccupied;
        bool isDeleted;
        void *pv;
    };
    unsigned int capacity;
    int filled;
    vector<HashItem> data;
    unsigned int hash(const string &key);
    int findPos(const string &key);
    bool rehash();
    unsigned int getPrime(int size);
};

#endif //SPELLINGNAZI_HASHTABLE_H
