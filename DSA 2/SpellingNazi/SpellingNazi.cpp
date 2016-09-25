#include "SpellingNazi.h"

#define initSize 50000 //Reasonable initial size for start of program

using namespace std;

/**
 * Constructor defining dictionary
 */
SpellingNazi::SpellingNazi() {
    dict = new HashTable(initSize);
}

/**
 * Destructor deleting dictionary
 */
SpellingNazi::~SpellingNazi() {
    delete (dict);
}

/**
 * Loads words into dictionary given user input
 */
void SpellingNazi::loadWords() {
    cout << "Dictionary: ";

    string dictFName; //Dictionary file name
    cin >> dictFName;

    ifstream dictStream(dictFName.c_str()); //Dictionary file stream

    if (!dictStream) {
        cerr << "Dictionary not found: " << dictFName << endl;
        exit(-1);
    }

    clock_t t1 = clock();
    string input;
    dictStream >> input; // Initial read of dictionary

    while (!dictStream.eof()) {
        toLower(input);
        dict->insert(input); //Inserts word into dictionary
        dictStream >> input; //Reads next word
    }

    clock_t t2 = clock();
    double diff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;
    cout << "Total time (in seconds) to load dictionary: " << diff << endl;
    dictStream.close(); //Closes stream
}

/**
 * Spell checks files against dictionary given user input
 */
void SpellingNazi::checkFile() {
    loadWords();                //Loads words into dictionary
    cout << "Input: ";
    string inFileName;
    cin >> inFileName;            //Document to be spell checked

    ifstream inStream(inFileName.c_str()); //Stream to document
    if (!inStream) {
        cerr << "Input not found: " << inFileName << endl;
        exit(-1);
    }

    cout << "Output: ";
    string outFileName;
    cin >> outFileName;    //Output document of results
    ofstream outStream;
    outStream.open(outFileName);    //Stream to output document

    string line;
    clock_t t1 = clock();

    do {
        getline(inStream, line);
        process(line, outStream); //Spell checks each line from input stream
    } while (!inStream.eof());

    clock_t t2 = clock();

    double diff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;
    cout << "Total time (in seconds) to check document: " << diff << endl;
    inStream.close(); //Closes input and output streams
    outStream.close();
}

/**
 * Processes each line and writes result to writer stream
 * @param line   Line to process
 * @param writer Stream to write output to
 */
void SpellingNazi::process(string &line, ofstream &writer) {
    static int lineNum = 0; //Line number counter
    lineNum++;
    toLower(line);
    int start;
    string word;

    start = firstValidCharPos(line, 0); //Finds first valid character in the string
    bool hasNum = isdigit(line[start]); //Checks if character is a number
    for (int kk = start; kk <= line.size(); kk++) {
        if (start == -1) //If no start is found, skips line. All characters are invalid
            break;
        hasNum = hasNum || isdigit(line[kk]);
        if (!isValidChar(line[kk])) { //If character is found, parses word starting at that line
            word = line.substr(start, kk - start);

            if (word.size() > 20)
                writer << "Long word at line " << lineNum << ", starts: " << word.substr(0, 20) << endl;
            else if (!hasNum && !dict->contains(word))
                writer << "Unknown word at line " << lineNum << ": " << word << endl;

            kk = start = firstValidCharPos(line, kk); //Continues parsing line at the next valid character
            hasNum = isdigit(line[start]); //Checks if first character is a number
        }
    }

}

/**
 * Finds first valid word character starting from init in a line
 * @param  line Line to find valid word character in
 * @param  init Starting position to find valid word character
 * @return      Position of valid character. -1 if not found
 */
int SpellingNazi::firstValidCharPos(string &line, int init) {
    for (int kk = init; kk < line.size(); kk++)
        if (isValidChar(line[kk]))
            return kk;
    return -1;
}

/**
 * Converts string to lowercase
 * @param str String to convert
 */
void SpellingNazi::toLower(string &str) {
    for (int kk = 0; kk < str.size(); kk++)
        str[kk] = tolower(str[kk]);
}

/**
 * Checks if given character is a valid word character
 * @param  charInt ASCII character value to check
 * @return         True if valid character. False if not
 */
bool SpellingNazi::isValidChar(int charInt) {
    return (isalpha(charInt) || isdigit(charInt) || charInt == 45 || charInt == 92 || charInt == 39);
}