#include "DoublyNode.h"

DoublyNode::DoublyNode(int data, DoublyNode* next, DoublyNode* prev)
{
	this->data = data;
	this->next = next;
	this->prev = prev;
}
DoublyNode::~DoublyNode() = default;

void DoublyNode::SetData(int data)
{
	this->data = data;
}
int DoublyNode::GetData()const
{
	return data;
}
void DoublyNode::SetNext(DoublyNode* next)
{
	this->next = next;
}
DoublyNode* DoublyNode::GetNext()const
{
	return next;
}
void DoublyNode::SetPrev(DoublyNode* prev)
{
	this->prev = prev;
}
DoublyNode* DoublyNode::GetPrev()const
{
	return prev;
}