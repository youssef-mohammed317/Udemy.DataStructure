#pragma once
#include "EdgeNode.h"
#include <stdexcept>

class SortedEdgeList
{
private:
	EdgeNode* head;
	int count;

public:
	SortedEdgeList();
	~SortedEdgeList();

	void Insert(Edge e);
	Edge ExtractFirst();

	bool IsEmpty() const;
	int GetSize() const;
	void Clear();
};