#pragma once

class AdjNode
{
private:
	int dest;
	int weight;
	AdjNode* next;

public:
	AdjNode(int dest, int weight);

	int GetDest() const;
	int GetWeight() const;
	AdjNode* GetNext() const;

	void SetDest(int dest);
	void SetWeight(int weight);
	void SetNext(AdjNode* nextNode);
};