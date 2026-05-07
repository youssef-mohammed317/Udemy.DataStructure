#pragma once
#include<list>
#include "Graph.h"
class PrimsAlgorithm
{
	// always select the min weight edge connected to the already selected vertices to grow a single tree
	// prims use "near" array to track the closest nodes and "selected" array init with false to mark what is visited
	// Note: this algorithm works ONLY for undirected graphs
public:
	static std::list<Edge> Execute(Graph& graph);
};

