#include <iostream>
#include "BinarySearchTree.hpp"

using namespace std; 

template<class T>
void Node<T>::setData(T data){
	this->data = data; 
}

template<class T>
void Node<T>::setRight(Node<T>* node){
	this->right = node; 
}

template<class T>
void Node<T>::setLeft(Node<T>* node){
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
}

template<class T>
BinarySearchTree<T>::~BinarySearchTree(){
	clearTree(root);
}

template<class T>
Node<T>* BinarySearchTree<T>::getRoot(){
	return this->root; 
}

template<class T>
void BinarySearchTree<T>::setRoot(Node<T>* newRoot){
	this->root = newRoot; 
}

template<class T>
void BinarySearchTree<T>::clearTree(Node<T>* t){
	if(t == NULL)
		return; 
	if(t->left != NULL)
		clearTree(t->left); 
	if(t->right != NULL)
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
	while((temp != NULL) &&  (temp->getData() != data))
		if(data <= temp->getData())
			temp = temp->getLeft(); 
		else temp = temp->getRight();

	if(temp == NULL)
		return temp;
	else return duplicateNode(temp); 
}

template<class T>
bool BinarySearchTree<T>::insert(Node<T>* newNode){
	Node<T>* temp; 
	Node<T>* prev; 
	temp = root; 
	prev = NULL; 

	while(temp != NULL){
		prev = temp;
		if(newNode->getData() <= temp->getData())
			temp = temp->getLeft(); 
		else temp = temp->getRight(); 
	}

	if(prev == NULL)
		root = newNode; 
	else
{		if(newNode->getData() <= prev->getData())
			prev->setLeft(newNode); 
		else prev->setRight(newNode); 
	}
	this->numNodes++; 
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
	Node<T>* prev; 
	Node<T>* temp; 
	Node<T>* delParent; 
	Node<T>* delNode;

	temp = this->getRoot(); 
	prev = NULL; 

	while((temp != NULL) && (data != temp->getData())){
		prev = temp; 
		if(data <= temp->getData())
			temp = temp->getLeft(); 
		else temp = temp->getRight(); 
	} 

	if(temp == NULL){
		return false; 
	}
	else{
		if(temp == this->getRoot()){
			delNode = this->getRoot(); 
			delParent = NULL; 
		}
		else{
			delNode = temp; 
			delParent = prev; 
		}
	}

	if(delNode->getRight() == NULL){
		if(delParent == NULL){
			this->setRoot(delNode->getLeft());
			delete delNode; 
			this->numNodes--; 
			return true; 
		}
		else{
			if(delParent->getLeft() == delNode)
				delParent->setLeft(delNode->getLeft());
			else delParent->setRight(delNode->getLeft());
			delete delNode; 
			this->numNodes--; 
			return true; 
		}
	}
	else{
		if(delNode->getLeft() == NULL){
			if(delParent == NULL){
				this->setRoot(delNode->getRight()); 
				delete delNode; 
				this->numNodes--; 
				return true; 
			}
			else{
				if(delParent->getLeft() == delNode)
					delParent->setLeft(delNode->getRight());
				else delParent->setRight(delNode->getRight());
				delete delNode;
				this->numNodes--; 
				return true; 
			}
		}
		else{
			temp = delNode->getLeft(); 
			prev = delNode; 
			while(temp->getRight() != NULL){
				prev = temp; 
				temp = temp->getRight();
			}
			delNode->setData(temp->getData());

			if(prev == delNode)
				prev->setLeft(temp->getLeft());
			else prev->setRight(temp->getRight());
			delete temp;
			this->numNodes--; 
			return true; 
		}
	}
}

template<class T>
Node<T>* BinarySearchTree<T>::findMin(){
	Node<T>* current = this;
	while(current->getLeft() != NULL)
		current = current->getLeft(); 
	return current; 
}

template<class T>
Node<T>* BinarySearchTree<T>::findMax(){
	Node<T>* current = this; 
	while(current->getRight() != NULL)
		current = current->getRight();
	return current; 
}

template<class T>
int BinarySearchTree<T>::getNumNodes(){
	return this->numNodes; 
}

template<class T>
void BinarySearchTree<T>::printOne(Node<T>* node){
	cout << node << endl;
}

template<class T>
void BinarySearchTree<T>::printAll(Node<T>* node){
	if(node != NULL){
		printAll(node->getLeft());
		printOne(node); 
		printAll(node->getRight()); 
	}
}

template<class T>
void BinarySearchTree<T>::printTree(){
	cout << this << endl; 
	printAll(this->getRoot()); 
}