#include "AdjacencyList.h"

void AdjacencyList::ValidateVertex(int vertex)
{
	if (vertex < 1 || vertex > verticesNumber)
		throw out_of_range("invalid vertex number");
}
void AdjacencyList::ValidateEdge(int u, int v)
{
	ValidateVertex(u);
	ValidateVertex(v);
}

AdjacencyList::AdjacencyList(int verticesNumber, bool isDirected)
{
	this->verticesNumber = verticesNumber;
	this->isDirected = isDirected;

	cost = new list<Node>[verticesNumber + 1];
}

AdjacencyList::~AdjacencyList()
{
	delete[]cost;
}
void AdjacencyList::Clear()
{
	for (int i = 1; i <= verticesNumber; i++)
	{
		cost[i].clear();
	}
}

void AdjacencyList::AddEdge(int u, int v, int weight)
{
	ValidateEdge(u, v);

	cost[u].push_back(Node(v, weight));
	if (isDirected == false)
	{
		cost[v].push_back(Node(u, weight));
	}
}

void AdjacencyList::RemoveEdge(int u, int v)
{
	ValidateEdge(u, v);

	cost[u].remove_if([v](const Node& n) {
		return n.vertex == v;
		});

	if (isDirected == false)
	{
		cost[v].remove_if([u](const Node& n) {
			return n.vertex == u;
			});
	}
}

bool AdjacencyList::HasEdge(int u, int v)
{
	ValidateEdge(u, v);

	auto it = find_if(cost[u].begin(), cost[u].end(), [v](const Node& n) {
		return n.vertex == v;
		});

	return it != cost[u].end();
}

int AdjacencyList::GetWeight(int u, int v)
{
	ValidateEdge(u, v);

	auto it = find_if(cost[u].begin(), cost[u].end(), [v](const Node& n) {
		return n.vertex == v;
		});

	if (it != cost[u].end())
	{
		return it->weight;
	}

	return INT_MAX;
}
