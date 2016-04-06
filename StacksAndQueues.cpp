/*
 * Krishna Thiyagarjan
 * Prof. Carl Sable
 * ECE-164: DSA I
 * StacksAndQueues.cpp
 * Version 2
 */

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <fstream>

using namespace std; 

template<class T>
class List{																							// Declares the generic list class
protected:																							// Creates a couple of protected vars in list(inheritable things but not public)
	string listName; 
	int listSize; 
	class Node{																						// Creates the node class inside the List class
	public:
		T nodeData; 																				// Node has data, points to the next node
		Node* nextNode;
		Node(T inputData); 																			// Constructor for node
	};
	Node* firstNode; 																				// First node nad last node of list
	Node* lastNode;

public:
	T pop();																						// Pop is a common function for all lists
	virtual void push(T pushedData) = 0; 															// Empty function that child classes can override
	string getListName();
	int getListSize();
	List(string name);																				// Base class constructor
};

template<class T>
string List<T>::getListName(){																		// Function that returns the List's name					
	return this->listName;
}; 

template<class T>
int List<T>::getListSize(){																			// Function that returns List's current size
	return this->listSize; 
};

template<class T> 
List<T>::List(string name){																			// Defines the base class constructor
	this->listName = name; 																			// Sets name using constructor
	this->listSize = 0;
	this->firstNode = this->lastNode = 0;															// Since new List, there are no Nodes in it
}; 

template<class T> 
List<T>::Node::Node(T input){																		// Defines Node constructor
	this->nodeData = input; 
	this->nextNode = 0;
}; 

template<class T>
class Stack: public List<T>{																		// Defines Stack as a subclass of List
public:
	void push(T pushedData);
	Stack(string stackName):List<T>(stackName){};
};

template<class T>
class Queue: public List<T>{																		// Defines Queue as a sublcass of List
public:
	void push(T pushedData); 
	Queue(string queueName):List<T>(queueName){};
}; 

template<class T>
T List<T>::pop(){																					// Stack and Queue removes values from first index of a list, so common function
	T poppedValue = this->firstNode->nodeData;
	typename List<T>::Node* tempNode = this->firstNode;
	this->firstNode = tempNode->nextNode;
	delete(tempNode);
	this->listSize--;
	return poppedValue;
}; 

template<class T>
void Stack<T>::push(T pushedData){																	// Overrides push function in List
	typename List<T>::Node* tempNode = new typename List<T>::Node(pushedData);						// Defines a temporary Node
	if(this->listSize == 0){																		// Checks if List is empty
		this->firstNode = this->lastNode = tempNode;												// Sets firstNode and lastNode as the new tempNode b/c it is the first Node
		tempNode->nextNode = 0; 																	// Sets the tempNode's nextNode to null (0)
		this->listSize++;
		return;																						// Returns so that no other operations are needed
	}
	tempNode->nextNode=this->firstNode;																// In case List is not empty, sets tempNodes nextNode as the firstNode of the List
	this->firstNode = tempNode; 																	// Sets firstNode as the tempNode
	this->listSize++;
};

template<class T>
void Queue<T>::push(T pushedData){																	// Overrides the push function in List
	typename List<T>::Node* tempNode = new typename List<T>::Node(pushedData);			
	if(this->listSize == 0){
		this->firstNode = this->lastNode = tempNode;												// If list is empty, firstNode and lastNode are both set to the tempNode
		tempNode->nextNode = 0;																		// No Nodes after tempNode that is being pushed into Queue
		this->listSize++;																
		return;
	}
	this->lastNode->nextNode=tempNode;																// In case list is not empty, sets tempNode as a node after lastNode
	this->lastNode = tempNode; 																		// Sets tempNode as the lastNode of the list
	this->listSize++;
};

template<class T>
List<T>* findList(vector<List<T>*>* toSearch, string listName){										// Searching function that searches for List given Vector and list's name
	vector<List<T>*> tempSearch = *toSearch;														
	int tempSize = tempSearch.size() - 1;															// Sets initial value of size of the tempSearch vector to n - 1
	List<T>* valFound = 0;																			// Sets found list value to null (0)
	while(tempSize >= 0){																			// When size is positive, searches list for match
		if(!listName.compare(tempSearch[tempSize]->getListName())){
			valFound = tempSearch[tempSize];
			break;
		}
		tempSize--; 
	}
	return valFound;																				// Returns list if it is found
}; 

template<class T>
void createList(vector<List<T> *>* destVector, string listType, string listName, ofstream* output){	// List creating function that adds list to given vector with given parameters
	if(findList<T>(destVector, listName)){															// Checks whether vector already contains the list
		(*output) << "ERROR: This name already exists!" << endl;
	}
	else{																							// Creates and adds list to vector if vector does not contain list
		List<T> * tempList;																			// Checks what type of list needs to be created
		if(listType.compare("stack")){
			tempList = new Queue<T>(listName);														// Declares temp variable with new Queue with listName
			destVector->push_back(tempList);														// Pushes variable onto vector
		}
		else{
			tempList = new Stack<T>(listName); 														// Does same thing as above but with stack
			destVector->push_back(tempList);
		}
	}
};

