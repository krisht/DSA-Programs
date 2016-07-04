#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include <iostream>
using namespace std; 

template<typename T>
class LinkedNode{
private:
	T data; 
	LinkedNode<T>* next;
	friend std::ostream& operator<<(std::ostream &strm, const LinkedNode* a){
		if(a == NULL)
			return strm << "NULL"; 
		return strm << "LinkedNode(Data: "<< a->data << ")"; 
	};
public:
	LinkedNode(T data); 
	void setData(T data);
	void setNext(LinkedNode<T>* node); 
	T getData(); 
	LinkedNode<T>* getNext();
}; 

template<typename T>
class List{
private: 
	LinkedNode<T>* head;
	int numNodes; 
	void clearTree(LinkedNode<T>* t); 
	LinkedNode<T>* duplicateNode(LinkedNode<T>* t); 
	void printAll(LinkedNode<T>* t); 
	friend std::ostream& operator<<(std::ostream &strm, const List* a){
		return strm << "List(Root Node: "<< a->root << ", # of Nodes: " << a->numNodes << ")"; 
	}; 
public:
	List();
	~List();
	LinkedNode<T>* getHead();
	void setHead(LinkedNode<T>* newRoot); 
	bool isEmpty();
	LinkedNode<T>* searchTree(T data); 
	bool insert(LinkedNode<T>* newNode); 
	bool insert(T data);
	bool deleteNode(T data); 
	LinkedNode<T>* findMin();
	LinkedNode<T>* findMax(); 
	int getNumNodes(); 
	void printOne(LinkedNode<T>* t); 
	void printTree(); 
}; 

#include "LinkedList.tpp"

#endif