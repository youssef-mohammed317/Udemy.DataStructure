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

void AdjacencyList::ParentHelper(int* parent, int& u, int& v, int& uRoot, int& vRoot)
{
	uRoot = u;
	while (parent[uRoot] > 0)
	{
		uRoot = parent[uRoot];
	}

	vRoot = v;
	while (parent[vRoot] > 0) {
		vRoot = parent[vRoot];
	}

	if (vRoot != uRoot)
	{
		if (parent[uRoot] < parent[vRoot])
		{
			parent[uRoot] += parent[vRoot];
			parent[vRoot] = uRoot;
		}
		else {
			parent[vRoot] += parent[uRoot];
			parent[uRoot] = vRoot;
		}
	}

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

int AdjacencyList::Find(int vertex)
{
	ValidateVertex(vertex);

	int* parent = new int[verticesNumber + 1] {0};
	for (int i = 1; i <= verticesNumber; i++)
		parent[i] = -1;

	int u, v, uRoot, vRoot;

	for (u = 1; u <= verticesNumber; u++)
	{
		for (const Node& n : cost[u])
		{
			v = n.vertex;
			ParentHelper(parent, u, v, uRoot, vRoot);
		}
	}

	int vertexRoot = vertex;
	while (parent[vertexRoot] > 0)
		vertexRoot = parent[vertexRoot];

	delete[]parent;
	return vertexRoot;
}

int AdjacencyList::CountConnectedComponents()
{
	int* parent = new int[verticesNumber + 1] {0};
	for (int i = 1; i <= verticesNumber; i++)
		parent[i] = -1;

	int u, v, uRoot, vRoot;

	for (u = 1; u <= verticesNumber; u++)
	{
		for (const Node& n : cost[u])
		{
			v = n.vertex;
			ParentHelper(parent, u, v, uRoot, vRoot);
		}
	}

	int counter = 0;
	for (int i = 1; i <= verticesNumber; i++)
	{
		if (parent[i] < 0)
			counter++;
	}
	delete[]parent;
	return counter;
}


int AdjacencyList::CountVertices()
{
	return verticesNumber;
}

int AdjacencyList::CountWeights()
{
	int weights = 0;


	for (int u = 1; u <= verticesNumber; u++)
	{
		for (const Node& n : cost[u])
		{
			weights += n.weight;
		}
	}

	return isDirected ? weights : weights / 2;

}

int AdjacencyList::CountEdges()
{
	int edges = 0;


	for (int u = 1; u <= verticesNumber; u++)
	{
		edges += cost[u].size();
	}

	return isDirected ? edges : edges / 2;
}

bool AdjacencyList::IsDirected()
{
	return isDirected;
}
bool AdjacencyList::IsConnected()
{
	return CountConnectedComponents() == 1;
}
bool AdjacencyList::IsCycle() {
	int* parent = new int[verticesNumber + 1] {0};
	for (int i = 1; i <= verticesNumber; i++)
		parent[i] = -1;

	int u, v, uRoot, vRoot;
	if (!isDirected)
	{
		for (u = 1; u <= verticesNumber; u++)
		{
			for (const Node& n : cost[u])
			{
				v = n.vertex;
				if (u <= v)
				{
					ParentHelper(parent, u, v, uRoot, vRoot);
					if (uRoot == vRoot)
					{
						delete[]parent;
						return true;
					}
				}


			}
		}
	}

	delete[]parent;
	return false;
}