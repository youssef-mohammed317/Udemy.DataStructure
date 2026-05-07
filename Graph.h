#pragma once
#include<list>
#include<algorithm>
#include<stdexcept>
#include<climits>
class Edge {
public:
	int src, dest, weight;
	Edge(int src, int dest, int weight)
	{
		this->src = src;
		this->dest = dest;
		this->weight = weight;
	}
	bool operator==(const Edge& other)const
	{
		return src == other.src && dest == other.dest;
	}
	Edge GetUnDirected()
	{
		return Edge(dest, src, weight);
	}
};
class Graph
{
	int vertices;
	bool isDirected;
	std::list<Edge> edges;
	void ValidateEdge(Edge edge);
public:
	Graph(int vertices, bool isDirceted);
	void AddEdge(Edge edge);
	bool HasEdge(Edge edge);
	void RemoveEdge(Edge edge);
	std::list<Edge> GetEdges();
	bool IsDirected();
	int GetVertices();
	int GetWeight(Edge edge);
	int GetWeight(int src, int dest);
	Edge GetMinWeight();
};

