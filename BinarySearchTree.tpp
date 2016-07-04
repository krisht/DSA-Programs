#include <iostream>
#include "BinarySearchTree.hpp"

using namespace std; 

template<typename T>
BSTNode<T>::BSTNode(T data){
	this->data = data; 
	this->left = this->right = NULL; 
}

template<typename T>
void BSTNode<T>::setData(T data){
	this->data = data; 
}

template<typename T>
void BSTNode<T>::setRight(BSTNode<T>* node){
	this->right = node; 
}

template<typename T>
void BSTNode<T>::setLeft(BSTNode<T>* node){
	this->left = node; 
}

template<typename T>
T BSTNode<T>::getData(){
	return this->data;  
} 

template<typename T>
BSTNode<T>* BSTNode<T>::getLeft(){
	return this->left; 
}

template<typename T>
BSTNode<T>* BSTNode<T>::getRight(){
	return this->right;
}

/*
 * Binary Tree implementation
 */
template<typename T>
BinarySearchTree<T>::BinarySearchTree(){
	root = NULL;
	return; 
}

template<typename T>
BinarySearchTree<T>::~BinarySearchTree(){
	clearTree(root);
	return;
}

template<typename T>
BSTNode<T>* BinarySearchTree<T>::getRoot(){
	return this->root; 
}

template<typename T>
void BinarySearchTree<T>::setRoot(BSTNode<T>* newRoot){
	this->root = newRoot; 
}

template<typename T>
void BinarySearchTree<T>::clearTree(BSTNode<T>* t){
	if(t == NULL)
		return; 
	if(t->getLeft() != NULL)
		clearTree(t->getLeft()); 
	if(t->getRight() != NULL)
		clearTree(t->getRight()); 
	delete t; 
	return; 
}

template<typename T>
bool BinarySearchTree<T>::isEmpty(){
	return (this->getRoot() == NULL); 
}

template<typename T>
BSTNode<T>* BinarySearchTree<T>::duplicateNode(BSTNode<T>* t){
	BSTNode<T>* dupNode; 
	dupNode = new BSTNode<T>(t->getData()); 
	return dupNode; 
}

template<typename T>
BSTNode<T>* BinarySearchTree<T>::searchTree(T data){
	BSTNode<T>* temp; 
	temp = this->getRoot(); 
	while((temp != NULL) && (temp->getData() != data))
		if(data <= temp->getData())
			temp = temp->getLeft(); 
		else temp = temp->getRight();

	if(temp == NULL)
		return temp;
	else return duplicateNode(temp); 
}

template<typename T>
bool BinarySearchTree<T>::insert(BSTNode<T>* newNode){
	BSTNode<T>* temp; 
	BSTNode<T>* prev; 
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

template<typename T>
bool BinarySearchTree<T>::insert(T data){
	BSTNode<T>* newNode; 
	newNode = new BSTNode<T>(data);
	return insert(newNode); 
}

template<typename T>
bool BinarySearchTree<T>::deleteNode(T data){
	BSTNode<T>* prev; 
	BSTNode<T>* temp; 
	BSTNode<T>* delParent;
	BSTNode<T>* delNode;

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

template<typename T>
BSTNode<T>* BinarySearchTree<T>::findMin(){
	BSTNode<T>* current = this->getRoot();
	while(current->getLeft() != NULL)
		current = current->getLeft(); 
	return current; 
}

template<typename T>
BSTNode<T>* BinarySearchTree<T>::findMax(){
	BSTNode<T>* current = this->getRoot(); 
	while(current->getRight() != NULL)
		current = current->getRight();
	return current; 
}

template<typename T>
int BinarySearchTree<T>::getNumNodes(){
	return this->numNodes; 
}

template<typename T>
void BinarySearchTree<T>::printOne(BSTNode<T>* node){
	cout << node << endl; 
}

template<typename T>
void BinarySearchTree<T>::printAll(BSTNode<T>* node){
	if(node != NULL){
		printAll(node->getLeft());
		printOne(node); 
		printAll(node->getRight()); 
	}
}

template<typename T>
void BinarySearchTree<T>::printTree(){
	cout << this << endl; 
	printAll(this->getRoot()); 
}