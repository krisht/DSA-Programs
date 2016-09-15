#ifndef SPELLINGNAZI_SPELLINGNAZI_H
#define SPELLINGNAZI_SPELLINGNAZI_H

#include "HashTable.h"
#include <fstream>
#include <algorithm>


/**
 * Spell checker class declaration
 */
class SpellingNazi {
public:

	/**
	 * Constructor for object
	 */
    SpellingNazi();

    /**
     * Destructor for object
     */
    ~SpellingNazi();

    /**
     * Initiates program
     */
    void checkFile();
private:
    HashTable* dict; //HashTable used to store words

    /**
     * Loads words from dictionary
     */
    void loadWords();

    /**
     * Parses a line and checks each word in it
     * @param line    Ref. to the string to be parsed
     * @param writeTo Output stream to output file
     */
    void process(string &line, ofstream &writeTo);

    /**
     * Finds the position of delimiters in a string
     * @param  line string to find delimiters in
     * @param  init starting position to find delimiters
     * @return      position of delimiter
     */
    int splitPos(string &line, int init);

    /**
     * Converts a string into lowercase
     * @param str string to convert to lowercase
     */
    void toLower(string &str);

};

#endif //SPELLINGNAZI_SPELLINGNAZI_H
