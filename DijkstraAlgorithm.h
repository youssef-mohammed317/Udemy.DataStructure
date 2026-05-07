#pragma once
#include<list>
#include "Graph.h"
class DijkstraAlgorithm
{
	// always select the unvisited vertex with the minimum cumulative distance from the source to find the shortest path
	// dijkstra uses "distances" array to track the lowest cost to each node and "selected" array to mark finalized vertices
	// Note: this algorithm works for both directed and undirected graphs, but CANNOT handle negative weight edges
public:
	static std::list<Edge>* Execute(Graph graph, int source);
};

