#pragma once
#include<stack>
#include<stdexcept>
#include<iostream>
using namespace std;
class QueueBy2Stack
{
	stack<int> s1, s2;
	int size;
public:
	QueueBy2Stack();
	~QueueBy2Stack();
	void Clear();

	void Enqueue(int data);
	int Dequeue();

	bool IsFull();
	bool IsEmpty();

	void Display();
	int First();
	int Last();
	int Size();

	static void TestBehavior();
};

