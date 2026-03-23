#pragma once
#include<iostream>
#include <climits>

#include <stdexcept>
using namespace std;
class Node {
	int data;
	Node* next;
public:
	Node(int data = 0, Node* next = nullptr);
	~Node();

	void SetData(int data);
	int GetData();
	Node* GetNext();
	void SetNext(Node* next);

};

class LinkedList
{
	int length;
	Node* head;
	void RDisplay(Node* temp);
	int RSum(Node* temp);
	int RMax(Node* temp, int currentMax);
	int R2Max(Node* temp);
public:
	LinkedList();
	~LinkedList();
	int GetLength();
	void Append(int data);
	void Display();
	void RDisplay();
	int Sum();
	int RSum();

	int Max();
	int RMax();
	int R2Max();


	static void TestBehavior();
};

