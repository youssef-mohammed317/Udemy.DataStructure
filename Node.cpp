#include "Node.h"
Node::Node(int data, Node* next)
{
	this->data = data;
	this->next = next;
}
Node::~Node() = default;

int Node::GetData() const
{
	return data;
}
Node* Node::GetNext() const
{
	return next;
}

void Node::SetData(int data)
{
	this->data = data;
}
void Node::SetNext(Node* next)
{
	this->next = next;
}