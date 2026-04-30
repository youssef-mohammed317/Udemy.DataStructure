#include "AdjacencyMatrix.h"

void AdjacencyMatrix::ValidateEdge(int u, int v)
{
	if (u > verticesNumber || u < 1 || v > verticesNumber || v < 1)
		throw out_of_range("invalid vertex inputs");
}
void AdjacencyMatrix::ValidateVertex(int vertex)
{
	if (vertex > verticesNumber || vertex < 1)
		throw out_of_range("invalid vertex inputs");
}
void AdjacencyMatrix::ParentHelper(int* parent, int& u, int& v, int& uRoot, int& vRoot)
{
	if (cost[u][v] != INT_MAX)
	{
		uRoot = u;
		while (parent[uRoot] > 0)
			uRoot = parent[uRoot];

		vRoot = v;
		while (parent[vRoot] > 0)
			vRoot = parent[vRoot];

		if (uRoot != vRoot)
		{
			if (parent[uRoot] <= parent[vRoot])
			{
				parent[uRoot] += parent[vRoot];
				parent[vRoot] = uRoot;
			}
			else
			{
				parent[vRoot] += parent[uRoot];
				parent[uRoot] = vRoot;
			}
		}
	}
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
	ValidateEdge(u, v);
	if (isDirected)
	{
		if (cost[u][v] == INT_MAX)
			cost[u][v] = weight;
		else
			cost[u][v] += weight;
	}
	else {
		if (cost[u][v] == INT_MAX)
			cost[u][v] = cost[v][u] = weight;
		else
		{
			cost[u][v] += weight;
			cost[v][u] += weight;
		}

	}
}

void AdjacencyMatrix::RemoveEdge(int u, int v)
{
	ValidateEdge(u, v);
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
	ValidateEdge(u, v);
	return cost[u][v] != INT_MAX;
}
int AdjacencyMatrix::GetWeight(int u, int v)
{
	ValidateEdge(u, v);
	return cost[u][v];
}

