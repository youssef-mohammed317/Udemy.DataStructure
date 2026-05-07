#include <iostream>
#include <list>
#include "Graph.h"
#include "KruskalAlgorithm.h"
#include "PrimsAlgorithm.h"
#include "DijkstraAlgorithm.h"
#include "OptimalMergePatternAlgorithm.h"

using namespace std;

// دالة مساعدة لطباعة المسارات وحساب التكلفة الإجمالية
void PrintEdges(const list<Edge>& edges)
{
	int totalCost = 0;
	for (auto& e : edges)
	{
		cout << "  Node " << e.src << " -> Node " << e.dest << " (Cost: " << e.weight << ")\n";
		totalCost += e.weight;
	}
	cout << "  => Total Cost: " << totalCost << "\n\n";
}

int main()
{
	cout << "========================================================\n";
	cout << "=== 1. Testing Graph Algorithms (ARPG Map Waypoints) ===\n";
	cout << "========================================================\n\n";

	// بناء جراف من 6 نقط
	Graph g = Graph(6, false);

	// إضافة الخطوط (بافتراض إنها مسارات في الخريطة)
	g.AddEdge(Edge(1, 2, 2));
	g.AddEdge(Edge(1, 3, 4));
	g.AddEdge(Edge(2, 3, 1));
	g.AddEdge(Edge(2, 4, 7));
	g.AddEdge(Edge(3, 5, 3));
	g.AddEdge(Edge(4, 6, 1));
	g.AddEdge(Edge(5, 4, 2));
	g.AddEdge(Edge(5, 6, 5));

	// -----------------------------------------
	// Test 1: Kruskal's Algorithm
	// -----------------------------------------
	cout << "--- Kruskal's Algorithm (Minimum Spanning Tree) ---\n";
	list<Edge> kruskalRes = KruskalAlgorithm::Execute(g);
	PrintEdges(kruskalRes);

	// -----------------------------------------
	// Test 2: Prim's Algorithm
	// -----------------------------------------
	cout << "--- Prim's Algorithm (Minimum Spanning Tree) ---\n";
	// النتيجة المفروض تطلع نفس تكلفة Kruskal بالضبط
	list<Edge> primRes = PrimsAlgorithm::Execute(g);
	PrintEdges(primRes);

	// -----------------------------------------
	// Test 3: Dijkstra's Algorithm
	// -----------------------------------------
	cout << "--- Dijkstra's Algorithm (Shortest Paths from Node 1) ---\n";
	list<Edge>* dijkstraRes = DijkstraAlgorithm::Execute(g, 1);

	for (int i = 2; i <= g.GetVertices(); i++)
	{
		cout << "Path to Node " << i << ":\n";
		if (dijkstraRes[i].empty())
		{
			cout << "  No path found.\n\n";
		}
		else
		{
			PrintEdges(dijkstraRes[i]);
		}
	}

	// تنظيف الميموري الخاصة بديجسترا
	delete[] dijkstraRes;

	cout << "=========================================\n";
	cout << "=== 2. Testing Optimal Merge Pattern ===\n";
	cout << "=========================================\n\n";

	// 5 مصفوفات مترتبة كأمثلة
	int A[] = { 2, 7, 15 };             // Size: 3
	int B[] = { 3, 9 };                 // Size: 2
	int C[] = { 1, 5, 8, 12 };          // Size: 4
	int D[] = { 10 };                   // Size: 1
	int E[] = { 4, 6, 11, 13, 14 };     // Size: 5

	// تنفيذ الدمج الأمثل
	pair<int, int*> mergedData = OptimalMergePatternAlgorithm::Execute(A, B, C, D, E, 3, 2, 4, 1, 5);

	// طباعة النتيجة النهائية
	cout << "Merged Array Size: " << mergedData.first << "\n";
	cout << "Merged Array Elements: \n[ ";
	for (int i = 0; i < mergedData.first; i++)
	{
		cout << mergedData.second[i];
		if (i < mergedData.first - 1) cout << ", ";
	}
	cout << " ]\n\n";

	// تنظيف الميموري بتاعة المصفوفة النهائية اللي اتعملها new جوه دالة Merge
	delete[] mergedData.second;

	return 0;
}