#pragma once
#include<iostream>
#include<stdexcept>
#include "Node.h"
struct MinMax
{
	int min;
	int max;
};
struct List {
	Node* tail = nullptr;
	Node* head = nullptr;
public:
	bool IsEmpty() {
		return head == nullptr;
	}
	void Append(int data)
	{
		Node* node = new Node(data);
		if (head == nullptr)
		{
			head = tail = node;
		}
		else {
			tail->SetNext(node);
			tail = node;
		}
	}
	void InsertFirst(int data)
	{
		head = new Node(data, head);
		if (tail == nullptr)
			tail = head;
	}
	int Front()
	{
		if (IsEmpty()) throw std::runtime_error("List is empty");
		int data = head->GetData();
		Node* temp = head;
		head = head->GetNext();
		delete temp;
		if (head == nullptr)
			head = tail = nullptr;

		return data;
	}
};

class SortingTechnique
{
	static void Swap(int& x, int& y);
	static MinMax GetMinMax(int* arr, int size);
	static void IMergeDescending(int* arr, int low, int mid, int high);
	static void IMergeAscending(int* arr, int low, int mid, int high);
	static void PrintArray(int* arr, int size);
	static void RMergeAscending(int* arr, int low, int high);
	static void RMergeDescending(int* arr, int low, int high);
	static void QuickAscending(int* arr, int low, int high);
	static void QuickDescending(int* arr, int low, int high);
public:
	static void BubbleAscending(int* arr, int size); // O(n^2)
	static void BubbleDescending(int* arr, int size); // O(n^2)

	static void InsertionAscending(int* arr, int size); // O(n^2)
	static void InsertionDescending(int* arr, int size);// O(n^2)

	static void SelectionAscending(int* arr, int size);// O(n^2)
	static void SelectionDescending(int* arr, int size);// O(n^2)

	static void CountAscending(int* arr, int size);// O(n)
	static void CountDescending(int* arr, int size);// O(n)

	static void BinBucketAscending(int* arr, int size);// O(n)
	static void BinBucketDescending(int* arr, int size);// O(n)

	static void RadixAscending(int* arr, int size);//O(n)
	static void RadixDescending(int* arr, int size);//O(n)

	static void ShellAscending(int* arr, int size);// O(n^2) - O(n^1.6) - O(n^1,25) - O(nlog(n))
	static void ShellDescending(int* arr, int size);// O(n^2) - O(n^1.6) - O(n^1,25) - O(nlog(n))

	static void IMergingAscending(int* arr, int size); // O(nlog(n))
	static void IMergingDescending(int* arr, int size);// O(nlog(n))

	static void RMergingAscending(int* arr, int size); // O(nlog(n))
	static void RMergingDescending(int* arr, int size);// O(nlog(n))

	static void QuickAscending(int* arr, int size); // O(nlog(n))
	static void QuickDescending(int* arr, int size); // O(nlog(n))

	static void TestBehavior();
};

