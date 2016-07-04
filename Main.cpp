#include <cstdlib> 
#include <ctime> 
#include <iostream>
#include <string.h>
#include "BinarySearchTree.hpp"

using namespace std; 

int main(){
	BinarySearchTree<int>* theTree; 
	Node<int>* newNode; 

	theTree = new BinarySearchTree<int>(); 

	srand((unsigned)time(0)); 
	for(int i = 0; i < 100; i++){
    	int randNum = (rand()%10000)+1;
    	theTree->insert(new Node<int>(randNum));
	}


	theTree->printTree(); 

    return 0;

}