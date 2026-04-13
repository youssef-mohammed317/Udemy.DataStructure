#pragma once
#include "Node.h"
#include<stdexcept>
#include<iostream>
#include<queue>
#include<stack>
using namespace std;
class BinaryTree
{
	Node* root;
	void RClear(Node* node);
	Node* RSearch(Node* node, int val);
	void RCountByDegree(Node* node, int degree, int& count);
	int GetHeight(Node* node);
	void RPostDisplay(Node* node);
	void RPreDisplay(Node* node);
	void RInDisplay(Node* node);

public:
	BinaryTree();
	~BinaryTree();
	void IClear();
	void RClear();

	void IInsert(int data);

	Node* RSearch(int val);
	Node* ISearch(int val);

	void RDelete(int val);
	void IDelete(int val);



	int GetMaxDegree();
	int GetHeight();
	int CountNodes();
	int CountInternal();
	int CountExternal();
	int ICountByDegree(int degree);
	int RCountByDegree(int degree);

	void RPostDisplay();
	void IPostDisplay();
	void RPreDisplay();
	void IPreDisplay();
	void RInDisplay();
	void IInDisplay();
	void RLevelDisplay();
	void ILeveLDisplay();

	static void TestBehavior();
};

