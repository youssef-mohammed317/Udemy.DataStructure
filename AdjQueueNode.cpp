#include "AdjQueueNode.h"

AdjQueueNode::AdjQueueNode(int data)
{
	this->data = data;
	this->next = nullptr;
}

int AdjQueueNode::GetData() const
{
	return data;
}

AdjQueueNode* AdjQueueNode::GetNext() const
{
	return next;
}

void AdjQueueNode::SetNext(AdjQueueNode* nextNode)
{
	this->next = nextNode;
}