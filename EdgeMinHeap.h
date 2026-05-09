#pragma once
#include "Edge.h"
#include <stdexcept>

class EdgeMinHeap
{
private:
	Edge* heapArray;
	int capacity;
	int size;

	int Parent(int i) const;
	int LeftChild(int i) const;
	int RightChild(int i) const;

	// Core heap operations
	void HeapifyUp(int index);
	void HeapifyDown(int index);
	void Resize();
	void Swap(Edge& a, Edge& b);

public:
	EdgeMinHeap(int initialCapacity = 10);
	~EdgeMinHeap();

	// Main priority queue functions
	void Insert(Edge e);
	Edge ExtractMin();

	// Utility functions
	bool IsEmpty() const;
	int GetSize() const;
	void Clear();
};