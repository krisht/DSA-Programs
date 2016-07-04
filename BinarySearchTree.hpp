#ifndef BINARYSEARCHTREE_HPP
#define BINARYSEARCHTREE_HPP

#include <iostream>
using namespace std; 

template<typename T>
class BSTNode{
private:
	T data;
	BSTNode<T>* left; 
	BSTNode<T>* right;
	friend std::ostream& operator<<(std::ostream &strm, const BSTNode* a){
		if(a == NULL)
			return strm << "NULL"; 
		return strm << "BSTNode(Data: "<< a->data << ")"; 
	}
public:
	BSTNode(T data); 
	void setData(T data);
	void setRight(BSTNode<T>* node); 
	void setLeft(BSTNode<T>* node); 
	T getData(); 
	BSTNode<T>* getLeft(); 
	BSTNode<T>* getRight(); 
}; 

template<typename T>
class BinarySearchTree{
private: 
	BSTNode<T>* root;
	int numNodes; 
	void clearTree(BSTNode<T>* t); 
	BSTNode<T>* duplicateNode(BSTNode<T>* t); 
	void printAll(BSTNode<T>* t); 
	friend std::ostream& operator<<(std::ostream &strm, const BinarySearchTree* a){
		return strm << "BST(Root Node: "<< a->root << ", # of Nodes: " << a->numNodes << ")"; 
	}
public:
	BinarySearchTree();
	~BinarySearchTree();
	BSTNode<T>* getRoot();
	void setRoot(BSTNode<T>* newRoot); 
	bool isEmpty();
	BSTNode<T>* searchTree(T data); 
	bool insert(BSTNode<T>* newNode); 
	bool insert(T data);
	bool deleteNode(T data); 
	BSTNode<T>* findMin();
	BSTNode<T>* findMax(); 
	int getNumNodes(); 
	void printOne(BSTNode<T>* t); 
	void printTree(); 

}; 

#include "BinarySearchTree.tpp"

#endif