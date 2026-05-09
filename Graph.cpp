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

Graph Graph::KruskalMST()
{
	if (isDirected)
		throw std::logic_error("This algorithm only for undirected graphs");

	// create edge array
	SortedEdgeList list;
	int src, dest;
	AdjNode* curr;
	for (src = 1; src <= numVertices; src++)
	{
		curr = adjLists[src].GetHead();
		while (curr != nullptr)
		{
			dest = curr->GetDest();

			if (dest >= src)
			{
				list.Insert(Edge(src, dest, curr->GetWeight()));
			}

			curr = curr->GetNext();
		}
	}
	Graph result = Graph(numVertices);
	Edge edge;
	int srcRoot, destRoot;
	int edgesAdded = 0;
	DisjointSet ds = DisjointSet(numVertices);
	while (!list.IsEmpty())
	{
		edge = list.ExtractFirst();

		src = edge.GetSrc();
		dest = edge.GetDest();

		srcRoot = ds.Find(src);
		destRoot = ds.Find(dest);

		if (srcRoot != destRoot)
		{
			ds.UnionSets(srcRoot, destRoot);
			result.AddEdge(src, dest, edge.GetWeight());
			edgesAdded++;
		}
		else
		{
			// here can detect cycle
		}
	}

	// count negatives in parent array in disjoint can get the number of components

	return result;
}

Graph Graph::DijkstraSPT(int startVertex) {

	if (startVertex < 1 || startVertex > numVertices)
		throw std::out_of_range("Vertex index out of bounds.");

	int* dist = new int[numVertices + 1];
	int* parent = new int[numVertices + 1];
	bool* selected = new bool[numVertices + 1];

	for (int i = 1; i <= numVertices; i++)
	{
		dist[i] = INT_MAX;
		parent[i] = -1;
		selected[i] = false;
	}

	dist[startVertex] = 0;
	int src, minDistance, dest;

	for (int count = 0; count < numVertices - 1; count++)
	{
		src = -1;
		minDistance = INT_MAX;

		for (dest = 1; dest <= numVertices; dest++)
		{
			if (!selected[dest] && dist[dest] < minDistance)
			{
				minDistance = dist[dest];
				src = dest;
			}
		}

		if (src == -1) break;

		selected[src] = true;

		AdjNode* curr = adjLists[src].GetHead();
		while (curr != nullptr)
		{
			int v = curr->GetDest();
			int weight = curr->GetWeight();

			if (!selected[dest] && dist[src] != INT_MAX && dist[src] + weight < dist[dest])
			{
				dist[dest] = dist[src] + weight;
				parent[dest] = src;
			}
			curr = curr->GetNext();
		}
	}

	Graph result = Graph(numVertices, isDirected);

	for (int i = 1; i <= numVertices; i++)
	{
		if (parent[i] != -1)
		{
			int w = GetWeight(parent[i], i);
			result.AddEdge(parent[i], i, w);
		}
	}

	delete[] dist;
	delete[] parent;
	delete[] selected;

	return result;
}