#pragma once
#include<climits>
#include<stdexcept>
#include<queue>
#include<stack>
#include<iostream>
using namespace std;
class AdjacencyMatrix
{
	int** cost;
	int verticesNumber;
	bool isDirected;
	void ValidateEdge(int u, int v);
	void ValidateVertex(int vertex);
	void ParentHelper(int* parent, int& u, int& v, int& uRoot, int& vRoot);

public:
	AdjacencyMatrix(int verticesNumber, bool isDirected = false);
	~AdjacencyMatrix();
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

	AdjacencyMatrix Union(AdjacencyMatrix& other);

	void PrintMatrix();

	static void TestBehavior();
};

