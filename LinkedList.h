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
	Node* RSearch(Node* temp, int key);
	Node* RSearchAndMoveToFront(Node* temp, Node* prev, int key);
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

	Node* Search(int key);
	Node* RSearch(int key);
	Node* SearchAndMoveToFront(int key);
	Node* RSearchAndMoveToFront(int key);




	static void TestBehavior();
};

