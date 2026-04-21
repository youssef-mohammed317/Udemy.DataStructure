#include "Node.h"
Node::Node(int data, Node* next)
{
	this->next = next;
	this->data = data;
}
Node::~Node()
{}
void Node::SetData(int data)
{
	this->data = data;
}
int Node::GetData()
{
	return this->data;
}
Node* Node::GetNext()
{
	return this->next;
}
void Node::SetNext(Node* next)
{
	this->next = next;
}