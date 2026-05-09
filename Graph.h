#pragma once
#include<list>
#include "AdjList.h"
#include "VertexQueue.h"
#include "VertexStack.h"
#include "DisjointSet.h"
#include "SortedEdgeList.h"
class Graph
{
private:
	int numVertices;
	AdjList* adjLists;
	bool isDirected;

public:
	Graph(int vertices = 1, bool directed = false);
	~Graph();

	Graph(const Graph& other);
	Graph& operator=(const Graph& other);

	// Basic Operations
	void AddEdge(int src, int dest, int weight = 0);
	void RemoveEdge(int src, int dest);
	bool HasEdge(int src, int dest) const;
	void PrintGraph() const;
	int GetWeight(int src, int dest) const;
	void Clear();

	// Traversal Algorithms
	// Uses a queue (FIFO) to explore level by level.
	void BFS(int startVertex);

	// Uses a stack (LIFO) or recursion to explore as deep as possible.
	void DFS(int startVertex);

	// always select min weight use sorted list or array with selected array init with false and mark what is selected
	// kruskal use disjoint sets
	// Note: this algorithm works ONLY for undirected graphs
	Graph KruskalMST();

	// Shortest Path
	// always select the unvisited vertex with the minimum cumulative distance from the source to find the shortest path
	// dijkstra uses "distances" array to track the lowest cost to each node and "selected" array to mark finalized vertices
	// Note: this algorithm works for both directed and undirected graphs, but CANNOT handle negative weight edges
	Graph DijkstraSPT(int startVertex);
};