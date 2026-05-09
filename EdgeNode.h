#pragma once
#include "Edge.h"

class EdgeNode
{
private:
	Edge edge;
	EdgeNode* next;

public:
	EdgeNode(Edge edge, EdgeNode* nextNode = nullptr);

	Edge GetEdge() const;
	EdgeNode* GetNext() const;

	void SetEdge(Edge edge);
	void SetNext(EdgeNode* nextNode);
};
