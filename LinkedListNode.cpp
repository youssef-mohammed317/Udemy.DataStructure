#include "LinkedListNode.h"

LinkedListNode::LinkedListNode(int data, LinkedListNode* next)
{
	this->data = data;
	this->next = next;
}

LinkedListNode::~LinkedListNode()
{}

int LinkedListNode::GetData()
{
	return data;
}

LinkedListNode* LinkedListNode::GetNext()
{
	return next;
}

void LinkedListNode::SetData(int data)
{
	this->data = data;
}
void LinkedListNode::SetNext(LinkedListNode* next)
{
	this->next = next;
}