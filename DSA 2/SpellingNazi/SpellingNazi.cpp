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
    dictStream >> input;
    while(!dictStream.eof()){
        toLower(input);
        dict->insert(input);
        dictStream >> input;
    }

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
    static int lineNum = 0;
    lineNum++;
    toLower(line);
    int start;
    string word;
    start = splitPos(line, 0);
    bool containsNumber = (line[start]<=57 && line[start]>=48);
    for (int kk = start; kk <= line.size(); ++kk){
        if (start == -1)
            break;
        containsNumber = containsNumber || (line[kk]<=57 && line[kk]>=48); //if any character is a number
        if (!(isalpha(line[kk]) || isdigit(line[kk]) || line[kk] == 45 || line[kk] == 92 || line[kk] == 39)){
            word = line.substr(start, kk-start);
            if (word.size() > 20)
                writer << "Long word at line " << lineNum << ", starts: " << word.substr(0,20) << endl;
            else if (!containsNumber && !dict->contains(word))
                writer << "Unknown word at line " << lineNum << ": " << word << endl;
            kk = start = splitPos(line, kk);
            containsNumber = (line[start]<=57 && line[start]>=48); //if start of word is number
        }
    }
}

int SpellingNazi::splitPos(string &line, int init) {
    for (int kk = init; kk < line.size(); kk++)
        if (isalpha(line[kk]) || isdigit(line[kk]) || line[kk] == 45 || line[kk] == 92 || line[kk] == 39)
            return kk;
    return -1;
}

void SpellingNazi::toLower(string &str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
}