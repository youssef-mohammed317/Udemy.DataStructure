#include "DisjointSet.h"

DisjointSet::DisjointSet(int n)
{
	if (n <= 0)
		throw std::invalid_argument("Number of elements must be positive.");

	this->n = n;

	parent = new int[n + 1]; // one-based

	for (int i = 1; i <= n; i++)
	{
		parent[i] = -1;
	}
}

DisjointSet::~DisjointSet()
{
	delete[] parent;
}

int DisjointSet::Find(int vertex)
{
	if (vertex < 1 || vertex > n)
		throw std::out_of_range("Vertex index out of bounds in Find (1-based).");

	while (parent[vertex] >= 0)
	{
		vertex = parent[vertex];
	}
	return vertex;
}

void DisjointSet::UnionSets(int rootSrc, int rootDest)
{
	if (rootSrc < 1 || rootSrc > n || rootDest < 1 || rootDest > n)
		throw std::out_of_range("Root index out of bounds in UnionSets.");

	if (rootSrc == rootDest) return;

	if (parent[rootSrc] < parent[rootDest])
	{
		parent[rootSrc] += parent[rootDest];
		parent[rootDest] = rootSrc;
	}
	else
	{
		parent[rootDest] += parent[rootSrc];
		parent[rootSrc] = rootDest;
	}
}