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
unsigned long long testArray[10];
NodeTypeA ArrayOfA[2000000]; 
NodeTypeB ArrayOfB[2000000];
NodeTypeC ArrayOfC[2000000];

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

}

void radixSort(int size){
  
}

void sortDataList(list<Data *> &l) {
  // Fill in this function
  int fileType; 
  startIterator = l.begin();
  endIterator = l.end();
  endIterator--;
  int listSize = l.size();

  //Code below finds the type of file that is being handled & sorted

  if(listSize > 500000){
    if((*startIterator)->data.size()/sizeof(char) <= 7)
      fileType = 3;
    else{
      testArray[0] = strtoull((startIterator*)->data.substr(0,8).c_str(),0,10);
      startIterator++;
      testArray[1] = strtoull((startIterator*)->data.substr(0,8).c_str(),0,10);
      if(testArray[0] == testArray[1])
        fileType = 4;
      else fileType = 2;
    }
  }
  else fileType = 1; 

  startIterator = l.begin(); // Resets startIterator

  //Arranges 
  if(fileType == 3){
    for(int i = 0; i < listSize; i++, starIterator++){
      ArrayOfB[i] = NodeTypeB();
      ArrayOfB[i].dataRef = (*startIterator); 
      ArrayOfB[i].total = atof((*startIterator)->data.c_str());
    }
  }
  else if(type != 4){

  }
  else{

  }

  //Switch statement that sorts the list
  switch(fileType){
    case 1:
      //QuickSort
      break;
    case 2: 
      // QuickSort
      break; 
    case 3: 
      //RadixSort
      break; 
    case 4: 
      //Insertion Sort
      break; 
  };

  cout << "Sorting complete!" << endl;
}