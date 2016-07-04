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
	Node();
	~Node(); 
	void setData(T data);
	void setRight(Node<T>* node); 
	void setLeft(Node<T>* nodintere); 
	T getData(); 
	Node<T>* getLeft(); 
	Node<T>* getRight();
	friend ostream& operator << (ostream& strm, const Node<T>& a){
		strm << "Node(Left: "<< a->getLeft() << ", Data: "<< a->getData() << ", Right: " << a->getRight() << ")"; 
		return strm; 
	}; 
}; 

template<class T>
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
	friend ostream& operator << (ostream& strm, const BinarySearchTree<T>& a){
		strm << "BST(Root: "<< a->getRoot()  << ")"; 
		return strm; 
	}; 
}; 

#endif