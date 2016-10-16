/**
 * Krishna Thiyagarajan
 * DSA II - Project #2
 * SpellingNazi.h
 * Defines data members and member functions
 * for a simple spell checker
 */

#ifndef SPELLINGNAZI_SPELLINGNAZI_H
#define SPELLINGNAZI_SPELLINGNAZI_H

#include "HashTable.h"
#include <fstream>
#include <algorithm>

class SpellingNazi {
public:
    SpellingNazi();

    ~SpellingNazi();

    void checkFile();

private:
    HashTable *dict;

    void loadWords();

    void process(string &line, ofstream &writeTo);

    int firstValidCharPos(string &line, int init);

    void toLower(string &str);

    bool isValidChar(int charInt);

};

#endif //SPELLINGNAZI_SPELLINGNAZI_H
