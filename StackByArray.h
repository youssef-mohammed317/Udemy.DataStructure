#pragma once
#include<stdexcept>
#include<iostream>
class StackByArray
{
	int length;
	int size;
	int* arr;
	int top;
public:
	StackByArray(int size);
	~StackByArray();

	void Clear();
	int Top();
	void Pop();
	int Size();
	int Length();
	void Push(int data);
	bool IsFull();
	bool IsEmpty();
	void Display();
	int Peek(int pos);

	static void TestBehavior();
};

