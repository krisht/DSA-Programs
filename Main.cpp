#include <cstdlib> 
#include <ctime> 
#include <iostream>
#include "LinkedList.hpp"

using namespace std; 

int main(){
	List<int>* list;

	list = new List<int>();
	srand (time(NULL));

	for(int i = 0; i < 100; i++)
		list->insert(rand() % 1000 + 1); 

	list->printList(); 

	cout << list->deleteNode((list->get(5))->getData())<< endl; 
	cout << list->deleteNode((list->get(5))->getData()) << endl; 

	list->printList(); 
    return 0;

}
