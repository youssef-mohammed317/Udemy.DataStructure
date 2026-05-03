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


	auto it = find_if(cost[u].begin(), cost[u].end(), [v](const Node& n) {
		return n.vertex == v;
		});


	if (it != cost[u].end())
		it->weight += weight;
	else
		cost[u].push_back(Node(v, weight));

	if (!isDirected && u != v)
	{
		auto it = find_if(cost[v].begin(), cost[v].end(), [u](const Node& n) {
			return n.vertex == u;
			});
		if (it != cost[v].end())
			it->weight += weight;
		else
			cost[v].push_back(Node(u, weight));
	}


}

void AdjacencyList::RemoveEdge(int u, int v)
{
	ValidateEdge(u, v);

	cost[u].remove_if([v](const Node& n) {
		return n.vertex == v;
		});
	if (!isDirected)
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
	if (!isDirected)
	{
		for (u = 1; u <= verticesNumber; u++)
		{
			for (const Node& n : cost[u])
			{
				v = n.vertex;
				ParentHelper(parent, u, v, uRoot, vRoot);
			}
		}
	}
	if (isDirected)
	{
		// later	
		delete[]parent;
		throw logic_error("not implemented yet");
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
			if (isDirected || u <= n.vertex)
				weights += n.weight;
		}
	}

	return weights;

}

int AdjacencyList::CountEdges()
{
	int edges = 0;


	for (int u = 1; u <= verticesNumber; u++)
	{
		for (const Node& n : cost[u]) {
			if (isDirected || u <= n.vertex)
				edges++;
		}
	}

	return   edges;
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
	if (isDirected)
	{
		// later	
		delete[]parent;
		throw logic_error("not implemented yet");
	}

	delete[]parent;
	return false;
}

void AdjacencyList::BreadthFirstSearch(int startVertex)
{
	ValidateVertex(startVertex);
	bool* visited = new bool[verticesNumber + 1] {0};
	queue<int> q;
	visited[startVertex] = true;
	q.push(startVertex);
	cout << "{";
	int u, v;
	while (!q.empty())
	{
		u = q.front(); q.pop();
		cout << u << " ";

		for (const Node& n : cost[u])
		{
			v = n.vertex;
			if (!visited[v])
			{
				q.push(v);
				visited[v] = true;
			}
		}
	}
	cout << "}\n";
	delete[]visited;
}

void AdjacencyList::DepthFirstSearch(int startVertex)
{
	ValidateVertex(startVertex);
	bool* visited = new bool[verticesNumber + 1] {0};
	stack<int> s;
	s.push(startVertex);
	cout << "{";
	int u, v;
	while (!s.empty())
	{
		u = s.top(); s.pop();
		if (!visited[u])
		{
			visited[u] = true;
			cout << u << " ";

			for (const Node& n : cost[u])
			{
				v = n.vertex;
				if (!visited[v])
				{
					s.push(v);
				}
			}
		}
	}
	cout << "}\n";
	delete[]visited;
}

AdjacencyList* AdjacencyList::Union(AdjacencyList& other)
{
	if (other.isDirected != isDirected)
		throw exception("invalid input");
	AdjacencyList* result = new AdjacencyList(other.verticesNumber > verticesNumber ? other.verticesNumber : verticesNumber, isDirected);

	for (int u = 1; u <= verticesNumber; u++)
	{
		for (const Node& n : cost[u])
		{
			if (isDirected || u <= n.vertex)
				result->AddEdge(u, n.vertex, n.weight);
		}
	}
	for (int u = 1; u <= other.verticesNumber; u++)
	{
		for (const Node& n : other.cost[u])
		{
			if (isDirected || u <= n.vertex)
				result->AddEdge(u, n.vertex, n.weight);
		}
	}
	return result;
}
void AdjacencyList::TestBehavior()
{
	try {
		cout << "=======================================\n";
		cout << "   [1] TESTING UNDIRECTED LIST \n";
		cout << "=======================================\n";
		AdjacencyList undirectedGraph(6, false);

		undirectedGraph.AddEdge(1, 2);
		undirectedGraph.AddEdge(2, 3);
		undirectedGraph.AddEdge(3, 4);
		undirectedGraph.AddEdge(4, 5);
		undirectedGraph.AddEdge(5, 6);

		cout << "Total Vertices: " << undirectedGraph.CountVertices() << "\n";
		cout << "Total Edges: " << undirectedGraph.CountEdges() << "\n";
		cout << "Is Connected? " << (undirectedGraph.IsConnected() ? "Yes" : "No") << "\n";
		cout << "Has Cycle? " << (undirectedGraph.IsCycle() ? "Yes" : "No") << "\n";

		cout << "BFS (from 1): ";
		undirectedGraph.BreadthFirstSearch(1);

		cout << "DFS (from 1): ";
		undirectedGraph.DepthFirstSearch(1);

		cout << "\n=======================================\n";
		cout << "   [2] TESTING DIRECTED LIST \n";
		cout << "=======================================\n";
		AdjacencyList directedGraph(4, true);
		directedGraph.AddEdge(1, 2);
		directedGraph.AddEdge(1, 3);
		directedGraph.AddEdge(2, 4);
		directedGraph.AddEdge(3, 4);

		cout << "Total Edges: " << directedGraph.CountEdges() << "\n";

		cout << "BFS (from 1): ";
		directedGraph.BreadthFirstSearch(1);

		cout << "DFS (from 1): ";
		directedGraph.DepthFirstSearch(1);

		cout << "\n=======================================\n";
		cout << "   [3] TESTING LIST UNION \n";
		cout << "=======================================\n";
		AdjacencyList list1(3, false);
		list1.AddEdge(1, 2, 5);

		AdjacencyList list2(4, false);
		list2.AddEdge(2, 3, 10);
		list2.AddEdge(3, 4, 15);
		list2.AddEdge(1, 2, 5); // Overlapping edge

		AdjacencyList* list3 = list1.Union(list2); // Using Pointer
		cout << "Union Graph Vertices (Expected 4): " << list3->CountVertices() << "\n";
		cout << "Union Graph Edges (Expected 3): " << list3->CountEdges() << "\n";
		cout << "Weight of overlapping edge (1, 2) (Expected 10): " << list3->GetWeight(1, 2) << "\n";

		delete list3; // Memory cleanup!
		cout << "\nAll List Tests Completed Successfully!\n";
	}
	catch (const exception& e) {
		cout << "\n[ERROR] Exception Caught in List: " << e.what() << "\n";
	}
}