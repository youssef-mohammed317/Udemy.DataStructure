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
	void RLevelClear(Node* ptr, int level);
	void RPreClear(Node* ptr);
	void RInClear(Node* ptr);
	void RPostClear(Node* ptr);
	int RGetHeight(Node* ptr);
	int RCountNodes(Node* ptr, int degree);
	void RInDisplay(Node* ptr);
	void RInsert(Node* ptr, int val);
	Node* RSearch(Node* ptr, int val);

public:
	BinarySearchTree();
	~BinarySearchTree();

	void ILevelClear();
	void IPreClear();
	void IInClear();
	void IPostClear();

	void RLevelClear();
	void RPreClear();
	void RInClear();
	void RPostClear();

	void IInsert(int val);
	void RInsert(int val);
	void IDelete(int val);
	void RDelete(int val);
	Node* ISearch(int val);
	Node* RSearch(int val);

	int RGetHeight();
	int IGetHeight();
	int RCountNodes(int degree);
	int ICountNodes(int degree);

	void IInDisplay();
	void RInDisplay();


	static void TestBehavior();
};

