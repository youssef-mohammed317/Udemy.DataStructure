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
	auto it = std::find_if(edges.begin(), edges.end(), [edge](const Edge& e) {
		return e == edge;
		});
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