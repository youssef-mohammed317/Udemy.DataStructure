#pragma once
#include "Node.h"
#include "LinkedListNode.h"
#include<queue>
#include<iostream>
using namespace std;
class HeapBinaryTree
{
	Node* root;
	bool maxHeap;
	void Clear(Node* ptr);
	void Insert(Node* ptr, int val);
	int GetHeight(Node* ptr);
	bool IsPerfect(Node* ptr);
	Node* Search(Node* ptr, int val);
	void Rearrange(Node* ptr);
public:
	HeapBinaryTree(bool maxHeap = true);
	~HeapBinaryTree();

	void Clear();
	void Insert(int val);
	Node* Search(int val);
	Node* Delete();
	int GetHeight();
	bool IsPerfect();
	LinkedListNode* GetSortedLinkedList();
	void Display();

	static void TestBehavior();
};

