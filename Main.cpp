#include <cstdlib> 
#include <ctime> 
#include <iostream>
#include <string.h>
#include "BinarySearchTree.hpp"

using namespace std; 

int main(){
	BinarySearchTree<float>* theTree; 
	Node<float>* newNode; 

	theTree = new BinarySearchTree<float>(); 

	srand((unsigned)time(0)); 
	for(int i = 0; i < 1000; i++){
    	float randNum = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) ; 
    	theTree->insert(new Node<float>(randNum));
	}	

	theTree->printTree();  

    return 0;

}