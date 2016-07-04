#include <cstdlib> 
#include <ctime> 
#include <iostream>
#include "BinarySearchTree.hpp"

using namespace std; 

int main(){
	BinarySearchTree<float>* theTree;

	theTree = new BinarySearchTree<float>(); 

	srand((unsigned)time(0)); 
	for(int i = 0; i < 1000; i++){
    	float randNum = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) ; 
    	theTree->insert(new BSTNode<float>(randNum));
	}

	cout << theTree << endl; 

    return 0;

}
