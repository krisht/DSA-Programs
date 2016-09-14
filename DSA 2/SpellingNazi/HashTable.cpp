#include "HashTable.h"

#define loadFactor 0.5

using namespace std;

HashTable::HashTable(int size) {
    capacity = getPrime(size);
    data.resize(capacity);
}

unsigned int HashTable::getPrime(int size) {
    static vector<unsigned int> primes = {53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 24593, 49157, 98317, 196613,
                                          393241, 786433, 1572869, 3145739, 786433, 1572869, 3145739, 6291469, 12582917,
                                          25165843, 50331653, 100663319, 201326611, 402653189, 805306457, 1610612741};
    for (int kk = 0; kk < primes.size(); kk++) 
        if (primes[kk] * loadFactor > size)
            return primes[kk];
    return primes[primes.size() - 1];
}

bool HashTable::insert(const string &key, void *pv) {
    if (contains(key))
        return false;

    int pos = hash(key);
    int tempPos = pos;

    if (data[pos].isDeleted)
        while (!data[pos = ++pos % data.capacity()].isDeleted && pos != tempPos);

    data[pos].isOccupied = true;
    data[pos].isDeleted = false;
    data[pos].key = key;
    data[pos].pv = pv;
    filled++;

    if ((float) filled / (float) capacity > loadFactor)
        return rehash();
}

bool HashTable::rehash() {
    capacity = getPrime(capacity);
    vector<HashItem> temp = data;

    data.clear();
    data.resize(capacity);

    if (data.size() != capacity)
        return false;

    filled = 0;

    for (int kk = 0; kk < temp.size(); kk++)
        if (!temp[kk].isDeleted)
            insert(temp[kk].key, temp[kk].pv);

    return true;
}


int HashTable::findPos(const string &key) {
    int pos = hash(key);
    int tempPos = pos;

    if ((data[pos].key).compare(key) == 0)
        return pos;
    else
        while (data[pos = ++pos % data.capacity()].isOccupied && data[pos].key.compare(key) != 0 && pos != tempPos);

    return (data[pos].key.compare(key) == 0 && !data[pos].isDeleted) ? pos : -1;
}

bool HashTable::remove(const string &key) {
    int pos = findPos(key);
    if (pos == -1)
        return false;
    data[pos].isDeleted = true;
    filled--;
    return true;
}

bool HashTable::contains(const string &key) {
    return (findPos(key) != -1);
}

unsigned int HashTable::hash(const string &key) {
    //Hash function from http://stackoverflow.com/a/629127
    unsigned h = 0; //salt definition
    const char *s = key.c_str();
    while (*s)
        h = h * 101 + (unsigned) *s++;
    return h % data.capacity();
}

void *HashTable::getPointer(const string &key, bool *b) {
    int pos = findPos(key);
    if (pos != -1) {
        *b = true;
        return data[pos].pv;
    }
    *b = false;
    return NULL;
}

bool HashTable::setPointer(const string &key, void *pv) {
    int pos = findPos(key);
    if (pos != -1)
        data[pos].pv = pv;
    else return false;
    return true;
}


