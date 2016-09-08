#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include <iostream>
using namespace std; 

template<typename T>
class SNode{
private:
	T data; 
	SNode<T>* next;
	friend std::ostream& operator<<(std::ostream &strm, const SNode* a){
		if(a == NULL)
			return strm << "NULL"; 
		return strm << "SNode(Data: "<< a->data << ")"; 
	};
public:
	SNode(T data); 
	bool setData(T data);
	bool setNext(SNode<T>* next); 
	T getData(); 
	SNode<T>* getNext();
}; 

template<typename T>
class DNode{
private:
	T data; 
	DNode<T>* next, prev;  
	friend std::ostream& operator<<(std::ostream &strm, const DNode* a){
		if(a == NULL)
			return strm << "NULL"; 
		return strm << "DNode(Data: "<< a->data << ")"; 
	};
public:
	DNode(T data); 
	bool setData(T data);
	bool setNext(DNode<T>* next);
	bool setPrev(DNode<T>* prev);  
	T getData(); 
	DNode<T>* getNext();
	DNode<T>* getPrev(); 
}; 

template<typename T>
class SList{
private: 
	SNode<T>* head;
	int numNodes; 
	bool clearList(SNode<T>* node); 
	SNode<T>* duplicateNode(SNode<T>* t); 
	bool printAll(SNode<T>* t); 
	friend std::ostream& operator<<(std::ostream &strm, const SList* a){
		return strm << "SList(Root Node: "<< a->head << ", # of Nodes: " << a->numNodes << ")"; 
	}; 
public:
	SList();
	~SList();
	SNode<T>* getHead();
	bool  setHead(SNode<T>* newRoot); 
	bool isEmpty();
	SNode<T>* searchList(T data); 
	bool insert(SNode<T>* newNode); 
	bool insert(T data);
	bool deleteNode(T data); 
	SNode<T>* findMin();
	SNode<T>* findMax(); 
	int getNumNodes(); 
	bool printOne(SNode<T>* t); 
	bool printList(); 
	SNode<T>* get(int n); 
	bool set(int i, T data);
}; 

template<typename T>
class DList{
private: 
	DNode<T>* head;
	DNode<T>* tail; 
	int numNodes; 
	bool clearList(DNode<T>* node); 
	DNode<T>* duplicateNode(DNode<T>* t); 
	bool printAll(DNode<T>* t); 
	friend std::ostream& operator<<(std::ostream &strm, const DList* a){
		return strm << "DList(Root Node: "<< a->head << ", # of Nodes: " << a->numNodes << ")"; 
	}; 
public:
	DList();
	~DList();
	DNode<T>* getHead();
	DNode<T>* getTail();
	bool setHead(DNode<T>* newRoot); 
	bool setTail(DNode<T>* newTail); 
	bool isEmpty();
	DNode<T>* searchList(T data); 
	bool insert(DNode<T>* newNode); 
	bool insert(T data);
	bool deleteNode(T data); 
	DNode<T>* findMin();
	DNode<T>* findMax(); 
	int getNumNodes(); 
	bool printOne(DNode<T>* t); 
	bool printList(); 
	DNode<T>* get(int n); 
	bool set(int i, T data);
};

#include "LinkedList.tpp"

#endif