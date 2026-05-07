#pragma once

class VertexNode
{
private:
	int data;
	VertexNode* next;

public:
	VertexNode(int data);

	int GetData() const;
	VertexNode* GetNext() const;
	void SetNext(VertexNode* nextNode);
};