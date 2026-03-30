#pragma once
#include "Node.h"
#include <stdexcept>
#include<iostream>
using namespace std;
class Queue
{
	Node* rear;
	Node* front;
	int size;
public:
	Queue();
	~Queue();
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

