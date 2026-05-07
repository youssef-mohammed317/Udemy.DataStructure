#pragma once
#include<iostream>
#include <stdexcept>
#include "AdjNode.h"

class AdjList
{
private:
	int source;
	int size;
	AdjNode* head;
	AdjNode* tail;

public:
	AdjList();
	AdjList(int source);
	AdjList(const AdjList& other);

	~AdjList();

	AdjList& operator=(const AdjList& other);

	int GetSource() const;
	int GetSize() const;
	AdjNode* GetHead() const;
	AdjNode* GetTail() const;

	void SetSource(int source);

	void AddEdge(int dest, int weight);
	void RemoveEdge(int dest);
	bool HasEdge(int dest) const;
	int GetWeight(int dest) const;
	void Clear();

	void Print() const;
};