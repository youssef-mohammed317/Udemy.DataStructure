#pragma once
#include <stdexcept>

class DisjointSet
{
private:
	int* parent;
	int n;

public:
	DisjointSet(int n);
	~DisjointSet();

	int Find(int vertex);

	void UnionSets(int rootSrc, int rootDest);
};