#ifndef HEAP_HASHTABLE_H
#define HEAP_HASHTABLE_H

#include <vector>
#include <iostream>
#include <string>

using namespace std;

class HashTable {
public:
    HashTable(int size = 0);

    bool insert(const string &key, void *pv = nullptr);

    bool contains(const string &key);

    void *getPointer(const string &key, bool &b);

    bool setPointer(const string &key, void *pv);

    bool remove(const string &key);

    unsigned int modPosition(int num);

private:
    class HashItem {
    public:
        string key = "";
        bool isOccupied = false;
        bool isDeleted = true;
        void *pv = nullptr;
    };

    unsigned int capacity = 0;
    int filled = 0;
    vector<HashItem> data;

    unsigned int hash(const string &key);

    int findPos(const string &key);

    bool rehash();

    unsigned int getPrime(int size);
};

#endif //HEAP_HASHTABLE_H
