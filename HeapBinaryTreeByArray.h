#pragma once
// complete
// min or max
// delete only largest or smallest
// swap with parent in inserting
// heapify:related to the creation
//			insert: as leaf then compare // direction of adjustment is up
//			delete: delete root then move leaf to its place then comapare until go to leaf // direction of adjustment is down
#include<iostream>
class HeapBinaryTreeByArray
{
	bool maxHeap;
	int capacity;
	int length;
	int* arr;
	void DoubleCapacity();
	void Swap(int& x, int& y);
public:
	HeapBinaryTreeByArray(bool maxHeap = true);
	~HeapBinaryTreeByArray();

	void Clear();
	bool IsEmpty();
	void Insert(int val);
	void Delete();
	int GetLength();
	int* Sort();
	void Display();

	static void TestBehavior();
};

