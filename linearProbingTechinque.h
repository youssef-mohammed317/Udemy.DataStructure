#pragma once
#include<iostream>
#include<limits>
#include<stack>
class linearProbingTechinque // close-hashing-(no extra space)
{
	int capacity;
	int length;
	int* hashTable;
	int GetHashIndex(int key);
	void DoubleCapacity();
	void ReInsert();
public:

	linearProbingTechinque();
	~linearProbingTechinque();
	void Clear();

	int GetLength();
	void Insert(int key);
	bool IsExist(int key);
	void Delete(int key);
	void Display();

	static void TestBehavior();
};
