#pragma once
#include<iostream>
#include<limits>
#include<stack>
class DoubleProbingTechinque // close-hashing-(no extra space)
{
	int capacity;
	int length;
	int* hashTable;
	int GetHashIndex(int key);
	void DoubleCapacity();
	void ReInsert();
public:

	DoubleProbingTechinque();
	~DoubleProbingTechinque();
	void Clear();

	int GetLength();
	void Insert(int key);
	bool IsExist(int key);
	void Delete(int key);
	void Display();

	static void TestBehavior();
};

