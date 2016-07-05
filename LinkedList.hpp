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
	bool setData(T data);
	bool setNext(LinkedNode<T>* next); 
	T getData(); 
	LinkedNode<T>* getNext();
}; 

template<typename T>
class List{
private: 
	LinkedNode<T>* head;
	int numNodes; 
	bool clearList(LinkedNode<T>* node); 
	LinkedNode<T>* duplicateNode(LinkedNode<T>* t); 
	bool printAll(LinkedNode<T>* t); 
	friend std::ostream& operator<<(std::ostream &strm, const List* a){
		return strm << "List(Root Node: "<< a->head << ", # of Nodes: " << a->numNodes << ")"; 
	}; 
public:
	List();
	~List();
	LinkedNode<T>* getHead();
	bool  setHead(LinkedNode<T>* newRoot); 
	bool isEmpty();
	LinkedNode<T>* searchList(T data); 
	bool insert(LinkedNode<T>* newNode); 
	bool insert(T data);
	bool deleteNode(T data); 
	LinkedNode<T>* findMin();
	LinkedNode<T>* findMax(); 
	int getNumNodes(); 
	bool printOne(LinkedNode<T>* t); 
	bool printList(); 
	LinkedNode<T>* get(int n); 
	bool set(int i, T data);
}; 

#include "LinkedList.tpp"

#endif