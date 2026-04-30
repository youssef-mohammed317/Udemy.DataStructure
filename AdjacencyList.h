#pragma once
#include<climits>
#include<stdexcept>
#include<queue>
#include<stack>
#include<list>
#include<iostream>
#include<algorithm>
using namespace std;

struct Node {
	int vertex;
	int weight;
	Node(int vertex, int weight = 1)
	{
		this->weight = vertex;
		this->weight = weight;
	}
};


class AdjacencyList
{
	list<Node>* cost;
	int verticesNumber;
	bool isDirected;
	void ValidateVertex(int vertex);
	void ValidateEdge(int u, int v);
	void ParentHelper(int* parent, int& u, int& v, int& uRoot, int& vRoot);

public:
	AdjacencyList(int verticesNumber, bool isDirected = false);
	~AdjacencyList();
	void Clear();

	void AddEdge(int u, int v, int weight = 1);
	void RemoveEdge(int u, int v);
	bool HasEdge(int u, int v);
	int GetWeight(int u, int v);

	int Find(int vertex);
	int CountVertices();
	int CountEdges();
	int CountWeights();
	int CountConnectedComponents();
	bool IsDirected();
	bool IsCycle();
	bool IsConnected();

	void BreadthFirstSearch(int startVertex);
	void DepthFirstSearch(int startVertex);

	AdjacencyList Union(AdjacencyList& other);

	void PrintMatrix();

	static void TestBehavior();
};

