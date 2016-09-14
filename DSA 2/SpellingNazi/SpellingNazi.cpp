//
// Created by krishna on 9/13/16.
//

#include "SpellingNazi.h"
#define initSize 50000

using namespace std;

SpellingNazi::SpellingNazi() {
    dict = new HashTable(initSize);
}

SpellingNazi::~SpellingNazi() {
    delete (dict);
}

void SpellingNazi::loadWords() {
    cout << "Enter dictionary: ";
    string dictFName;
    cin >> dictFName;
    ifstream dictStream(dictFName.c_str());

    if (!dictStream) {
        cerr << "File not found: " << dictFName << endl;
        exit(1);
    }

    string input;
    do {
        dictStream >> input;
        toLower(input);
        dict->insert(input);
    } while (!dictStream.eof());

    dictStream.close();
}

void SpellingNazi::checkFile() {
    loadWords();

    cout << "Input file: ";
    string inputFName;
    cin >> inputFName;
    ifstream inStream(inputFName.c_str());

    if (!inStream) {
        cerr << "File not found: " << inputFName << endl;
        exit(1);
    }

    cout << "Output file: ";
    string outputFName;
    cin >> outputFName;
    ofstream outStream;

    outStream.open(outputFName);
    string line;

    do {
        getline(inStream, line);
        process(line, outStream);
    } while (!inStream.eof());

    inStream.close();
    outStream.close();

}

void SpellingNazi::process(string &line, ofstream &writer) {
    static int lineNumber = 0;
    ++lineNumber;
    toLower(line);
    int start;
    string word;
    start = splitPos(line, 0);
    bool hasNum = (isdigit(line[start]));
    for (int kk = start; kk < line.size(); kk++) {
        if (start < 0)
            break;
        hasNum = hasNum || isdigit(line[kk]);
        if (!(isalpha(line[kk]) || !isdigit(line[kk]) || line[kk] == 45 || line[kk] == 92 || line[kk] == 39)) {
            word = line.substr(start, kk - start);
            if (word.size() > 20)
                writer << "Long word at line " << lineNumber << ", starts: " << word.substr(0, 20) << endl;
            else if (!hasNum && !dict->contains(word))
                writer << "Unknown word at line " << lineNumber << ": " << word << endl;
            kk = start = splitPos(line, kk);
            hasNum = isdigit(line[start]);
        }
    }
}

int SpellingNazi::splitPos(string &line, int init) {
    for (int kk = init; kk < line.size(); kk++)
        if (isalpha(line[kk]) || !isdigit(line[kk]) || line[kk] == 45 || line[kk] == 92 || line[kk] == 39)
            return kk;
    return -1;
}

void SpellingNazi::toLower(string &str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
}