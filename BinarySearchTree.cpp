#include <iostream>
#include "BinarySearchTree.hpp"

using namespace std; 

template<class T>
void Node<T>::setData(T data){
	this->data = data; 
}

template<class T>
void Node<T>::setRight(Node* node){
	this->right = node; 
}

template<class T>
void Node<T>::setLeft(Node* node){
	this->left = node; 
}

template<class T>
T Node<T>::getData(){
	return this->data;  
} 

template<class T>
Node<T>* Node<T>::getLeft(){
	return this->left; 
}

template<class T>
Node<T>* Node<T>::getRight(){
	return this->right;
}

/*
 * Binary Tree implementation
 */
template<class T>
BinarySearchTree<T>::BinarySearchTree(){
	root = NULL; 
	return; 
}

template<class T>
BinarySearchTree<T>::~BinarySearchTree(){
	clearTree(root); 
	return; 
}

template<class T>
void BinarySearchTree<T>::clearTree(Node<T>* t){
	if(t == NULL)
		return; 
	if(t->left !=NULL)
		clearTree(t->left); 
	if(t->right !=NULL)
		clearTree(t->right); 
	delete t; 
	return; 
}

template<class T>
bool BinarySearchTree<T>::isEmpty(){
	return (this->root == NULL); 
}

template<class T>
Node<T>* BinarySearchTree<T>::duplicateNode(Node<T>* t){
	Node<T>* dupNode; 
	dupNode = new Node<T>(); 
	dupNode->setData(t->getData()); 
	dupNode->setLeft(NULL); 
	dupNode->setRight(NULL); 
	return dupNode; 
}

template<class T>
Node<T>* BinarySearchTree<T>::searchTree(T data){
	Node<T>* temp; 
	temp = this->root; 
	while((temp!=NULL) &&  (temp->getData() != data))
		if(data < temp->getData())
			temp = temp->getLeft(); 
		else temp = temp->getRight();

	if(temp == NULL)
		return temp;
	else return duplicateNode(temp); 
}

template<class T>
bool BinarySearchTree<T>::insert(Node<T>* newNode){
	Node<T>* temp; 
	Node<T>* back; 
	temp = root; 
	back = NULL; 

	while(temp != NULL){
		back = temp;
		if(newNode->getData() < temp->getData())
			temp = temp->getLeft(); 
		else temp = temp->getRight(); 
	}

	if(back == NULL)
		root = newNode; 
	else
{		if(newNode->getData() < back->getData())
			back->setLeft(newNode); 
		else back->setRight(newNode); 
	}
	return true; 
}

template<class T>
bool BinarySearchTree<T>::insert(T data){
	Node<T>* newNode; 
	newNode = new Node<T>(); 
	newNode->setData(data);
	newNode->setLeft(NULL); 
	newNode->setRight(NULL); 
	return insert(newNode); 
}

template<class T>
bool BinarySearchTree<T>::deleteNode(T data){
	
}

template<class T>
Node<T>* BinarySearchTree<T>::findMin(){
	Node<T>* current = this;
	while(current->getLeft() !=NULL)
		current = current->getLeft(); 
	return current; 
}

template<class T>
Node<T>* BinarySearchTree<T>::getRoot(){
	return this->root; 
}

template<class T>
