#include "AdjQueue.h"

AdjQueue::AdjQueue()
{
	this->front = nullptr;
	this->rear = nullptr;
	this->size = 0;
}

AdjQueue::~AdjQueue()
{
	Clear();
}

void AdjQueue::Enqueue(int data)
{
	AdjQueueNode* newNode = new AdjQueueNode(data);

	if (IsEmpty())
	{
		front = newNode;
		rear = newNode;
	}
	else
	{
		rear->SetNext(newNode);
		rear = newNode;
	}
	size++;
}

int AdjQueue::Dequeue()
{
	if (IsEmpty())
	{
		throw std::underflow_error("Queue is empty. Cannot dequeue.");
	}

	AdjQueueNode* temp = front;
	int dequeuedData = temp->GetData();

	front = front->GetNext();

	if (front == nullptr)
	{
		rear = nullptr;
	}

	delete temp;
	size--;

	return dequeuedData;
}

int AdjQueue::Peek() const
{
	if (IsEmpty())
	{
		throw std::underflow_error("Queue is empty. Cannot peek.");
	}
	return front->GetData();
}

bool AdjQueue::IsEmpty() const
{
	return (front == nullptr);
}

int AdjQueue::GetSize() const
{
	return size;
}

void AdjQueue::Clear()
{
	while (!IsEmpty())
	{
		Dequeue();
	}
}