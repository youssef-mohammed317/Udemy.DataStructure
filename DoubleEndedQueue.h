#pragma once
#include "Node.h"
#include<iostream>
#include <stdexcept>
using namespace std;
class DoubleEndedQueue
{
	Node* rear;
	Node* front;
	int size;
public:
	DoubleEndedQueue();
	~DoubleEndedQueue();
	void Clear();

	void EnqueueFromRear(int data);
	void EnqueueFromFront(int data);
	int DequeueFromFront();
	int DequeueFromRear();

	bool IsFull();
	bool IsEmpty();

	void Display();
	int First();
	int Last();
	int Size();

	static void TestBehavior();
};

