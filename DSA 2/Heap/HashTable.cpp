#include "HashTable.h"

#define loadFactor 0.5 //Load factor of half. Can be changed if needed

using namespace std;

HashTable::HashTable(int size) {
    capacity = getPrime(size); //Finds capacity of vector representing HashTable
    data.resize(capacity);
}

/**
 * Gets a prime given a size that satisfies global loadFactor
 * @param  size Size of expected HashTable
 * @return      Capacity of HashTable
 */
unsigned int HashTable::getPrime(int size) {
    static vector<unsigned int> primes = {53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 24593, 49157, 98317, 196613,
                                          393241, 786433, 1572869, 3145739, 786433, 1572869, 3145739, 6291469, 12582917,
                                          25165843, 50331653, 100663319, 201326611, 402653189, 805306457, 1610612741};

    for (int kk = 0; kk < primes.size(); kk++)
        if (primes[kk] * loadFactor > size)
            return primes[kk];
    return primes[primes.size() - 1];
}

/**
 * Inserts a key into HashTable
 * @param  key String representing key
 * @param  pv  Optional pointer attributed to key
 * @return     True if insert was successful, else false
 */
bool HashTable::insert(const string &key, void *pv) {
    if(key.compare("") == 0)
        return false;

    int pos = hash(key);

    if (data[pos].isOccupied) //If pos is occupied linear probes
        for (int kk = 1; kk < data.size(); kk++)
            if (!data[modPosition(pos + kk)].isOccupied) {
                pos = modPosition(pos + kk);
                break;
            }


    //Sets variables appropriately
    data[pos].isOccupied = true;
    data[pos].isDeleted = false;
    data[pos].key = key;
    data[pos].pv = pv;
    filled++;

    if (((double) filled / capacity) >= loadFactor) //If loadFactor is exceeded, rehashes
        return rehash();

    return true;
}

/**
 * Rehashes HashTable and expands it
 * @return true on success
 */
bool HashTable::rehash() {
    capacity = getPrime(capacity); //gets new capacity
    vector<HashItem> temp = data;
    data.clear();//removes all data from HashTable

    data.resize(capacity); //Resizes table
    if (data.size() != capacity)
        return false;

    filled = 0; //Resets filled

    for (int kk = 0; kk < temp.size(); kk++) //Adds all item in old table to new rehashed table
        if (!temp[kk].isDeleted)
            insert(temp[kk].key, temp[kk].pv);

    return true;
}

/**
 * Finds position of key in the HashTable
 * @param  key String to be searched for
 * @return     Position of key if found. If not, return -1
 */
int HashTable::findPos(const string &key) {

    int pos = hash(key);

    if (data[pos].key.compare(key) == 0)
        return pos;
    else
        for (int kk = 1; kk < data.size(); kk++) //Linear probes and looks for key
            if (data[modPosition(kk + pos)].isOccupied && data[modPosition(kk + pos)].key.compare(key) == 0)
                return modPosition(kk + pos);
            else if (!data[modPosition(kk + pos)].isOccupied) //Breaks if there is a break HashTable
                break;
    return -1;
}

/**
 * Removes given key from HashTable
 * @param  key String to remove from HashTable
 * @return     True if successful, false if not
 */
bool HashTable::remove(const string &key) {
    int pos = findPos(key);
    if (pos == -1) //Key not found. Can't be removed
        return false;

    data[pos].isDeleted = true; //Key found. Lazily removes key
    data[pos].key = "";
    return true;
}

/**
 * Checks if HashTable contains certain key
 * @param  key Key to find
 * @return     true if found, false if not
 */
bool HashTable::contains(const string &key) {
    return (findPos(key) != -1);
}

/**
 * Generates Hash value given a string key
 * @param  key String that represents key
 * @return     Hash value of key
 */
unsigned int HashTable::hash(const string &key) {
    //Hash function from http://stackoverflow.com/a/629127
    unsigned h = 0; //salt definition
    const char *s = key.c_str();
    while (*s)
        h = h * 101 + (unsigned) *s++;
    return modPosition(h);
}

/**
 * Gets a pointer associated with key
 * @param  key Key to find the pointer of
 * @param  b   Boolean representing success of method
 * @return     Void poitner associated with key
 */
void *HashTable::getPointer(const string &key, bool &b) {
    int pos = findPos(key);
    if (pos != -1) {
        b = true; //Pointer is found
        return data[pos].pv;
    }
    else{
        b = false; //Pointer is not found
        return nullptr;
    }

}

/**
 * Sets pointer associated with key
 * @param  key Key to associate pointer with
 * @param  pv  Pointer to associate with key
 * @return     True on success, else false
 */
bool HashTable::setPointer(const string &key, void *pv) {
    int pos = findPos(key);
    if (pos != -1) {
        data[pos].pv = pv; //Key is found. Pointer is set
        return true;
    }
    else{
        return false;
    } //Key is not found
}

/**
 * Generates modulus number
 * @param  num Number to find modulus of
 * @return     Modulus number of given number
 */
unsigned int HashTable::modPosition(int num) {
    return num % capacity;
}
