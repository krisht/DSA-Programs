#include <cstdlib> 
#include <ctime> 
#include <iostream>
#include "LinkedList.hpp"

using namespace std; 

int main(){
	SList<int>* list;

	list = new SList<int>();
	srand (time(NULL));

	for(int i = 0; i < 100; i++)
		list->insert(rand() % 1000 + 1); 

	list->printList(); 

    return 0;

}
