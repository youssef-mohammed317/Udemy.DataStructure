#include "VertexNode.h"

VertexNode::VertexNode(int data)
{
	this->data = data;
	this->next = nullptr;
}

int VertexNode::GetData() const
{
	return data;
}

VertexNode* VertexNode::GetNext() const
{
	return next;
}

void VertexNode::SetNext(VertexNode* nextNode)
{
	this->next = nextNode;
}