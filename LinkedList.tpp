#include <iostream>
#include "LinkedList.hpp"

using namespace std; 

/*
 * LinkedNode<T> implementations
 */

template <typename T>
LinkedNode<T>::LinkedNode(T data){
	this->data = data; 
	this->next = NULL; 
}

template <typename T>
bool LinkedNode<T>::setData(T data){
	this->data = data;
	return (this->data == data); 
}

template <typename T>
bool LinkedNode<T>::setNext(LinkedNode<T>* node){
	this->next = node;
	return (this->next == node); 
}

template <typename T>
T LinkedNode<T>::getData(){
	return this->data; 
}

template <typename T>
LinkedNode<T>* LinkedNode<T>::getNext(){
	return this->next; 
}

/*
 * List<T> implementation
 */

template <typename T>
bool List<T>::clearList(LinkedNode<T>* node){
	if( node == NULL)
		return;
	if(node->getNext() !=NULL)
		clearTree(node->getNext());
	delete node; 
	this->numNodes = 0;
	return (this->numNodes == 0); 
} 

template <typename T>
LinkedNode<T>* List<T>::duplicateNode(LinkedNode<T>* node){
	LinkedNode<T>* dupNode = new LinkedNode<T>(node->getData()); 
	return dupNode; 
}

template <typename T>
bool List<T>::printAll(LinkedNode<T>* node){
	if(node != NULL){
		printOne(node);
		printAll(node->getNext());
	}
	return (node != NULL); 
}

template <typename T>
List<T>::List(){
	this->head = NULL;
	this->numNodes = 0;
	return; 
} 

template <typename T>
List<T>::~List(){
	clearList(head);
	return; 
}

template <typename T>
LinkedNode<T>* List<T>::getHead(){
	return this->head; 
}

template <typename T>
bool List<T>::setHead(LinkedNode<T>* newHead){
	this->head = newHead;
	return (this->head == newHead); 
}

template <typename T>
bool List<T>::isEmpty(){
	return (this->getHead() == NULL);
}

template <typename T>
LinkedNode<T>* List<T>::searchList(T data){
	LinkedNode<T>* curr = this->getHead(); 
	while((curr != NULL) && (curr->getData() !=  data))
		curr = curr->getNext();
	if(curr == NULL)
		return curr;
	else return duplicateNode(curr);
}

template <typename T>
bool List<T>::insert(LinkedNode<T>* newNode){
	LinkedNode<T>* curr = this->getHead(); 
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
bool List<T>::insert(T data){
	LinkedNode<T>* newNode = new LinkedNode<T>(data);
	return this->insert(newNode); 
}
//You might need to fix this
template <typename T>
bool List<T>::deleteNode(T data){
	LinkedNode<T>* curr = this->getHead();
	LinkedNode<T>* prev = NULL;  
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
LinkedNode<T>* List<T>::findMin(){
	LinkedNode<T>* currMin = this->getHead();
	LinkedNode<T>* curr = this->getHead();
	while(curr->getNext() != NULL){
		curr = curr->getNext();
		if(curr->getData() < currMin->getData())
			currMin = curr;
	}
	return currMin; 
}

template <typename T>
LinkedNode<T>* List<T>::findMax(){
	LinkedNode<T>* currMax = this->getHead();
	LinkedNode<T>* curr = this->getHead();
	while(curr->getNext() != NULL){
		curr = curr->getNext();
		if(curr->getData() > currMax->getData())
			currMax = curr;
	}
	return currMax; 
}

template <typename T>
int List<T>::getNumNodes(){
	return this->numNodes; 
}

template <typename T>
bool List<T>::printOne(LinkedNode<T>* node){
	cout << node << endl;
	return true; 
}

template <typename T>
bool List<T>::printList(){
	cout << this << endl; 
	printAll(this->getHead()); 
	return true;  
}

template <typename T>
LinkedNode<T>* List<T>::get(int n){
	if(!(n < this->getNumNodes()))
		return NULL;
	LinkedNode<T>* curr = this->getHead();
	for(int i = 0; i < n; i++)
		curr  = curr->getNext();

	return this->duplicateNode(curr); 
}

template <typename T>
bool List<T>::set(int i, T data){
	if(!(i < this->getNumNodes()))
		return false;
	LinkedNode<T>* curr = this->getHead();
	for(int k = 0; k < i; k++)
		curr = curr->getNext();
	curr->setData(data);
	return true; 

}