int AdjacencyMatrix::Find(int vertex)
{
	ValidateVertex(vertex);
	int* parent = new int[verticesNumber + 1] {0};
	for (int i = 1; i <= verticesNumber; i++)
		parent[i] = -1;

	int u, v, uRoot, vRoot;
	if (isDirected)
	{
		for (u = 1; u <= verticesNumber; u++)
			for (v = 1; v <= verticesNumber; v++)
				ParentHelper(parent, u, v, uRoot, vRoot);
	}
	else {
		for (u = 1; u <= verticesNumber; u++)
			for (v = u + 1; v <= verticesNumber; v++)
				ParentHelper(parent, u, v, uRoot, vRoot);
	}

	int boss = parent[vertex] < 0 ? vertex : parent[vertex];
	delete[] parent;
	return boss;
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

int AdjacencyMatrix::CountConnectedComponents()
{
	int* parent = new int[verticesNumber + 1] {0};
	for (int i = 1; i <= verticesNumber; i++)
		parent[i] = -1;

	int u, v, uRoot, vRoot;
	if (isDirected)
	{
		for (u = 1; u <= verticesNumber; u++)
		{
			for (v = 1; v <= verticesNumber; v++)
			{
				ParentHelper(parent, u, v, uRoot, vRoot);
			}
		}

	}
	else {
		for (u = 1; u <= verticesNumber; u++)
		{
			for (v = u + 1; v <= verticesNumber; v++)
			{
				ParentHelper(parent, u, v, uRoot, vRoot);
			}
		}
	}
	int counter = 0;
	for (int i = 1; i <= verticesNumber; i++)
		if (parent[i] < 0)
			counter++;

	delete[]parent;
	return counter;
}

bool AdjacencyMatrix::IsDirected()
{
	return isDirected;
}

bool AdjacencyMatrix::IsConnected()
{
	return CountConnectedComponents() == 1;
}
bool AdjacencyMatrix::IsCycle()
{
	int* parent = new int[verticesNumber + 1] {0};
	for (int i = 1; i <= verticesNumber; i++)
		parent[i] = -1;

	int u, v, uRoot, vRoot;
	if (isDirected)
		for (u = 1; u <= verticesNumber; u++)
			for (v = 1; v <= verticesNumber; v++)
			{
				ParentHelper(parent, u, v, uRoot, vRoot);
				if (cost[u][v] != INT_MAX && uRoot == vRoot)
				{
					delete[]parent;
					return true;
				}
			}
	else
		for (u = 1; u <= verticesNumber; u++)
			for (v = u + 1; v <= verticesNumber; v++)
			{
				ParentHelper(parent, u, v, uRoot, vRoot);

				if (cost[u][v] != INT_MAX && uRoot == vRoot) {
					delete[]parent;
					return true;
				}
			}

	delete[]parent;

	return false;
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
		for (int v = verticesNumber; v >= 1; v--)
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

AdjacencyMatrix AdjacencyMatrix::Union(AdjacencyMatrix& other)
{
	if (isDirected != other.isDirected)
	{
		throw invalid_argument("both graphs must be directed or not");
	}
	int vertexNumber = verticesNumber > other.verticesNumber ? verticesNumber : other.verticesNumber;
	AdjacencyMatrix result = AdjacencyMatrix(vertexNumber, isDirected);
	int u, v;
	for (u = 1; u <= verticesNumber; u++)
		for (v = isDirected ? 1 : u + 1; v <= verticesNumber; v++)
		{
			if (cost[u][v] != INT_MAX)
				result.AddEdge(u, v, cost[u][v]);
		}

	for (u = 1; u <= other.verticesNumber; u++)
		for (v = isDirected ? 1 : u + 1; v <= other.verticesNumber; v++)
		{
			if (other.cost[u][v] != INT_MAX)
				result.AddEdge(u, v, other.cost[u][v]);
		}
	return result;
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
void AdjacencyMatrix::TestBehavior()
{
	cout << "==========================================\n";
	cout << "    [1] Testing Undirected Graph (DSU, Cycles) \n";
	cout << "==========================================\n";
	AdjacencyMatrix unGraph(5, false); // 5 Vertices, Undirected

	unGraph.AddEdge(1, 2, 10);
	unGraph.AddEdge(2, 3, 20);
	unGraph.AddEdge(1, 4, 30);

	cout << "Graph Edges Count (Expected 3): " << unGraph.CountEdges() << "\n";
	cout << "Graph Total Weight (Expected 60): " << unGraph.CountWeights() << "\n";
	cout << "Is Connected? (Expected 0/False): " << unGraph.IsConnected() << "\n"; // Node 5 is isolated
	cout << "Connected Components (Expected 2): " << unGraph.CountConnectedComponents() << "\n";
	cout << "Is Cycle? (Expected 0/False): " << unGraph.IsCycle() << "\n";
	cout << "Find boss of 3 (Expected 1 or 2 depending on tree): " << unGraph.Find(3) << "\n";

	cout << "\n-> Adding edge (3, 4) to create a cycle...\n";
	unGraph.AddEdge(3, 4, 5);
	cout << "Is Cycle now? (Expected 1/True): " << unGraph.IsCycle() << "\n";

	cout << "\n==========================================\n";
	cout << "    [2] Testing Directed Graph (Traversals) \n";
	cout << "==========================================\n";
	AdjacencyMatrix dirGraph(6, true); // 6 Vertices, Directed

	dirGraph.AddEdge(1, 2);
	dirGraph.AddEdge(1, 3);
	dirGraph.AddEdge(2, 4);
	dirGraph.AddEdge(2, 5);
	dirGraph.AddEdge(3, 6);

	cout << "BFS starting from 1 (Expected {1 2 3 4 5 6 }): \n";
	dirGraph.BreadthFirstSearch(1);

	cout << "DFS starting from 1 (Expected {1 2 4 5 3 6 }): \n";
	dirGraph.DepthFirstSearch(1);


	cout << "\n==========================================\n";
	cout << "    [3] Testing Graph Union \n";
	cout << "==========================================\n";
	AdjacencyMatrix g1(3, false);
	g1.AddEdge(1, 2, 5);

	AdjacencyMatrix g2(4, false);
	g2.AddEdge(2, 3, 10);
	g2.AddEdge(3, 4, 15);
	g2.AddEdge(1, 2, 5); // Overlapping edge

	AdjacencyMatrix g3 = g1.Union(g2);
	cout << "Union Graph Vertices (Expected 4): " << g3.CountVertices() << "\n";
	cout << "Union Graph Edges (Expected 3): " << g3.CountEdges() << "\n";
	cout << "Weight of overlapping edge (1, 2) (Expected 10): " << g3.GetWeight(1, 2) << "\n";

	cout << "\nMatrix Representation of Union Graph:\n";
	g3.PrintMatrix();

	cout << "\nAll tests completed successfully!\n";
}