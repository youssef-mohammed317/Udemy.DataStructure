#pragma once
#include <stdexcept>
#include<iostream>
using namespace std;
class CircularQueue
{
	int rear;
	int front;
	int size;
	int length;
	int* arr;
public:
	CircularQueue(int size);
	~CircularQueue();
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



