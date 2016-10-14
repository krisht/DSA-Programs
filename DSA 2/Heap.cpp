#include "Heap.h"
#include <climits>

using namespace std;

Heap::Heap(int capacity) {
    mapping = new HashTable(capacity);
    data.resize(capacity + 1);
    maxCapacity = capacity;
}

int Heap::insert(const string &id, int key, void *pv) {
    if ((size + 1) > maxCapacity)
        return 1;

    if (mapping->contains(id))
        return 2;

    size++;

    data[size].id = id;
    data[size].key = key;
    data[size].pData = pv;
    mapping->insert(data[size].id);
    if (size != 1)
        percolateUp(size);

    return 0;
}

int Heap::setKey(const string &id, int key) {
    bool *exists;
    Node *value = static_cast<Node *>(mapping->getPointer(id, exists));

    if (!exists)
        return 1;

    bool up;
    int oldKey = value->key;
    value->key = key;
    up = (key < oldKey);

    if (up)
        percolateUp(value->pos);
    else percolateDown(value->pos);

    return 0;
}

int Heap::remove(const string &id, int *key, void *ppData) {
    bool *exists;
    Node *value = static_cast<Node *> (mapping->getPointer(id, exists));
    if (*exists) {

    }
    if (key != nullptr)
        *key = value->key;
    setKey(id, INT_MIN);
    return deleteMin(nullptr, nullptr, ppData);
}

int Heap::deleteMin(string *id, int *key, void *ppData) {
    if (size == 0)
        return 1;

    mapping->remove(data[1].id);

    if (id != nullptr)
        *key = data[1].key;

    if (key != nullptr)
        *key = data[1].key;

    if (ppData != nullptr)
        ppData = data[1].pData;

    data[1] = data[size--];
    percolateDown(1);
    return 0;
}

void Heap::percolateUp(int posCur) {
    Node value = data[posCur];

    while (posCur > 1) {
        if (value < data[posCur / 2]) {
            data[posCur] = data[posCur / 2];
            data[posCur].pos = posCur;
            if (!mapping->setPointer(data[posCur].id, &data[posCur])) {
                cout << "Error in percolate up!" << endl;
                return;
            }
            posCur /= 2;
        }
        else
            break;
    }

    data[posCur] = value;
    data[posCur].pos = posCur;
    mapping->setPointer(value.id, &data[posCur]);
}

void Heap::percolateDown(int posCur) {
    Node value = data[posCur];
    int smallerKey = 1;
    while (posCur < size) {
        if (2 * posCur > size)
            break;
        else if (2 * posCur + 1 > size)
            smallerKey = 2 * posCur;
        else smallerKey = (data[2 * posCur] > data[2 * posCur + 1]) ? (2 * posCur + 1) : (2 * posCur);

        if (value > data[smallerKey]) {
            data[posCur] = data[smallerKey];
            data[posCur].pos = posCur;
            if (!mapping->setPointer(data[posCur].id, &data[posCur])) {
                cout << "Error in percolate down!" << endl;
                return;
            }
            posCur = smallerKey;
        }
        else break;

        data[posCur] = value;
        data[posCur].pos = posCur;
        mapping->setPointer(value.id, &data[posCur]);

    }
}