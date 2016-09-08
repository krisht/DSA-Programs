#include <iostream>
#include "LinkedList.hpp"

using namespace std; 

/*
 * SNode<T> implementations
 */

template <typename T>
SNode<T>::SNode(T data){
	this->data = data; 
	this->next = NULL; 
}

template <typename T>
bool SNode<T>::setData(T data){
	this->data = data;
	return (this->data == data); 
}

template <typename T>
bool SNode<T>::setNext(SNode<T>* node){
	this->next = node;
	return (this->next == node); 
}

template <typename T>
T SNode<T>::getData(){
	return this->data; 
}

template <typename T>
SNode<T>* SNode<T>::getNext(){
	return this->next; 
}

/*
 * SList<T> implementation
 */

template <typename T>
bool SList<T>::clearList(SNode<T>* node){
	if( node == NULL)
		return;
	if(node->getNext() !=NULL)
		clearTree(node->getNext());
	delete node;
	return true;  
} 

template <typename T>
SNode<T>* SList<T>::duplicateNode(SNode<T>* node){
	SNode<T>* dupNode = new SNode<T>(node->getData()); 
	return dupNode; 
}

template <typename T>
bool SList<T>::printAll(SNode<T>* node){
	if(node != NULL){
		printOne(node);
		printAll(node->getNext());
	}
	return (node != NULL); 
}

template <typename T>
SList<T>::SList(){
	this->head = NULL;
	this->numNodes = 0;
	return; 
} 

template <typename T>
SList<T>::~SList(){
	this->clearList(this->getHead());
	return; 
}

template <typename T>
SNode<T>* SList<T>::getHead(){
	return this->head; 
}

template <typename T>
bool SList<T>::setHead(SNode<T>* newHead){
	this->head = newHead;
	return (this->head == newHead); 
}

template <typename T>
bool SList<T>::isEmpty(){
	return (this->getHead() == NULL);
}

template <typename T>
SNode<T>* SList<T>::searchList(T data){
	SNode<T>* curr = this->getHead(); 
	while((curr != NULL) && (curr->getData() !=  data))
		curr = curr->getNext();
	if(curr == NULL)
		return curr;
	else return duplicateNode(curr);
}

template <typename T>
bool SList<T>::insert(SNode<T>* newNode){
	SNode<T>* curr = this->getHead(); 
	if(curr == NULL){
		this->setHead(newNode);
		this->numNodes++;  
		return (this->getHead() == newNode); 
	}
	while(curr->getNext() != NULL)
		curr = curr->getNext(); 
	curr->setNext(newNode);
	this->numNodes++;
	return (curr->getNext() == newNode); 
}

template <typename T>
bool SList<T>::insert(T data){
	SNode<T>* newNode = new SNode<T>(data);
	return this->insert(newNode); 
}
//You might need to fix this
template <typename T>
bool SList<T>::deleteNode(T data){
	SNode<T>* curr = this->getHead();
	SNode<T>* prev = NULL;  
	while(curr->getData() != data && curr->getNext() != NULL){
		prev = curr; 
		curr = curr->getNext();
	}

	if(curr == NULL)
		return false; 
	else{
		if(prev == NULL)
			this->setHead(curr->getNext());
		else if(curr->getNext() == NULL)
			prev->setNext(NULL);
		else prev->setNext(curr->getNext());
		
		delete curr; 
		this->numNodes--; 
		return true; 
	}
}

template <typename T>
SNode<T>* SList<T>::findMin(){
	SNode<T>* currMin = this->getHead();
	SNode<T>* curr = this->getHead();
	while(curr->getNext() != NULL){
		curr = curr->getNext();
		if(curr->getData() < currMin->getData())
			currMin = curr;
	}
	return currMin; 
}

template <typename T>
SNode<T>* SList<T>::findMax(){
	SNode<T>* currMax = this->getHead();
	SNode<T>* curr = this->getHead();
	while(curr->getNext() != NULL){
		curr = curr->getNext();
		if(curr->getData() > currMax->getData())
			currMax = curr;
	}
	return currMax; 
}

