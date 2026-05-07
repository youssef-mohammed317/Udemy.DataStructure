#include "VertexStack.h"

VertexStack::VertexStack()
{
	this->top = nullptr;
	this->size = 0;
}

VertexStack::~VertexStack()
{
	Clear();
}

void VertexStack::Push(int data)
{
	VertexNode* newNode = new VertexNode(data);

	newNode->SetNext(top);
	top = newNode;

	size++;
}

int VertexStack::Pop()
{
	if (IsEmpty())
	{
		throw std::underflow_error("Stack is empty. Cannot pop.");
	}

	VertexNode* temp = top;
	int poppedData = temp->GetData();

	top = top->GetNext();

	delete temp;
	size--;

	return poppedData;
}

int VertexStack::Peek() const
{
	if (IsEmpty())
	{
		throw std::underflow_error("Stack is empty. Cannot peek.");
	}
	return top->GetData();
}

bool VertexStack::IsEmpty() const
{
	return (top == nullptr);
}

int VertexStack::GetSize() const
{
	return size;
}

// Remove all elements from the stack
void VertexStack::Clear()
{
	while (!IsEmpty())
	{
		Pop();
	}
}