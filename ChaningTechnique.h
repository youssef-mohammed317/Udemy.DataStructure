#pragma once
#include "Node.h"
#include<iostream>
class ChaningTechnique // open-hashing
{
	int size;
	int length;
	Node** hashTable;
	int GetHashIndex(int key);
public:

	ChaningTechnique();
	~ChaningTechnique();
	void Clear();

	int GetLength();
	void Insert(int key);
	bool IsExist(int key);
	void Delete(int key);
	void Display();

	static void TestBehavior();
};

