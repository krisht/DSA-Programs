#include "SpellingNazi.h"
#include <ctime>

#define initSize 50000

using namespace std;

SpellingNazi::SpellingNazi() {
    dict = new HashTable(initSize);
}

SpellingNazi::~SpellingNazi() {
    delete(dict);
}

void SpellingNazi::loadWords(){
    cout << "Dictionary: ";

    string dictFName;
    cin >> dictFName;

    ifstream dictStream(dictFName.c_str());
    
    if(!dictStream){
        cerr << "Dictionary not found: " << dictFName << endl;
        exit(-1);
    }

    clock_t t1 = clock();
    string input;
    dictStream >> input;
    while(!dictStream.eof()){
        toLower(input);
        dict->insert(input);
        dictStream >> input;
    }

    clock_t t2 = clock();
    double diff  = ((double)(t2-t1))/CLOCKS_PER_SEC;
    cout << "Total time (in seconds) to load dictionary: " << diff << endl;
    dictStream.close();
}

void SpellingNazi::checkFile(){
    loadWords();
    cout << "Input: ";
    string inFileName;
    cin >> inFileName;

    ifstream inStream(inFileName.c_str());
    if (!inStream) {
        cerr << "Input not found: " << inFileName << endl;
        exit(-1);
    }

    cout << "Output: ";
    string outFileName;
    cin >> outFileName;
    ofstream outStream;
    outStream.open(outFileName);

    string line;
    clock_t t1 = clock();
    do{
        getline(inStream, line);
        process(line, outStream);
    }while(!inStream.eof());
    clock_t t2 = clock();

    double diff = ((double)(t2-t1))/CLOCKS_PER_SEC;
    cout << "Total time (in seconds) to check document: " << diff << endl;
    inStream.close();
    outStream.close();
}

void SpellingNazi::process(string &line, ofstream &writer) {
    static int lineNum = 0;
    lineNum++;
    toLower(line);
    int start;
    string word;

    start = firstValidCharPos(line, 0);
    bool hasNum = isdigit(line[start]);
    for(int kk = start; kk <= line.size(); kk++){
        if(start == -1)
            break;
        hasNum = hasNum || isdigit(line[kk]);
        if(!isValidChar(line[kk])){
            word = line.substr(start, kk - start);

            if(word.size() > 20)
                writer << "Long word at line " << lineNum << ", starts: " << word.substr(0,20) << endl;
            else if(!hasNum && !dict->contains(word))
                writer << "Unknown word at line " << lineNum << ": " << word << endl;

            kk = start = firstValidCharPos(line, kk);
            hasNum = isdigit(line[start]);
        }
    }

}

int SpellingNazi::firstValidCharPos(string &line, int init) {
    for(int kk = init; kk < line.size(); kk++)
        if(isValidChar(line[kk]))
            return kk;
    return -1;
}

void SpellingNazi::toLower(string &str) {
    for(int kk = 0; kk <str.size(); kk++)
        str[kk] = tolower(str[kk]);
}

bool SpellingNazi::isValidChar(int charInt) {
    return ((charInt<=90 && charInt>=65) || (charInt<=122 && charInt>=97) || (charInt<=57 && charInt>=48) || charInt== 45 || charInt == 92 || charInt== 39);
}