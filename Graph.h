#pragma once
#include "AdjList.h"
#include "VertexQueue.h"
#include "VertexStack.h"
#include "DisjointSet.h"
class Graph
{
private:
	int numVertices;
	AdjList* adjLists;
	bool isDirected;

public:
	Graph(int vertices, bool directed = false);
	~Graph();

	Graph(const Graph& other);
	Graph& operator=(const Graph& other);

	// Basic Operations
	void AddEdge(int src, int dest, int weight = 0);
	void RemoveEdge(int src, int dest);
	bool HasEdge(int src, int dest) const;
	void PrintGraph() const;
	void Clear();

	// Traversal Algorithms
	// Uses a queue (FIFO) to explore level by level.
	void BFS(int startVertex);

	// Uses a stack (LIFO) or recursion to explore as deep as possible.
	void DFS(int startVertex);

	// Minimum Spanning Tree (MST)
	// always select the min weight edge connected to the already selected vertices to grow a single tree
	// prims use "near" array to track the closest nodes and "selected" array init with false to mark what is visited
	// Note: this algorithm works ONLY for undirected graphs
	Graph PrimMST();

	// always select min weight use sorted list or array with selected array init with false and mark what is selected
	// kruskal use disjoint sets
	// Note: this algorithm works ONLY for undirected graphs
	Graph KruskalMST();

	// Shortest Path
	// always select the unvisited vertex with the minimum cumulative distance from the source to find the shortest path
	// dijkstra uses "distances" array to track the lowest cost to each node and "selected" array to mark finalized vertices
	// Note: this algorithm works for both directed and undirected graphs, but CANNOT handle negative weight edges
	Graph Dijkstra(int startVertex);
};