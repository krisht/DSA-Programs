#ifndef BINARYSEARCHTREE_HPP
#define BINARYSEARCHTREE_HPP

#include <iostream>
using namespace std; 

template<class T>
class Node{
private:
	T data;
	Node<T>* left; 
	Node<T>* right;
public:
	void setData(T data);
	void setRight(Node<T>* node); 
	void setLeft(Node<T>* node); 
	T getData(); 
	Node<T>* getLeft(); 
	Node<T>* getRight(); 
}; 

template<class T>
class BinarySearchTree{
private: 
	Node<T>* root; 
	void clearTree(Node<T>* t); 
	Node<T>* duplicateNode(Node<T>* t); 
	void printAll(Node<T>* t); 
public:
	BinarySearchTree();
	~BinarySearchTree(); 
	bool isEmpty();
	Node<T>* searchTree(T data); 
	bool insert(Node<T>* newNode); 
	bool insert(T data);
	bool deleteNode(T data); 
	Node<T>* findMin(); 
	void printOne(Node<T>* t); 
	void printTree(); 
	Node<T>* getRoot(); 

}; 

#endif