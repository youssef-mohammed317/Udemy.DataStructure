#pragma once
#include "Node.h"
#include<stdexcept>
#include<iostream>
using namespace std;

class ElementPriorityQueue // greater the number greater the priority
{
	Node* head;
	Node* tail;
	int size;
public:
	ElementPriorityQueue();
	~ElementPriorityQueue();
	void Clear();

	void Enqueue(int data);
	int Dequeue();
	bool IsFull();
	bool IsEmpty();

	void Display();
	static void TestBehavior();


};

