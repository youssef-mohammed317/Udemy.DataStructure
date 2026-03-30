#pragma once
#include "Node.h"
#include<stdexcept>
#include<iostream>
class Stack
{
	Node* top;
	int size;
public:
	Stack();
	~Stack();
	void Clear();
	int Top();
	void Pop();
	int Size();
	void Push(int data);
	bool IsFull();
	bool IsEmpty();
	void Display();
	int Peek(int pos);

	static void TestBehavior();
};

