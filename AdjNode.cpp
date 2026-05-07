#include "AdjNode.h"

AdjNode::AdjNode(int dest, int weight)
{
	this->dest = dest;
	this->weight = weight;
	this->next = nullptr;
}

int AdjNode::GetDest() const
{
	return dest;
}
int AdjNode::GetWeight() const
{
	return weight;
}
AdjNode* AdjNode::GetNext() const
{
	return next;
}

void AdjNode::SetDest(int dest)
{
	this->dest = dest;
}
void AdjNode::SetWeight(int weight)
{
	this->weight = weight;
}
void AdjNode::SetNext(AdjNode* nextNode)
{
	this->next = nextNode;
}