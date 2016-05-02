// THIS IS THE PROVIDED CODE FOR PROGRAM #2, DSA 1, SPRING 2016

#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <cstring>
#include <cctype>
#include <cstdlib>

using namespace std;


// A simple class; each object holds one string
class Data {
public:
  string data;
  Data(const string &s) { data = s; }
};

// Load the data from a specified input file
void loadDataList(list<Data *> &l) {
  string filename;
  cout << "Enter name of input file: ";
  cin >> filename;

  ifstream input(filename.c_str());
  if (!input) {
    cerr << "Error: could not open " << filename << endl;
    exit(1);
  }

  // The first line indicates the size
  string line;
  getline(input, line);
  stringstream ss(line);
  int size;
  ss >> size;

  // Load the data
  for (int i = 0; i < size; i++) {
    string line;
    getline(input, line);
    l.push_back(new Data(line));
  }

  input.close();
}

// Output the data to a specified input file
void writeDataList(const list<Data *> &l) {
  string filename;
  cout << "Enter name of output file: ";
  cin >> filename;

  ofstream output(filename.c_str());
  if (!output) {
    cerr << "Error: could not open " << filename << endl;
    exit(1);
  }

  // Write the size first
  int size = l.size();
  output << size << endl;

  // Write the data
  for (list<Data *>::const_iterator ipD = l.begin(); ipD != l.end(); ipD++) {
    output << (*ipD)->data << endl;
  }

  output.close();
}

void sortDataList(list<Data *> &);

// The main function calls routines to get the data, sort the data,
// and output the data. The sort is timed according to CPU time.
int main() {
  list<Data *> theList;
  loadDataList(theList);

  cout << "Data loaded.  Executing sort..." << endl;

  clock_t t1 = clock(); 
  sortDataList(theList);
  clock_t t2 = clock();
  double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;

  cout << "Sort finished. CPU time was " << timeDiff << " seconds." << endl;

  writeDataList(theList);
}

// -------------------------------------------------
// YOU MAY NOT CHANGE OR ADD ANY CODE ABOVE HERE !!!
// -------------------------------------------------

// You may add global variables, functions, and/or
// class defintions here if you wish.

/*
 * Krishna Thiyagarajan
 * Prof. Carl Sable
 * ECE-164: DSA I
 * MasterSort.cpp
 * Version 3.0
 * Purpose: Sort a list of randomly generated floats
 *          in the form of strings eficiently
 * Apprch : Classify file type into T1, T2, T3 or T4
 *          as noted in assignment. Extract useful
 *          data into the below described nodes
 *          apply QuickSort if T1 or T2, Radix if T3
 *          and Insertion if T4.  
 */

/*
 * TypeA Node Object for T1 & T2 types of data
 */
class NodeTypeA{
public:
  Data* dataRef;
  unsigned long long leftOfDec;
  unsigned long long rightOfDec;
  int least; 
  int sizeOfWhole;
};

/*
 * TypeB Node Object for T3 type of data
 */
class NodeTypeB{
public: 
  Data* dataRef;
  float floatValue;
  int intRep;
}; 

/*
 * TypeC Node Object for T4 type of data
 */
class NodeTypeC{
public: 
  Data* dataRef; 
  unsigned long long leftOfDec;
  unsigned long long rightOfDec;
};

//Public Variables Declaration
list<Data *>::iterator startIterator;                             //Start & End Iterator for copying and transferring arrays
list<Data *>::iterator endIterator;
NodeTypeA ArrayOfA[2000000];                                      //Arrays for manipulating and sorting
NodeTypeB ArrayOfB[2000000];
NodeTypeC ArrayOfC[2000000];
NodeTypeB TempArrayOfB[2000000];                                  // Temporary Array for Radix Sort
int fileType, listSize;                                           // Public variables for easy usage (this was allowed in assignment)

/*
 * General function to copy manipulated arrays to original list
 */
void copyToOriginal(list<Data *> &l){
  startIterator = l.begin(); 
  endIterator = l.end();
  int i = 0; 

  while(startIterator != endIterator){
    if(fileType == 3)
      *startIterator = ArrayOfB[i].dataRef;
    else if(fileType !=4)
      *startIterator = ArrayOfA[i].dataRef;
    else *startIterator = ArrayOfC[i].dataRef;
    i++;
    startIterator++;
  }
}

/*
 * Comparison function for Type A elements
 * Returns true if first argument is less than second argument
 */
bool CompareA(const NodeTypeA &first, const NodeTypeA &second){
  if(first.sizeOfWhole != second.sizeOfWhole)
    return first.sizeOfWhole < second.sizeOfWhole;
  else return first.leftOfDec < second.leftOfDec; 
}

/*
 * Comparison function for Type C elements
 * Returns true if first argument is less than second argument
 */