template<class T>
void pushList(vector<List<T>*>* destVector, T dataPushed, string listName, ofstream * output){		// Pushes data onto a list in specified vector
	List<T>* tempList = findList<T>(destVector, listName);											// First finds list in the vector
	if(tempList == 0){																				// Checks if list exists
		(*output) << "ERROR: This name does not exist!" <<endl;
		return;
	}
	tempList->push(dataPushed);																		// If it exists, it pushes the data onto the list on the vector
}; 

template<class T>
void popList(vector<List<T> *> * destVector, string name, ofstream * output ){						// Pops data off of a list on the specified vector
	List<T> * tempList = findList<T>(destVector, name);												// Finds the list on the specified vector
	if(tempList == 0){																				// If list does not exist, returns an error
		(*output) << "ERROR: This name does not exist!" << endl;
		return;
	}
	if(tempList->getListSize() == 0){																// If list is empty, returns an error because nothing can be popped
		(*output) << "ERROR: This list is empty!" <<endl; 
		return; 
	}
	T valuePopped = tempList->pop();																// If list is not empty, pops off value depending on type of list
	(*output) << "Value popped: " << valuePopped << endl; 											// Returns popped value to the output stream
}; 

int processCommands(string fInput, string fOutput){
	vector<List<int> *> listOfInteger; 																// Declares athe three types of different vectors needed for the program
	vector<List<double> *> listOfDouble; 
	vector<List<string> *> listOfString; 
	
	ifstream inputStrm;																				// Declares stream variables
	ofstream outputStrm; 
	inputStrm.open(fInput.c_str());  																// Opens streams for input and output
	outputStrm.open(fOutput.c_str());

	if(inputStrm.is_open() == 0){																	// If file is not found, indicates so and closes program
		cout << "File not found! Please retry!" <<endl; 
		return -1; 
	}

	string cmds; 																					// Declares variable to read lines into

	while(getline(inputStrm, cmds)){																// Reads each line of command txt file for commands
		outputStrm << "PROCESSING COMMAND: " << cmds <<endl;										// Indicates which command is being processed
		stringstream cmdSplitter; 																	// Declares a stringstream for easy splitting of command string
		cmdSplitter << cmds; 																		// Inputs command to stringstream
		string instruction, listName, dataType;														
		cmdSplitter >> instruction; 																// Finds instruction and saves it to instruction
		cmdSplitter >> listName; 																	// Finds listname and saves it to listName
		dataType = listName.substr(0,1); 															// Infers datatype from first letter of listName

		if(!instruction.compare("create")){															// Checks if command is to create a new list
			string listType; 
			cmdSplitter >> listType;																// Finds list type (stack or queue?)
			if(!dataType.compare("i"))																// Uses data type to create the list on the appropriate vector
				createList<int>(&listOfInteger, listType, listName, &outputStrm);
			else if(!dataType.compare("d"))
				createList<double>(&listOfDouble, listType, listName, &outputStrm);
			else if(!dataType.compare("s"))
				createList<string>(&listOfString, listType, listName, &outputStrm);
			else{																					// Returns an error if list datatype is wrong (i.e. not i, d or s)
				cout << "Error in list data type detected! Please fix error and restart!" <<endl; 
				return -1; 
			}
		}
		else if(!instruction.compare("push")){														// Checks if command is to push to a list in a vector
			string pushedData; 			
			cmdSplitter >> pushedData;																// Splits string again to find what the data needs to be pushed is
			if(!dataType.compare("i")){																// Uses data type to convert data to appropriate datatype and pushes it to appropriate list in  appropriate vector
				int dataInt = atoi(pushedData.c_str()); 
				pushList<int>(&listOfInteger, dataInt, listName, &outputStrm);
			}
			else if(!dataType.compare("d")){
				double dataDouble = strtod(pushedData.c_str(),0);
				pushList<double>(&listOfDouble, dataDouble, listName, &outputStrm);
			}
			else if(!dataType.compare("s")){
				pushList<string>(&listOfString, pushedData, listName, &outputStrm);
			}
			else{																					// Returns an error if list datatype is wrong
				cout << "Error in list data type detected! Please fix error and restart!" <<endl; 
				return -1; 
			}
		}
		else{																						// Realizes that there is only one command left (pop)
			if(!dataType.compare("i"))																// Checks what data type we are dealing with so that appropriate vector is used
				popList<int>(&listOfInteger, listName, &outputStrm);								// Pops data off of appropriate list in appropriate vector
			else if(!dataType.compare("d"))
				popList<double>(&listOfDouble, listName, &outputStrm);
			else if(!dataType.compare("s"))
				popList<string>(&listOfString, listName, &outputStrm);
			else{																					// Returns an error if list datatype is wrong
				cout << "Error in list data type detected! Please fix error and restart!" <<endl; 
				return -1; 
			}
		} 
	}

	return 0;																						// Returns 0 signalling correct execution of program
}; 

int main(int argc, char **argv){																	// Declares main function with arguments (for my own convenience)
	string fInput = ""; 																			// Declares necessary strings for files, commands, and input and output streams
	string fOutput = ""; 

	if(argc >1){																					// If argc > 1, that means that there are file arguments in a commandline interface
		fInput = argv[1]; 																			// Sets file input
		fOutput = argv[2];																			// Sets file output
	}
	else{
		cout<< "Enter name of input file: " <<endl; 												// If not on a cmd interface, prompts user for input file and output file
		getline(cin, fInput); 
		cout<< "Enter name of output file: " <<endl; 
		getline(cin, fOutput); 
	}

	return processCommands(fInput, fOutput);

}; 