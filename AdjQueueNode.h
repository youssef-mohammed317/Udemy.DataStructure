#pragma once

class AdjQueueNode
{
private:
	int data;
	AdjQueueNode* next;

public:
	AdjQueueNode(int data);

	int GetData() const;
	AdjQueueNode* GetNext() const;
	void SetNext(AdjQueueNode* nextNode);
};