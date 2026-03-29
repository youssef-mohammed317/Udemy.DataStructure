#pragma once
#include "Node.h"
#include<iostream>
#include<stdexcept>
using namespace std;

class CircularLinkedList
{
	Node* head;
	Node* tail;
	int length;
public:
	CircularLinkedList();
	void Clear();
	~CircularLinkedList();

	void Append(int data);
	void Insert(int pos, int data);
	void Delete(int pos);

	void Display();

	static void TestBehavior();
};

