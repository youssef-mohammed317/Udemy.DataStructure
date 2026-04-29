#include "AdjacencyMatrix.h"

void AdjacencyMatrix::ValidateEdge(int u, int v)
{
	if (u > verticesNumber || u < 1 || v > verticesNumber || v < 1)
		throw new exception("invalid vertex inputs");
}
void AdjacencyMatrix::ValidateVertex(int vertex)
{
	if (vertex > verticesNumber || vertex < 1)
		throw new exception("invalid vertex inputs");
}

AdjacencyMatrix::AdjacencyMatrix(int verticesNumber, bool isDirected)
{
	this->verticesNumber = verticesNumber;
	this->isDirected = isDirected;

	cost = new int* [verticesNumber + 1]; // one-based index (rows)
	for (int i = 0; i <= verticesNumber; i++)
	{
		cost[i] = new int[verticesNumber + 1] {0};// one-based index (cols)
	}
	Clear(); // no edges initial infinty
}

AdjacencyMatrix::~AdjacencyMatrix()
{
	for (int i = 0; i <= verticesNumber; i++)
	{
		delete[]cost[i];
	}
	delete[]cost;
}
void AdjacencyMatrix::Clear()
{
	// remove all edges
	for (int u = 1; u <= verticesNumber; u++)
		for (int v = 1; v <= verticesNumber; v++)
			cost[u][v] = INT_MAX;
}
void AdjacencyMatrix::AddEdge(int u, int v, int weight)
{
	ValidateIndex(u, v);
	if (isDirected)
	{
		cost[u][v] = weight;
	}
	else {
		cost[u][v] = cost[v][u] = weight;
	}
}

void AdjacencyMatrix::RemoveEdge(int u, int v)
{
	ValidateIndex(u, v);
	if (isDirected)
	{
		cost[u][v] = INT_MAX;
	}
	else {
		cost[u][v] = cost[v][u] = INT_MAX;
	}
}
bool AdjacencyMatrix::HasEdge(int u, int v)
{
	ValidateIndex(u, v);
	return 	cost[u][v] != INT_MAX;
}

int AdjacencyMatrix::CountVertices()
{
	return verticesNumber;
}
int AdjacencyMatrix::CountEdges()
{
	int counter = 0;

	if (isDirected)
	{
		for (int u = 1; u <= verticesNumber; u++)
		{
			for (int v = 1; v <= verticesNumber; v++)
				if (cost[u][v] != INT_MAX)
					counter++;
		}
	}
	else {
		for (int u = 1; u <= verticesNumber; u++)
		{
			for (int v = u; v <= verticesNumber; v++)
				if (cost[u][v] != INT_MAX)
					counter++;
		}
	}
	return counter;
}

int AdjacencyMatrix::CountWeights()
{
	int sum = 0;

	if (isDirected)
	{
		for (int u = 1; u <= verticesNumber; u++)
		{
			for (int v = 1; v <= verticesNumber; v++)
				if (cost[u][v] != INT_MAX)
					sum += cost[u][v];
		}
	}
	else {
		for (int u = 1; u <= verticesNumber; u++)
		{
			for (int v = u; v <= verticesNumber; v++)
				if (cost[u][v] != INT_MAX)
					sum += cost[u][v];
		}
	}
	return sum;
}
bool AdjacencyMatrix::IsDirected()
{
	return isDirected;
}

void AdjacencyMatrix::BreadthFirstSearch(int startVertex)
{
	ValidateVertex(startVertex);

	bool* printed = new bool[verticesNumber + 1] {0};
	queue<int>q;
	q.push(startVertex);
	printed[startVertex] = true;
	int u;
	cout << "{";
	while (!q.empty())
	{
		u = q.front(); q.pop();
		cout << u << " ";
		for (int v = 1; v <= verticesNumber; v++)
		{
			if (!printed[v] && cost[u][v] != INT_MAX)
			{
				q.push(v);
				printed[v] = true;
			}
		}
	}
	cout << "}\n";
	delete[]printed;
}

void AdjacencyMatrix::DepthFirstSearch(int startVertex)
{
	ValidateVertex(startVertex);

	bool* printed = new bool[verticesNumber + 1] {0};
	stack<int>s;
	s.push(startVertex);
	printed[startVertex] = true;
	int u;
	cout << "{";
	while (!s.empty())
	{
		u = s.top(); s.pop();
		cout << u << " ";
		for (int v = verticesNumber; v >= 1; v++)
		{
			if (!printed[v] && cost[u][v] != INT_MAX)
			{
				s.push(v);
				printed[v] = true;
			}
		}
	}
	cout << "}\n";
	delete[]printed;
}

void AdjacencyMatrix::PrintMatrix()
{
	int u, v;
	for (u = 1; u <= verticesNumber; u++)
	{
		cout << "{";
		for (v = 1; v < verticesNumber; v++)
		{
			if (cost[u][v] != INT_MAX)
				cout << cost[u][v] << ", ";
			else
				cout << "-" << ", ";
		}
		if (cost[u][v] != INT_MAX)
			cout << cost[u][v] << "}\n";
		else
			cout << "-" << "}\n";

	}

}