#include "Graph.h"
void Graph::ValidateEdge(Edge edge)
{
	if (edge.src > vertices || edge.src < 1 || edge.dest > vertices || edge.dest < 1)
		throw std::exception("invalid input");
}
Graph::Graph(int vertices, bool isDirected)
{
	this->vertices = vertices;
	this->isDirected = isDirected;
}
void Graph::AddEdge(Edge edge)
{
	ValidateEdge(edge);
	auto it = std::find(edges.begin(), edges.end(), edge);
	if (it == edges.end())
	{
		edges.push_back(edge);
		if (!isDirected)
		{
			edges.push_back(edge.GetUnDirected());
		}
	}
	else {
		it->weight += edge.weight;
		if (!isDirected)
		{
			auto it2 = std::find(edges.begin(), edges.end(), edge.GetUnDirected());
			it2->weight += edge.weight;
		}
	}
}

void Graph::RemoveEdge(Edge edge)
{
	ValidateEdge(edge);
	edges.remove(edge);
	if (!isDirected)
	{
		edges.remove(edge.GetUnDirected());
	}
}

bool Graph::HasEdge(Edge edge)
{
	ValidateEdge(edge);
	auto it = std::find(edges.begin(), edges.end(), edge);
	return it != edges.end();
}
bool Graph::IsDirected()
{
	return isDirected;
}
int Graph::GetVertices()
{
	return vertices;
}
std::list<Edge> Graph::GetEdges()
{
	return edges;
}
int Graph::GetWeight(int src, int dest)
{
	return GetWeight(Edge(src, dest, 1));
}
int Graph::GetWeight(Edge edge)
{
	ValidateEdge(edge);
	auto it = std::find(edges.begin(), edges.end(), edge);
	if (it != edges.end())
	{
		return it->weight;
	}
	return INT_MAX;
}
Edge Graph::GetMinWeight()
{
	if (edges.empty()) throw std::logic_error("the graph is empty");
	Edge selected = edges.front();
	for (Edge& e : edges)
	{
		if (e.weight < selected.weight)
		{
			selected = e;
		}
	}
	return selected;
}