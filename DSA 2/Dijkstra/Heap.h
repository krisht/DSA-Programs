/**
 * Krishna Thiyagarajan
 * DSA II - Project #2
 * Heap.h
 * Defines data members and member functions for a Heap data structure
 */

#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include <string>
#include "HashTable.h"

using namespace std;

class Heap {

public:
    Heap(int capacity);

    int insert(const string &id, int key, void *pv = nullptr);

    int setKey(const string &id, int key);

    int remove(const string &id, int *key = nullptr, void *ppData = nullptr);

    int deleteMin(string *id = nullptr, int *key = nullptr, void *ppData = nullptr);

private:
    class Node {
    public:
        string id = "";
        int key = 0;
        void *pData = nullptr;
        int pos = 0;

        bool operator<(const Node &b) {
            return key < b.key;
        }

        bool operator>(const Node &b) {
            return key > b.key;
        }
    };

    HashTable *heapMap;
    vector<Node> data;

    void bubbleUp(int posCur);

    void bubbleDown(int posCur);

    int size = 0;
    int maxCapacity;

};


#endif //HEAP_H