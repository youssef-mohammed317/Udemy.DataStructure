#pragma once
#include "Node.h"
#include<iostream>
#include<stdexcept>
#include<queue>
#include<stack>
using namespace std;
class BinarySearchTree
{
	Node* root;
public:
	BinarySearchTree();
	~BinarySearchTree();

	void ILevelClear();
	void IPreClear();
	void IInClear();
	void IPostClear();

	void IInsert(int val);
	void IDelete(int val);
	Node* ISearch(int val);

	int GetHeight();
	int CountNodes(int degree);
	void IInDisplay();
	void RInDisplay();

	static void TestBehavior();
};

