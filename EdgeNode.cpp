#include "EdgeNode.h"

EdgeNode::EdgeNode(Edge edge, EdgeNode* nextNode)
{
	this->edge = edge;
	this->next = nextNode;
}

Edge EdgeNode::GetEdge() const
{
	return edge;
}

EdgeNode* EdgeNode::GetNext() const
{
	return next;
}

void EdgeNode::SetEdge(Edge edge)
{
	this->edge = edge;
}

void EdgeNode::SetNext(EdgeNode* nextNode)
{
	this->next = nextNode;
}