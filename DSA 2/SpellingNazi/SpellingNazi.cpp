#include "SpellingNazi.h"
#define initSize 50000

using namespace std;

SpellingNazi::SpellingNazi() {
    dict = new HashTable(initSize); //Intializes HashTable to inital size of 50k
}

SpellingNazi::~SpellingNazi() {
    delete (dict); //Deletes HashTable to clean up program
}

void SpellingNazi::loadWords() {
    cout << "Dict. Name: ";
    string dictFName;
    cin >> dictFName;
    ifstream dictStream(dictFName.c_str()); //Input file stream initialized to the dictionary

    /**
     * If not found, return error and exit
     */
    if (!dictStream) {
        cerr << "File not found: " << dictFName << endl;
        exit(1);
    }


    /**
     * Read from dictionary and load words to HashTable
     */
    string input;
    dictStream >> input;
    while(!dictStream.eof()){
        toLower(input);
        dict->insert(input);
        dictStream >> input;
    }

    dictStream.close(); //Safely close dictioanry file
}

void SpellingNazi::checkFile() {
    loadWords();

    cout << "Input file: ";
    string inputFName;
    cin >> inputFName;
    ifstream inStream(inputFName.c_str()); //Input file stream initalized to file needing spell checking

    if (!inStream) {
        cerr << "File not found: " << inputFName << endl;
        exit(1);
    }

    cout << "Output file: ";
    string outputFName;
    cin >> outputFName; 
    ofstream outStream;

    outStream.open(outputFName); // Output file stream to output file


    /**
     *  Reads input file line by line
     *  Parses each line for words
     *  Repeats until file is empty
     */
    string line;
    do {
        getline(inStream, line);
        process(line, outStream);
    } while (!inStream.eof());

    inStream.close();       //Closes file streams
    outStream.close();
}

void SpellingNazi::process(string &line, ofstream &writer) {
    static int lineNum = 0; //line counter
    lineNum++;
    toLower(line);
    int start;
    string word;
    start = splitPos(line, 0);  //finds first delimiter
    bool containsNumber = isdigit(line[start]); //checks whether delimiter is a number
    /**
     * Runs through string to find words and classfiy them
     */
    for (int kk = start; kk <= line.size(); ++kk){

        if (start == -1) break; //Checks whether line doesn't have any delimiters
        
        containsNumber = containsNumber || isdigit(line[kk]); // is any character is a number

        /**
         * If character is not a valid word character, it's a delimiter. Parses word and spell checks
         */
        if (!(isalpha(line[kk]) || isdigit(line[kk]) || line[kk] == 45 || line[kk] == 92 || line[kk] == 39)){
            word = line.substr(start, kk-start);

            if (word.size() > 20)
                writer << "Long word at line " << lineNum << ", starts: " << word.substr(0,20) << endl; //Error message for long words
            else if (!containsNumber && !dict->contains(word))
                writer << "Unknown word at line " << lineNum << ": " << word << endl; //Error message for short words
            kk = start = splitPos(line, kk);
            containsNumber = isdigit(line[start]); //if start of word is number
        }
    }
}

int SpellingNazi::splitPos(string &line, int init) {
    /**
     * Runs through line starting at init and finds starting position
     */
    for (int kk = init; kk < line.size(); kk++)
        if (isalpha(line[kk]) || isdigit(line[kk]) || line[kk] == 45 || line[kk] == 92 || line[kk] == 39)
            return kk;
    return -1; //no starting position found
}

void SpellingNazi::toLower(string &str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
}