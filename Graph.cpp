#include "Graph.h"
#include <iostream>
#include <stdexcept>

Graph::Graph(int vertices, bool directed)
{
	if (vertices <= 0)
	{
		throw std::invalid_argument("Number of vertices must be greater than zero.");
	}

	this->numVertices = vertices;
	this->isDirected = directed;

	// one-based
	this->adjLists = new AdjList[vertices + 1];

	for (int i = 1; i <= vertices; i++)
	{
		adjLists[i].SetSource(i);
	}
}

Graph::~Graph()
{
	delete[] adjLists;
}

Graph::Graph(const Graph& other)
{
	this->numVertices = other.numVertices;
	this->isDirected = other.isDirected;
	this->adjLists = new AdjList[numVertices + 1];

	for (int i = 1; i <= numVertices; i++)
	{
		this->adjLists[i] = other.adjLists[i];
	}
}

Graph& Graph::operator=(const Graph& other)
{
	if (this != &other)
	{
		delete[] adjLists;

		this->numVertices = other.numVertices;
		this->isDirected = other.isDirected;
		this->adjLists = new AdjList[numVertices + 1];

		for (int i = 1; i <= numVertices; i++)
		{
			this->adjLists[i] = other.adjLists[i];
		}
	}
	return *this;
}

void Graph::AddEdge(int src, int dest, int weight)
{
	if (src < 1 || src > numVertices || dest < 1 || dest > numVertices)
		throw std::out_of_range("Vertex index out of bounds (1-based).");

	adjLists[src].AddEdge(dest, weight);
	if (!isDirected)
	{
		adjLists[dest].AddEdge(src, weight);
	}
}

void Graph::RemoveEdge(int src, int dest)
{
	if (src < 1 || src > numVertices || dest < 1 || dest > numVertices)
		throw std::out_of_range("Vertex index out of bounds (1-based).");

	adjLists[src].RemoveEdge(dest);
	if (!isDirected)
	{
		adjLists[dest].RemoveEdge(src);
	}
}

bool Graph::HasEdge(int src, int dest) const
{
	if (src < 1 || src > numVertices || dest < 1 || dest > numVertices)
		return false;

	return adjLists[src].HasEdge(dest);
}

void Graph::PrintGraph() const
{
	std::cout << "Graph Adjacency List (Vertices: " << numVertices << " | 1-based indexing):\n";
	for (int i = 1; i <= numVertices; i++)
	{
		adjLists[i].Print();
	}
}
void Graph::Clear()
{
	for (int i = 1; i <= numVertices; i++)
	{
		adjLists[i].Clear();
	}
}

void Graph::BFS(int startVertex)
{
	if (startVertex < 1 || startVertex > numVertices)
		throw std::out_of_range("Vertex index out of bounds (1-based).");

	bool* visited = new bool[numVertices + 1] {false};

	VertexQueue q;
	q.Enqueue(startVertex);
	visited[startVertex] = true;
	int src, dest;
	AdjNode* curr;
	bool isFirst = true;
	std::cout << "{";
	while (!q.IsEmpty())
	{
		src = q.Dequeue();
		if (!isFirst) std::cout << ", ";
		std::cout << src;
		isFirst = false;
		curr = adjLists[src].GetHead();
		while (curr != nullptr)
		{
			dest = curr->GetDest();
			if (!visited[dest])
			{
				q.Enqueue(dest);
				visited[dest] = true;
			}
			curr = curr->GetNext();
		}
	}
	std::cout << "}\n";
	delete[] visited;
}

void Graph::DFS(int startVertex)
{
	if (startVertex < 1 || startVertex > numVertices)
		throw std::out_of_range("Vertex index out of bounds (1-based).");

	bool* visited = new bool[numVertices + 1] {false};
	VertexStack s;
	s.Push(startVertex);
	int src, dest;
	AdjNode* curr;
	std::cout << "{";
	bool isFirst = true;
	while (!s.IsEmpty())
	{
		src = s.Pop();
		if (!visited[src])
		{
			if (!isFirst) std::cout << ", ";
			std::cout << src;
			visited[src] = true;
			isFirst = false;
			curr = adjLists[src].GetHead();
			while (curr != nullptr)
			{
				dest = curr->GetDest();
				if (!visited[dest])
				{
					s.Push(dest);

				}
				curr = curr->GetNext();
			}

		}
	}
	std::cout << "}\n";
	delete[] visited;
}