#pragma once
#include "Queue.h"
enum PeriorityNumber
{
	ALL = 0,
	LOW = 1,
	HIGH = 2,
	HIGHEST = 3
};

class PriorityQueue
{
	Queue low;
	Queue high;
	Queue highest;
	int size;
public:
	PriorityQueue();
	~PriorityQueue();
	void Clear();

	void Enqueue(int data, PeriorityNumber periority = LOW);

	int Dequeue();

	bool IsFull(PeriorityNumber periority = ALL);
	bool IsEmpty(PeriorityNumber periority = ALL);

	void Display();
	int First();
	int Last();
	int Size();

	static void TestBehavior();
};

