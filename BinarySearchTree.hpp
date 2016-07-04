#ifndef BINARYSEARCHTREE_HPP
#define BINARYSEARCHTREE_HPP

#include <iostream>
using namespace std; 

template<typename T>
class Node{
private:
	T data;
	Node<T>* left; 
	Node<T>* right;
public:
	Node(T data); 
	void setData(T data);
	void setRight(Node<T>* node); 
	void setLeft(Node<T>* node); 
	T getData(); 
	Node<T>* getLeft(); 
	Node<T>* getRight(); 
}; 

template<typename T>
class BinarySearchTree{
private: 
	Node<T>* root;
	int numNodes; 
	void clearTree(Node<T>* t); 
	Node<T>* duplicateNode(Node<T>* t); 
	void printAll(Node<T>* t); 
public:
	BinarySearchTree();
	~BinarySearchTree();
	Node<T>* getRoot();
	void setRoot(Node<T>* newRoot); 
	bool isEmpty();
	Node<T>* searchTree(T data); 
	bool insert(Node<T>* newNode); 
	bool insert(T data);
	bool deleteNode(T data); 
	Node<T>* findMin();
	Node<T>* findMax(); 
	int getNumNodes(); 
	void printOne(Node<T>* t); 
	void printTree(); 

}; 

#include "BinarySearchTree.tpp"

#endif