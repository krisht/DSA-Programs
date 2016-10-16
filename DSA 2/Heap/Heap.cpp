/**
 * Krishna Thiyagarajan
 * DSA II - Project #2
 * Heap.cpp
 * Implements all data members and member functions defined in Heap.h
 */

#include "Heap.h"
#include <climits>

using namespace std;

Heap::Heap(int capacity) {
    heapMap = new HashTable(capacity);
    data.resize(capacity + 1);
    maxCapacity = capacity;
}

/**
 * Inserts a node with parameters into heap
 * @param  id  String id of the node
 * @param  key Integer key of the node
 * @param  pv  Pointer associated with node
 * @return     Success of operation
 */
int Heap::insert(const string &id, int key, void *pv) {
    if (size + 1 > maxCapacity) //Returns 1 in the case that overflow occurs
        return 1;
    if (heapMap->contains(id))  //Returns 2 in the case that the id is already in table
        return 2;

    //Assigns attributes
    data[++size].id = id;
    data[size].key = key;
    data[size].pData = pv;
    heapMap->insert(data[size].id); //Inserts into the HashTable

    if (size != 1)
        bubbleUp(size); //Bubble's up new node

    return 0;
}

/**
 * Sets integer key of specified node
 * @param  id  Node's id
 * @param  key Key to set
 * @return     returns 0 on success
 */
int Heap::setKey(const string &id, int key) {
    bool exists;
    Node *value = static_cast<Node *>(heapMap->getPointer(id, exists)); //Casts pointer to node
    if (!exists)
        return 1;

    int oldKey = value->key;
    value->key = key;
    bool upOrDown = key < oldKey; //Percolate up or down
    
    if (upOrDown)
        bubbleUp(value->pos);
    else bubbleDown(value->pos);
    return 0;
}

/**
 * Removes item from heap given data related to node
 * @param  id     id to remove
 * @param  key    key to remove
 * @param  ppData Associated data to removes
 * @return        1 on failure
 */
int Heap::remove(const string &id, int *key, void *ppData) {
    bool exists;
    Node *value = static_cast<Node *>(heapMap->getPointer(id, exists));
    if (exists) {
        if (key != nullptr)
            *key = value->key;
        setKey(id, INT_MIN); // Sets id to minimum value for deletion with deleteMin
        return deleteMin(nullptr, nullptr, ppData);
    }
    return 1;
}

/**
 * Deletes minimum element from Heap
 * @param  id     String id associated with node
 * @param  key    Key associated with node
 * @param  ppData Pointer associated with node
 * @return        0 on success
 */
int Heap::deleteMin(string *id, int *key, void *ppData) {
    if (size == 0)
        return 1;
    heapMap->remove(data[1].id);
    if (id != nullptr)
        *id = data[1].id;
    if (key != nullptr)
        *key = data[1].key;
    if (ppData != nullptr)
        ppData = data[1].pData;
    data[1] = data[size--];
    bubbleDown(1);
    return 0;
}

/**
 * Bubbles up a node given it's current position
 * @param posCur Current position
 */
void Heap::bubbleUp(int posCur) {
    Node value = data[posCur];
    while (posCur > 1) {
        if (value < data[posCur / 2]) {
            data[posCur] = data[posCur / 2];
            data[posCur].pos = posCur;
            if (!heapMap->setPointer(data[posCur].id, &data[posCur])) {
                cout << "Error, percolate up went wrong" << endl;
                return;
            }
            posCur /= 2;
        } else break;
    }
    data[posCur] = value;
    data[posCur].pos = posCur;
    heapMap->setPointer(value.id, &data[posCur]);
}

/**
 * Bubbles down given
 * @param posCur Current position of node in Heap
 */
void Heap::bubbleDown(int posCur) {
    Node value = data[posCur];
    int smallerKey = 1; // the position of the child node with the smaller key value. Or the position of the child node that exists
    while (posCur < size) {
        if (2 * posCur > size) // Edge case #1: There are no children, end percolation
            break;
        else if (2 * posCur + 1 > size) //Edge case #2: There is no right node, only compare with the left node
            smallerKey = 2 * posCur;
        else
            smallerKey = (data[2 * posCur] > data[2 * posCur + 1]) ? (2 * posCur + 1) : (2 *
                                                                                         posCur); //Find the position of the smaller node

        if (value > data[smallerKey]) { //Compare against smaller node
            data[posCur] = data[smallerKey];
            data[posCur].pos = posCur;
            if (!heapMap->setPointer(data[posCur].id, &data[posCur])) {
                cout << "Error, percolate down went wrong" << endl;
                return;
            }
            posCur = smallerKey;
        }
        else break;
    }
    data[posCur] = value;
    data[posCur].pos = posCur;
    heapMap->setPointer(value.id, &data[posCur]);
}