template <typename T>
int SList<T>::getNumNodes(){
	return this->numNodes; 
}

template <typename T>
bool SList<T>::printOne(SNode<T>* node){
	cout << node << endl;
	return true; 
}

template <typename T>
bool SList<T>::printList(){
	cout << this << endl; 
	printAll(this->getHead()); 
	return true;  
}

template <typename T>
SNode<T>* SList<T>::get(int n){
	if(!(n < this->getNumNodes()))
		return NULL;
	SNode<T>* curr = this->getHead();
	for(int i = 0; i < n; i++)
		curr  = curr->getNext();

	return this->duplicateNode(curr); 
}

template <typename T>
bool SList<T>::set(int i, T data){
	if(!(i < this->getNumNodes()))
		return false;
	SNode<T>* curr = this->getHead();
	for(int k = 0; k < i; k++)
		curr = curr->getNext();
	curr->setData(data);
	return true; 
}

/*
 * DNode<T> implementation
 */

 template <typename T>
 DNode<T>::DNode(T data){
 	this->data = data; 
 	this->prev = this->next = NULL; 
 }

 template <typename T>
 bool DNode<T>::setData(T data){
 	this->data = data;
 	return (this->data == data); 
 }

 template <typename T>
 bool DNode<T>::setNext(DNode<T>* next){
 	this->next = next; 
 	return (this->next == next); 
 }

 template <typename T>
 bool DNode<T>::setPrev(DNode<T>* prev){
 	this->prev = prev;
 	return (this->prev == prev); 
 }

 template <typename T>
 T DNode<T>::getData(){
 	return this->data; 
 }

 template <typename T>
 DNode<T>* DNode<T>::getNext(){
 	return this->next;
 }

 template <typename T>
 DNode<T>* DNode<T>::getPrev(){
 	return this->prev;
 }

/*
 * DList<T> implementation
 */

 template <typename T>
 bool DList<T>::clearList(DNode<T>* node){
 	if( node == NULL)
		return;
	if(node->getNext() != NULL)
		clearTree(node->getNext());
	delete node; 
	return true; 
 }

 template <typename T>
 DNode<T>* DList<T>::duplicateNode(DNode<T>* node){
 	DNode<T>* newNode = new DNode<T>(node->getData());
 	return newNode; 
 }

 template <typename T>
 bool DNode<T>::printAll(DNode<T>* node){

 }

 template <typename T>
 DList<T>::DList(){
 	this->head = NULL; 
 	this->tail = NULL;
 	this->numNodes = 0;
 }

 template <typename T>
 DList<T>::~DList(){
 	this->clearList(this->getHead());
 	return; 
 }

 template <typename T>
 DNode<T>* DNode<T>::getHead(){
 	return this->head; 
 }

 template <typename T>
 DNode<T>* DNode<T>::getTail(){
 	return this->tail; 
 }

 template <typename T>
 bool DNode<T>::setHead(DNode<T>* newRoot){
 	this->head = newRoot;
 	return (this->head == newRoot); 
 }

 template <typename T>
 bool DNode<T>::setTail(DNode<T>* newTail){
 	this->tail = newTail; 
 	return (this->tail == newTail); 
 }

 template <typename T>
 bool DNode<T>::isEmpty(){
 	return (this->numNodes == 0); 
 }

 template <typename T>
 DNode<T>* DNode<T>::searchList(T data){
	DNode<T>* curr = this->getHead(); 
	while((curr != NULL) && (curr->getData() !=  data))
		curr = curr->getNext();
	if(curr == NULL)
		return curr;
	else return duplicateNode(curr);
 }

 template <typename T>
 bool DNode<T>::insert(DNode<T>* newNode){
 	SNode<T>* curr = this->getHead(); 
	if(curr == NULL){
		this->setHead(newNode);
		this->numNodes++;  
		return (this->getHead() == newNode); 
	}
	while(curr->getNext() != NULL)
		curr = curr->getNext(); 
	curr->setNext(newNode);
	this->numNodes++;
	return (curr->getNext() == newNode); 
 }