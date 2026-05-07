#pragma once
#include "VertexNode.h"
#include <stdexcept>

class VertexQueue
{
private:
	VertexNode* front;
	VertexNode* rear;
	int size;

public:
	VertexQueue();
	~VertexQueue();

	void Enqueue(int data);
	int Dequeue();
	int Peek() const;

	bool IsEmpty() const;
	int GetSize() const;
	void Clear();
};