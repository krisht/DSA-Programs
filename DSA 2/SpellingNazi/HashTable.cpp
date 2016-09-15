#include "HashTable.h"

#define loadFactor 0.5

using namespace std;

HashTable::HashTable(int size) {
    capacity = getPrime(size);
    data.resize(capacity);
}

unsigned int HashTable::getPrime(int size) {
    //List of good HashTable lengths
    static vector<unsigned int> primes = {53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 24593, 49157, 98317, 196613,
                                          393241, 786433, 1572869, 3145739, 786433, 1572869, 3145739, 6291469, 12582917,
                                          25165843, 50331653, 100663319, 201326611, 402653189, 805306457, 1610612741};
    for (int kk = 0; kk < primes.size(); kk++) 
        if (primes[kk] * loadFactor > size)
            return primes[kk];
    return primes[primes.size() - 1];
}

bool HashTable::insert(const string &key, void *pv) {
    if (contains(key)) //No point in inserting again. Just takes up more space
        return false;

    int pos = hash(key);//computes HashValue and position
    int tempPos = pos;

    if (data[pos].isDeleted) //Increases position if collision until no collision
        while (!data[pos = ++pos % data.capacity()].isDeleted && pos != tempPos);

    /**
     * Inserts key
     */
    data[pos].isOccupied = true;
    data[pos].isDeleted = false;
    data[pos].key = key;
    data[pos].pv = pv;
    filled++;       // increments filled value

    if ((float) filled / (float) capacity > loadFactor) //rehashes if loadFactor is exceeded
        return rehash();
}

bool HashTable::rehash() {
    capacity = getPrime(capacity); //gets new HashTable array size
    vector<HashItem> temp = data; //stores current data in temp variable

    data.clear(); //clears current data
    data.resize(capacity); //intializes size for new hashtable

    if (data.size() != capacity) //if size and capacity aren't equal, something messed up
        return false;

    filled = 0; //resets filled to 0

    for (int kk = 0; kk < temp.size(); kk++) //goes through temp and adds all new values into table
        if (!temp[kk].isDeleted)
            insert(temp[kk].key, temp[kk].pv);

    return true; //completed successfully
}


int HashTable::findPos(const string &key) {
    int pos = hash(key);
    int tempPos = pos;

    /**
     * Finds position where key is located
     */
    if ((data[pos].key).compare(key) == 0)
        return pos;
    else
        while (data[pos = ++pos % data.capacity()].isOccupied && data[pos].key.compare(key) != 0 && pos != tempPos);

    return (data[pos].key.compare(key) == 0 && !data[pos].isDeleted) ? pos : -1; //if not found, returns -1
}

bool HashTable::remove(const string &key) {
    int pos = findPos(key);
    if (pos == -1)      //not found in the table
        return false;
    data[pos].isDeleted = true; //if found, sets it as deleted
    filled--; //decreased filled
    return true; 
}

bool HashTable::contains(const string &key) {
    return (findPos(key) != -1); // if found, then table contains key
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
    if (pos != -1) { //if found, returns pointer and sets *b to true
        *b = true;
        return data[pos].pv;
    }
    *b = false; //if not, sets b to false and returns null pointer
    return NULL;
}

bool HashTable::setPointer(const string &key, void *pv) {
    int pos = findPos(key);
    if (pos != -1)              // if found, sets pointer to pv
        data[pos].pv = pv;
    else return false;          // if not, op failed. returns false
    return true;
}


