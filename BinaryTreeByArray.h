#pragma once
#include<limits.h>
#include<iostream>
#include<queue>
#include<stack>
using namespace std;
class BinaryTreeByArray
{
	int* arr;
	int rear;
	int capacity;
	void DoubleCapacity();
	int GetHeight(int parentIndex);
	void RPreDisplay(int parentIndex);
	void RInDisplay(int parentIndex);
	void RPostDisplay(int parentIndex);
	void RLevelDisplay(int low, int high);

public:
	BinaryTreeByArray();
	~BinaryTreeByArray();

	bool IsEmpty();
	void Clear();
	bool IsExist(int val);
	void Insert(int val);
	void Delete(int val);

	int GetMaxDegree();
	int GetHeight();
	int CountNodes();
	int CountInternal();
	int CountExternal();
	int CountByDegree(int degree);


	bool IsStrict();
	bool IsComplete();
	bool IsFull();

	void RLevelDisplay();
	void RPreDisplay();
	void RInDisplay();
	void RPostDisplay();

	void ILevelDisplay();
	void IQueueLevelDisplay();
	void IPreDisplay();
	void IInDisplay();
	void IPostDisplay();


	static void TestBehavior();
};

