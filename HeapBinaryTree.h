#pragma once
#include "Node.h"

class HeapBinaryTree
{
	Node* root;
	bool maxHeap;
public:
	HeapBinaryTree(bool maxHeap = true);
	~HeapBinaryTree();

	void Clear();
	void Insert(int val);
	Node* Search(int val);
	void Delete();

	void Display();

	static void TestBehavior();
};

