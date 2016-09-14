//
// Created by krishna on 9/13/16.
//

#ifndef SPELLINGNAZI_HASHTABLE_H
#define SPELLINGNAZI_HASHTABLE_H

#include <vector>
#include <iostream>
#include <string>

using namespace std;

class HashTable {

public:

    // The constructor initializes the hash table.
    // Uses getPrime to choose a prime number at least as large as
    // the specified size for the initial size of the hash table.
    HashTable(int size = 0);

    // Insert the specified key into the hash table.
    // If an optional pointer is provided,
    // associate that pointer with the key.
    // Returns 0 on success,
    // 1 if key already exists in hash table,
    // 2 if rehash fails.
    bool insert(const string &key, void *pv = NULL);

    // Check if the specified key is in the hash table.
    // If so, return true; otherwise, return false.
    bool contains(const string &key);

    // Get the pointer associated with the specified key.
    // If the key does not exist in the hash table, return NULL.
    // If an optional pointer to a bool is provided,
    // set the bool to true if the key is in the hash table,
    // and set the bool to false otherwise.
    void *getPointer(const string &key, bool *b = NULL);

    // Set the pointer associated with the specified key.
    // Returns 0 on success,
    // 1 if the key does not exist in the hash table.
    bool setPointer(const string &key, void *pv);

    // Delete the item with the specified key.
    // Returns true on success,
    // false if the specified key is not in the hash table.
    bool remove(const string &key);

private:

    // Each item in the hash table contains:
    // key - a string used as a key.
    // isOccupied - if false, this entry is empty,
    //              and the other fields are meaningless.
    // isDeleted - if true, this item has been lazily deleted.
    // pv - a pointer related to the key;
    //      NULL if no pointer was provided to insert.
    class HashItem {
    public:
        string key;
        bool isOccupied;
        bool isDeleted;
        void *pv;
    };

    unsigned int capacity; // The current capacity of the hash table.
    int filled; // Number of occupied items in the table.

    vector<HashItem> data; // The actual entries are here.

    // The hash function.
    unsigned int hash(const string &key);

    // Search for an item with the specified key.
    // Return the position if found, -1 otherwise.
    int findPos(const string &key);

    // The rehash function; makes the hash table bigger.
    // Returns true on success, false if memory allocation fails.
    bool rehash();

    // Return a prime number at least as large as size.
    // Uses a precomputed sequence of selected prime numbers.
    unsigned int getPrime(int size);
};



#endif //SPELLINGNAZI_HASHTABLE_H
