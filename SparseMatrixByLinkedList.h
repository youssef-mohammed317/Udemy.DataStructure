#pragma once
#include<iostream>
#include<stdexcept>
#include "SparseNode.h"
using namespace std;

class SparseMatrixByLinkedList
{
	int rows;
	int cols;
	int length;
	SparseNode* head;
	SparseNode* tail;
	void ThrowIfFull();
	void ThrowIfIndexOutOfRange(int r, int c);
public:
	SparseMatrixByLinkedList(int rows, int cols);
	// The Copy Constructor
	SparseMatrixByLinkedList(const SparseMatrixByLinkedList& other);
	~SparseMatrixByLinkedList();
	void Clear();

	int GetRows();
	int GetCols();
	int GetLength();

	void Set(int row, int col, int data);
	int Get(int row, int col);
	void Display();

	static void TestBehavior();

	SparseMatrixByLinkedList operator+(SparseMatrixByLinkedList& s);
};

