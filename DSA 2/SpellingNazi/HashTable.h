#ifndef SPELLINGNAZI_HASHTABLE_H
#define SPELLINGNAZI_HASHTABLE_H

#include <vector>
#include <iostream>
#include <string>

using namespace std;

class HashTable {
public:
    /**
     * Constructor with default size set to 0
     */
    HashTable(int size = 0);
    
    /**
     * Insert specified key into HashTable
     * If Optional pointer is provided,
     * associate pointer with key
     * @param  key string to be inserted
     * @param  pv  optional pointer
     * @return     true if successful false if not
     */
    bool insert(const string &key, void *pv = NULL);
    
    /**
     * Check if specified key is in HashTable
     * @param  key string to be checked
     * @return     true if found, false if not
     */
    bool contains(const string &key);
    
    /**
     * Get pointer associated with specified key
     * @param  key string to be checked
     * @param  b   optional boolean
     * @return     pointer associated with key
     */
    void *getPointer(const string &key, bool *b = NULL);
    
    /**
     * Setter for optional pointer
     * @param  key string to be found
     * @param  pv  associative pointer
     * @return     true if successful, false if not
     */
    bool setPointer(const string &key, void *pv);
    
    /**
     * Removes key from HashTable
     * @param  key string to be deleted from HashTable
     * @return     true if successful, false if not
     */
    bool remove(const string &key);
    
private:
    /**
     * Class definition for HashItem
     */
    class HashItem {
    public:
        string key;
        bool isOccupied;
        bool isDeleted;
        void *pv;
    };

    unsigned int capacity; //current capacity of HashTable
    int filled; //Amount of slots filled in HashTable
    vector<HashItem> data; //Vector containing HashTable's data
    
    /**
     * Hashing function
     * @param  key string to be hashed
     * @return     unsigned integer representing hash value
     */
    unsigned int hash(const string &key);

    /**
     * Finds position of key in HashTable
     * @param  key string to be searched
     * @return     integer position or -1 if not found
     */
    int findPos(const string &key);
    
    /**
     * Rehashing function if loadFactor is exceeded
     * @return true if successful, false if not
     */
    bool rehash();

    /**
     * Gets prime number that is appropriate for size
     * @param  size size that HashTable will hold
     * @return      prime number
     */
    unsigned int getPrime(int size);
};

#endif //SPELLINGNAZI_HASHTABLE_H
