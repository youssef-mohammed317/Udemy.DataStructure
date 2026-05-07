#include "VertexQueue.h"

VertexQueue::VertexQueue()
{
	this->front = nullptr;
	this->rear = nullptr;
	this->size = 0;
}

VertexQueue::~VertexQueue()
{
	Clear();
}

void VertexQueue::Enqueue(int data)
{
	VertexNode* newNode = new VertexNode(data);

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

int VertexQueue::Dequeue()
{
	if (IsEmpty())
	{
		throw std::underflow_error("Queue is empty. Cannot dequeue.");
	}

	VertexNode* temp = front;
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

int VertexQueue::Peek() const
{
	if (IsEmpty())
	{
		throw std::underflow_error("Queue is empty. Cannot peek.");
	}
	return front->GetData();
}

bool VertexQueue::IsEmpty() const
{
	return (front == nullptr);
}

int VertexQueue::GetSize() const
{
	return size;
}

void VertexQueue::Clear()
{
	while (!IsEmpty())
	{
		Dequeue();
	}
}