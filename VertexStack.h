#pragma once
#include "VertexNode.h"
#include <stdexcept>

class VertexStack
{
private:
	VertexNode* top;
	int size;

public:
	VertexStack();
	~VertexStack();

	void Push(int data);
	int Pop();
	int Peek() const;

	bool IsEmpty() const;
	int GetSize() const;
	void Clear();
};