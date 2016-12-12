/**
 * Krishna Thiyagarajan
 * ECE-365: Data Structures & Algorithms II
 * Prof. Carl Sable
 * Programming Assignment 4
 * December 12, 2016
 * File: krishDynamic.cpp
 */

#include <iostream>
#include <fstream>
#include <cstring>

#define MAX_SIZE 1001 //Max size of a word is given. Don't need more space than that

using namespace std;

short data[MAX_SIZE][MAX_SIZE];  // Maximum size string size of 1001. matrix of that size

bool isMerge(string str1, string str2, string *str3) {

    //String not merge if sizes don't add up
    if (str1.length() + str2.length() != str3->length())
        return false;

    //Initialize data array
    memset(data, 0, sizeof(data[0][0]) * MAX_SIZE * MAX_SIZE);

    data[0][0] = 1; //Always going to be set to 1

    //Loop through both strings and find out which characters are from which string
    for (int jj = 0; jj <= str2.length(); jj++)
        for (int ii = 0; ii <= str1.length(); ii++)
            if (data[ii][jj]) {
                if (str1[ii] == (*str3)[ii + jj] && !data[ii + 1][jj])
                    data[ii + 1][jj] = 2;
                if (str2[jj] == (*str3)[ii + jj] && !data[ii][jj + 1])
                    data[ii][jj + 1] = 3;
            }

    // Traverse matrix to see if str3 is a right form of merge
    int ii = (int)str1.length(), jj = (int)str2.length(), kk;

    while (ii + jj > 0) {
        if (!data[ii][jj]) //Not a merge in this case for all possibilities
            return false;

        kk = ii + jj - 1;

        if (data[ii][jj] == 2)
            (*str3)[kk] = (char)toupper((*str3)[kk]); // From str1 so convert to uppercase

        //Find which way to traverse in matrix
        if (jj > 0 && data[ii][jj - 1])
            jj--;
        else if (ii > 0 && data[ii - 1][jj])
            ii--;
    }

    return true;
}

int main() {

    //Open input and output files as streams
    string inFile, outFile;

    cout << "Input file: ";
    cin >> inFile;

    cout << "Output file: ";
    cin >> outFile;

    ifstream inStream(inFile);
    ofstream outStream(outFile);

    if(!inStream){
        cerr << "Input file not found!" << endl;
        return -1;
    }

    if(!outStream){
        cerr << "Output file cannot be opened!" << endl;
        return -1;
    }

    //Get input strings
    string str1, str2, str3;

    while (getline(inStream, str1) && getline(inStream, str2) && getline(inStream, str3))
        if (isMerge(str1, str2, &str3))
            outStream << str3 << endl;
        else outStream << "*** NOT A MERGE ***" << endl;

    inStream.close();
    outStream.close();

    return 0;
}
