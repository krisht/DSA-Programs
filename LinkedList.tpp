#include <iostream>
#include "BinarySearchTree.hpp"

using namespace std; 

template <typename T>
LinkedNode<T>::LinkedNode(T data){
	this->data = data; 
	this->next = NULL
}

template <typename T>
void LinkedNode<T>::setData(T data){
	this->data = data;
}

template <typename T>
void LinkedNode<T>::setNext(LinkedNode<T>* node){
	this->next = next; 
}

template <typename T>
T LinkedNode<T>::getData(){
	return this->data; 
}

template <typename T>
LinkedNode<T>* getNext(){
	return this->next; 
}

/*
 * List implementation
 */

template <typename T>
List<T>::List(){
	this->head = NULL;
	this->numNodes = 0; 
} 

template <typename T>
List<T>::~List(){
	clearList(head);
}

template <typename T>
LinkedNode<T>* List<T>::getHead(){
	return this->head; 
}

template <typename T>
void List<T>::setHead(LinkedNode<T>* newHead){
	this->head = newHead; 
}

template <typename T>
bool List<T>::isEmpty(){
	return (this->getHead() == NULL);
}

template <typename T>
LinkedNode<T>* List<T>::searchTree(T data){
	LinkedNode<T>* curr = this->getHead();
	while(curr->getData() != data)
		curr = curr->getNext();
	return curr; 
}

template <typename T>
bool List<T>::insert(LinkedNode<T>* newNode){
	LinkedNode<T>* curr = this->getHead(); 
	while(curr->getNext() != NULL)
		curr = curr->getNext(); 
	curr->setNext(newNode);

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
	while(curr->getData() != data && curr->getNext() != NULL)
		prev = curr; 
		curr = curr->getNext();

	if(curr == NULL)
		return false; 
	else{
		if(prev == NULL){
			this->setHead(curr->getNext());
			curr->setNext(NULL);
			curr->setData(N
				ULL)
			delete curr; 
			return true; 
		}
		else if(curr->getNext() == NULL){
			prev->setNext(NULL);
			curr->setNext(NULL);
			curr->setData(NULL); 
			delete curr; 
			return true; 
		}
		else {
			prev->setNext(curr->getNext());
			curr->setNext(NULL); 
			curr->setData(NULL);
			delete curr; 
			return true; 
		}
	}
}

LinkedNode<T>* List<T>::findMin(){
	LinkedNode<T>* currMin = this->getHead();
	LinkedNode<T>* curr = this->getHead();

	while(curr->getNext() != NULL){
		curr= curr->getNext();
		if(curr->getData() < currMin->getData())
			currMin = curr;
	}

	return currMin; 
}

LinkedNode<T>* List<T>::findMax(){
	LinkedNode<T>* currMin = this->getHead();
	LinkedNode<T>* curr = this->getHead();
	while(curr->getNext() != NULL){
		curr= curr->getNext();
		if(curr->getData() > currMin->getData())
			currMin = curr;
	}
	return currMin; 
}

template <typename T>
int List<T>::getNumNodes(){
	return this->numNodes; 
}

template <typename T>
void List<T>::printOne(LinkedNode<T>* node){
	cout << node << endl; 
}

template <typename T>
void List<T>::printList(){
	LinkedNode<T>* node = this->getHead(); 
}
