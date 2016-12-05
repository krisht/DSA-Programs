/**
 * Krishna Thiyagarajan
 * ECE-365: Data Structures & Algorithms II
 * Program IV - Dynamic Programming
 * December 5, 2016
 * Prof. Carl Sable
 */

#include <cctype>
#include <iostream>
#include <fstream>

using namespace std;

int data[1005][1005];

int main(){
    
    string inFile, outFile;
   
    cout << "Enter name of input file: " ;
    cin >> inFile;
   
    cout << "Enter name of output file: ";
    cin >> outFile;
   
    ifstream inStream(inFile.c_str());
    if (!inStream){
        cerr << "Error: File not found!" << endl;
        return 1;
    }
    
    ofstream outStream(outFile.c_str());
    if (!outStream){
        cerr << "Error: Cannot open output file!" << endl;
        return 1;
    }
    
    data[0][0] = 0;
    string str1, str2, strcomb;
    int larger = 0;
    int ii, jj;

    while (!inStream.eof()){

        inStream >> str1 >> str2 >> strcomb;

        //Fill in top row
        for (ii = 0; ii < str1.length(); ii++)
            data[0][ii+1] = (strcomb[data[0][ii]] == str1[ii]) ? data[0][ii] + 1 : data[0][ii];

        //Fill in top column
        for (ii = 0; ii <= str2.length(); ii++)
            data[ii+1][0] = (strcomb[data[ii][0]] == str2[ii]) ? data[ii][0] + 1 : data[ii][0];

        //Fill in the rest of the matrix
        for (ii = 1; ii < str2.length() + 1; ii++)
            for (jj = 1; jj <= str1.length(); jj++){
                bool upOrDown = (data[ii-1][jj] > data[ii][jj-1]);
                larger = (upOrDown) ? data[ii-1][jj] : data[ii][jj-1];
                char tempChar = (upOrDown) ? str2[ii-1] : str1[jj-1];
                data[ii][jj] = (tempChar == strcomb[larger]) ? larger + 1 : larger;
            }


        if (data[--ii][--jj] != strcomb.length())
            outStream << "*** NOT A MERGE ***" << endl;
        else {
            larger = data[ii][jj];

            while (larger != 0){

                if (ii == 0){
                    larger = data[ii][--jj];
                    strcomb[larger] = toupper(strcomb[larger]);
                    continue;
                }

                if (jj == 0){
                    larger = data[--ii][jj];
                    continue;
                }
                if (data[ii-1][jj] == (larger-1))
                    larger = data[--ii][jj];
                else {
                    larger = data[ii][--jj];
                    strcomb[larger] = toupper(strcomb[larger]);
                }

            }

            outStream << strcomb << endl;

        }

    }

}