#pragma once
#include "DoublyNode.h"
#include<iostream>
#include<stdexcept>
#include<stack>
using namespace std;
class DoublyLinkedList
{
	DoublyNode* head;
	DoublyNode* tail;
	int length;

public:
	DoublyLinkedList();
	void Clear();
	~DoublyLinkedList();

	void Append(int data);
	void Insert(int pos, int data);
	void Delete(int pos);
	void Reverse();
	void ReverseWithTwoPointers();
	void Display();
	void DisplayReverse();
	int GetLength();

	DoublyNode* GetMiddleNode();
	int GetMiddleValue();
	DoublyNode* GetMiddleNodeUsingOnePointerUsingStack();

	DoublyNode* GetIntersectionNodeUsingStack(DoublyLinkedList* other);

	static void TestBehavior();

};

