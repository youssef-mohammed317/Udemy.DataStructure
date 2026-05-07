#pragma once
#include "AdjQueueNode.h"
#include <stdexcept>
class AdjQueue
{
private:
	AdjQueueNode* front;
	AdjQueueNode* rear;
	int size;

public:
	AdjQueue();
	~AdjQueue();

	void Enqueue(int data);
	int Dequeue();
	int Peek() const;

	bool IsEmpty() const;
	int GetSize() const;
	void Clear();
};