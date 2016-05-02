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
 * Version 1.5
 */

// QuickSort T1, T2, Radix Sort T3, Insertion Sort T4

/*
 * Class declarations for each type of data point for T1, T2, T3, & T4
 */

// T1 & T2 Type Node
class NodeTypeA{ 
public:
  Data* dataRef;
  unsigned long long post;
  unsigned long long pre;
  int least; 
  int size;
};

// T3 Type Node
class NodeTypeB{
public: 
  Data* dataRef;
  float total;
  int intRep;
}; 

// T4 Type Node
class NodeTypeC{
public: 
  Data* dataRef; 
  unsigned long long post;
  unsigned long long pre;
};

//Public Variables Declaration
list<Data *>::iterator startIterator; 
list<Data *>::iterator endIterator;
NodeTypeA ArrayOfA[2000000]; 
NodeTypeB ArrayOfB[2000000];
NodeTypeC ArrayOfC[2000000];
NodeTypeB TempArrayOfB[2000000];
int fileType, listSize;

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

bool CompareA(const NodeTypeA &first, const NodeTypeA &second){
  if(first.size != second.size)
    return first.size < second.size;
  else return first.post < second.post; 
}

bool CompareB(const NodeTypeB &first, const NodeTypeB &second){
  return first.total < second.total;
}

bool CompareC(const NodeTypeC &first, const NodeTypeC &second){
  if(first.post != second.post)
    return first.post < second.post;
  else return first.pre < second.pre; 
}

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

void radixSort(int size){

  int digit = 1;
  int passNum = 1;

  while(999999/digit > 0){
    countingSort(size, digit);
    passNum++;
    digit*=10;
  }

}

void sortDataList(list<Data *> &l) {
  // Fill in this function
  startIterator = l.begin();
  endIterator = l.end();
  endIterator--;
  listSize = l.size();

  //Code below finds the type of file that is being handled & sorted

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

  startIterator = l.begin(); // Resets startIterator

  //Arranges Strings into Sortable Array
  if(fileType == 3){
    for(int i = 0; i < listSize; i++, startIterator++){
      ArrayOfB[i] = NodeTypeB();
      ArrayOfB[i].dataRef = (*startIterator); 
      ArrayOfB[i].total = atof((*startIterator)->data.c_str());
      ArrayOfB[i].intRep = (int)(ArrayOfB[i].total * 1000); 
    }
  }
  else if(fileType != 4){
    int posOfDecimal; 
    int strLength;
    for(int i = 0; i < listSize; i++, startIterator++){
      ArrayOfA[i] = NodeTypeA();
      posOfDecimal = (*startIterator)->data.find('.');
      if(posOfDecimal == 20){
        ArrayOfA[i].size = 20;
        ArrayOfA[i].post = strtoull((*startIterator)->data.substr(0,19).c_str(),0,10);
        ArrayOfA[i].dataRef = (*startIterator);
      }
      else{
        ArrayOfA[i].size = posOfDecimal;
        ArrayOfA[i].post = strtoull((*startIterator)->data.substr(0,posOfDecimal).c_str(), 0, 10);
        ArrayOfA[i].dataRef = (*startIterator);
      }
    }
  }
  else{
    int posOfDecimal; 
    for(int i = 0; i < listSize; i++, startIterator++){
      ArrayOfC[i] = NodeTypeC();
      posOfDecimal = (*startIterator)->data.find('.');
      ArrayOfC[i].post = strtoull((*startIterator)->data.substr(posOfDecimal-16,17).c_str(), 0, 10);
      ArrayOfC[i].pre = strtoull((*startIterator)->data.substr(posOfDecimal+1, 15).c_str(), 0, 10); 
      ArrayOfC[i].dataRef = (*startIterator);
    }

  }

  //Switch statement that sorts the list
  switch(fileType){
    case 1:
       //QuickSort
      sort(ArrayOfA, ArrayOfA + listSize, CompareA);
      break;  
    case 2: 
      //QuickSort
      sort(ArrayOfA, ArrayOfA + listSize, CompareA);
      break; 
    case 3:
      sort(ArrayOfB, ArrayOfB + listSize, CompareB);
      break; 
    case 4: 
      insertionSort(listSize);
      break;
  };

  copyToOriginal(l);

  cout << "Sorting complete!" << endl;
}