bool CompareC(const NodeTypeC &first, const NodeTypeC &second){
  if(first.leftOfDec != second.leftOfDec)
    return first.leftOfDec < second.leftOfDec;
  else return first.rightOfDec < second.rightOfDec; 
}

/*
 * Insertion sort for T4 type of files
 */
void insertionSort(int size){
  for(int i = 1; i < size; i++){
    int j = i-1; 
    NodeTypeC temp = ArrayOfC[i];
    while(j>=0 && CompareC(temp, ArrayOfC[j])){
      ArrayOfC[j+1] = ArrayOfC[j];
      j--; 
    }
    ArrayOfC[j+1] = temp;
  }
}

/*
 * Counting sorter for Radix sorting
 */
void countingSort(int size, int digit){
  int countOfDigits[10] = {0};

  for(int i = 0; i < size; i++)
    countOfDigits[(ArrayOfB[i].intRep/digit) % 10]++;

  for(int i = 1; i< 10; i++)
    countOfDigits[i]+=countOfDigits[i-1];

  for(int i = size -1; i >= 0; i--){
    TempArrayOfB[countOfDigits[(ArrayOfB[i].intRep/digit) % 10] - 1] = ArrayOfB[i];
    countOfDigits[(ArrayOfB[i].intRep/digit) % 10]--;
  }

  for(int i = 0; i < size; i++)
    ArrayOfB[i] = TempArrayOfB[i];

}

/*
 * Radix sort for T3 type files
 */
void radixSort(int size){                                       

  int digit = 1;
  int passNum = 1;

  while(999999/digit > 0){
    countingSort(size, digit);
    passNum++;
    digit*=10;
  }

}

/*
 * Sorts given list l intelligently
 */

void sortDataList(list<Data *> &l) { 

  startIterator = l.begin();                                                // Initiates starting point and ending point with iterators
  endIterator = l.end(); 
  endIterator--;
  listSize = l.size();                                                      // Finds list size 

  /*
   * Finds the type of file that is being handled & sorted
   */

  if(listSize > 500000){
    if((*startIterator)->data.size()/sizeof(char) <= 7)
      fileType = 3;
    else{
      unsigned long long testA, testB; 
      testA = strtoull((*startIterator)->data.substr(0,8).c_str(), 0, 10); 
      startIterator++;
      testB= strtoull((*startIterator)->data.substr(0,8).c_str(),0,10);
      if(testA == testB)
        fileType = 4;
      else fileType = 2;
    }
  }
  else fileType = 1; 

  startIterator = l.begin();                                                // Resets startIterator

  /*
   *Arranges strings into sortable array and extracts necessary information
   */
  if(fileType == 3){
    for(int i = 0; i < listSize; i++, startIterator++){
      ArrayOfB[i] = NodeTypeB();
      ArrayOfB[i].dataRef = (*startIterator); 
      ArrayOfB[i].floatValue = atof((*startIterator)->data.c_str());
      ArrayOfB[i].intRep = (int)(ArrayOfB[i].floatValue * 1000); 
    }
  }
  else if(fileType != 4){
    int posOfDecimal; 
    int strLength;
    for(int i = 0; i < listSize; i++, startIterator++){
      ArrayOfA[i] = NodeTypeA();
      posOfDecimal = (*startIterator)->data.find('.');
      if(posOfDecimal == 20){
        ArrayOfA[i].sizeOfWhole = 20;
        ArrayOfA[i].leftOfDec = strtoull((*startIterator)->data.substr(0,19).c_str(),0,10);
        ArrayOfA[i].dataRef = (*startIterator);
      }
      else{
        ArrayOfA[i].sizeOfWhole = posOfDecimal;
        ArrayOfA[i].leftOfDec = strtoull((*startIterator)->data.substr(0,posOfDecimal).c_str(), 0, 10);
        ArrayOfA[i].dataRef = (*startIterator);
      }
    }
  }
  else{
    int posOfDecimal; 
    for(int i = 0; i < listSize; i++, startIterator++){
      ArrayOfC[i] = NodeTypeC();
      posOfDecimal = (*startIterator)->data.find('.');
      ArrayOfC[i].leftOfDec = strtoull((*startIterator)->data.substr(posOfDecimal-16,17).c_str(), 0, 10);
      ArrayOfC[i].rightOfDec = strtoull((*startIterator)->data.substr(posOfDecimal+1, 15).c_str(), 0, 10); 
      ArrayOfC[i].dataRef = (*startIterator);
    }

  }

  /*
   * Switch statement that sorts list based on type of list
   */
  switch(fileType){
    case 1:                 
    case 2: 
      //QuickSort
      sort(ArrayOfA, ArrayOfA + listSize, CompareA );
      break; 
    case 3:
      radixSort(listSize); 
      break; 
    case 4: 
      insertionSort(listSize);
      break;
  };

  copyToOriginal(l);

}