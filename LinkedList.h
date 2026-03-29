#pragma once

#include<iostream>
#include <climits>
#include<string>
#include <stdexcept>
#include "Node.h"
using namespace std;

class LinkedList
{
	int length;
	Node* head;
	Node* tail; //added for insert last

	void RDisplay(Node* temp);
	int RSum(Node* temp);
	int RMax(Node* temp, int currentMax);
	int R2Max(Node* temp);
	Node* RSearch(Node* temp, int key);
	Node* RSearchAndMoveToFront(Node* temp, Node* prev, int key);
	void RInsert(Node* temp, int index, int pos, int data);
	void RReverseLinks(Node* prev, Node* curr);
	void RReverseLinksCourseMethod(Node* prev, Node* curr);

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

	void Insert(int pos, int data);
	void RInsert(int pos, int data);
	void InsertLastUsingTail(int data);

	void InsertInSortedAsc(int data);
	bool CheckSortedAsc();
	void RemoveDuplicatesInSortedAscList();
	void Delete(int pos);

	void ReverseLinks();
	void ReverseLinksCourseMethod();
	void ReverseElements();
	void RReverseLinks();
	void RReverseLinksCourseMethod();

	bool IsLoop();
	void ConcatWith(LinkedList* other);
	void Clear();
	void MergeWith(LinkedList* other); // merge need to be sorted

	static void TestBehavior();
};

