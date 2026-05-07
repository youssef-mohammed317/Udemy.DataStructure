#include "KruskalAlgorithm.h"
int KruskalAlgorithm::Find(int* parent, int vertex)
{
	while (parent[vertex] > 0)
	{
		vertex = parent[vertex];
	}
	return vertex;
}

void KruskalAlgorithm::Union(int* parent, int srcRoot, int destRoot)
{
	if (parent[srcRoot] < parent[destRoot])
	{
		parent[srcRoot] += parent[destRoot];
		parent[destRoot] = srcRoot;
	}
	else {
		parent[destRoot] += parent[srcRoot];
		parent[srcRoot] = destRoot;
	}
}

std::list<Edge> KruskalAlgorithm::Execute(Graph& graph)
{
	std::list<Edge> edges = graph.GetEdges();
	edges.sort([](Edge& a, Edge& b) {
		return  a.weight < b.weight;
		});

	int* parent = new int[graph.GetVertices() + 1] {0};
	for (int i = 0; i <= graph.GetVertices(); i++)
		parent[i] = -1;

	std::list<Edge> result;
	int srcRoot, destRoot;
	for (Edge& edge : edges)
	{
		srcRoot = Find(parent, edge.src);
		destRoot = Find(parent, edge.dest);
		if (srcRoot != destRoot)
		{
			Union(parent, srcRoot, destRoot);
			result.push_back(edge);
		}
		else {
			// here can detect a cycle
		}
	}

	delete[]parent;
	return result;
}