#pragma once
#include "Node.h"
#include<iostream>
class AVLBinarySearchTree
{
	Node* root;

	int GetHeight(Node* ptr);
	int GetBalanceFactor(Node* ptr);
	void Clear(Node* ptr);

	Node* LLRotation(Node* ptr);
	Node* LRRotation(Node* ptr);
	Node* RLRotation(Node* ptr);
	Node* RRRotation(Node* ptr);

	Node* Insert(Node* ptr, int val);
	Node* Delete(Node* ptr, int val);

	void Display(Node* ptr);

public:
	AVLBinarySearchTree();
	~AVLBinarySearchTree();
	void Clear();

	void Insert(int val);
	void Delete(int val);

	void Display();

	static void TestBehavior();
};

