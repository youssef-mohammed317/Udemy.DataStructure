#pragma once
#include<list>
#include<climits>
#include "Graph.h"
class KruskalAlgorithm
{
	// always select min weight use sorted list or array with selected array init with false and mark what is selected
	// kruskal use disjoint sets
	// Note: this algorithm works ONLY for undirected graphs


	static int Find(int* parent, int vertex);
	static void Union(int* parent, int src, int dest);
public:
	static std::list<Edge> Execute(Graph& graph);
};

