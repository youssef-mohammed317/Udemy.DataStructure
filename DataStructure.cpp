#include <iostream>
#include <stdexcept>
#include "AdjList.h"
#include "VertexQueue.h"
#include "VertexStack.h"
#include "Graph.h"
#include "DisjointSet.h"

using namespace std;

int main()
{
	try
	{
		// ========================================================
		// SECTION 1: Testing Adjacency List
		// ========================================================
		cout << "========================================================\n";
		cout << "=== Testing Adjacency List (With Exceptions & Print) ===\n";
		cout << "========================================================\n\n";

		cout << "[+] Building connections for Node 1...\n";
		AdjList node1(1);
		node1.AddEdge(2, 15);
		node1.AddEdge(3, 8);
		node1.AddEdge(4, 25);

		node1.Print();

		cout << "[?] Testing Exception Handling in GetWeight()...\n";
		try
		{
			cout << "  Weight of path to Node 3: " << node1.GetWeight(3) << "\n";
		}
		catch (const invalid_argument& e) { cout << "  Error: " << e.what() << "\n"; }

		try
		{
			cout << "  Weight of path to Node 5: ";
			cout << node1.GetWeight(5) << "\n";
		}
		catch (const invalid_argument& e) { cout << "[Exception Caught] " << e.what() << "\n\n"; }


		// ========================================================
		// SECTION 2: Testing VertexQueue (FIFO for BFS)
		// ========================================================
		cout << "========================================================\n";
		cout << "=== Testing VertexQueue (FIFO for BFS)               ===\n";
		cout << "========================================================\n\n";

		VertexQueue q;
		q.Enqueue(10);
		q.Enqueue(20);
		q.Enqueue(30);

		cout << "[+] Dequeuing all elements (FIFO):\n";
		while (!q.IsEmpty()) { cout << "  Dequeued: " << q.Dequeue() << "\n"; }


		// ========================================================
		// SECTION 3: Testing VertexStack (LIFO for DFS)
		// ========================================================
		cout << "\n========================================================\n";
		cout << "=== Testing VertexStack (LIFO for DFS)               ===\n";
		cout << "========================================================\n\n";

		VertexStack s;
		s.Push(100);
		s.Push(200);
		s.Push(300);

		cout << "[+] Popping all elements (LIFO):\n";
		while (!s.IsEmpty()) { cout << "  Popped: " << s.Pop() << "\n"; }


		// ========================================================
		// SECTION 4: Testing Graph (1-Based Indexing)
		// ========================================================
		cout << "\n========================================================\n";
		cout << "=== Testing Graph Class (1-Based & Exceptions)      ===\n";
		cout << "========================================================\n\n";

		Graph myGraph(5, false); // Undirected graph with 5 vertices

		cout << "[+] Adding edges (1-based)...\n";
		myGraph.AddEdge(1, 2, 10);
		myGraph.AddEdge(1, 5, 20);
		myGraph.AddEdge(2, 3, 5);
		myGraph.AddEdge(4, 5, 30);

		myGraph.PrintGraph();

		cout << "\n[?] Checking HasEdge:\n";
		cout << "  Has edge (1, 5)? " << (myGraph.HasEdge(1, 5) ? "Yes" : "No") << "\n";
		cout << "  Has edge (5, 1)? " << (myGraph.HasEdge(5, 1) ? "Yes" : "No") << " (Should be Yes - Undirected)\n";

		cout << "\n[!] Testing Graph Boundary Exceptions:\n";
		try {
			cout << "  Attempting AddEdge(0, 1): ";
			myGraph.AddEdge(0, 1, 10);
		}
		catch (const out_of_range& e) { cout << "[Caught] " << e.what() << "\n"; }

		try {
			cout << "  Attempting AddEdge(1, 6): ";
			myGraph.AddEdge(1, 6, 10);
		}
		catch (const out_of_range& e) { cout << "[Caught] " << e.what() << "\n"; }


		// ========================================================
		// SECTION 5: Testing DisjointSet (1-Based & Weighted Union)
		// ========================================================
		cout << "\n========================================================\n";
		cout << "=== Testing DisjointSet (1-Based & Union by Size)    ===\n";
		cout << "========================================================\n\n";

		DisjointSet ds(5);
		cout << "[+] Performing Unions: (1,2), (3,4), (2,4)...\n";

		ds.UnionSets(ds.Find(1), ds.Find(2));
		ds.UnionSets(ds.Find(3), ds.Find(4));
		ds.UnionSets(ds.Find(2), ds.Find(4)); // Now 1, 2, 3, 4 are connected

		cout << "\n[?] Checking Connectivity:\n";
		cout << "  Root of 1: " << ds.Find(1) << "\n";
		cout << "  Root of 4: " << ds.Find(4) << "\n";

		if (ds.Find(1) == ds.Find(4))
			cout << "  Result: 1 and 4 are in the same set! ✅\n";

		cout << "  Root of 5: " << ds.Find(5) << " (Should be its own root: 5)\n";

		cout << "\n[!] Testing DisjointSet Exceptions:\n";
		try {
			ds.Find(6);
		}
		catch (const out_of_range& e) { cout << "  [Caught] " << e.what() << "\n"; }

		cout << "\n[-] Clearing the graph...\n";
		myGraph.Clear();
		myGraph.PrintGraph();

	}
	catch (const exception& e)
	{
		cout << "\nCRITICAL ERROR: " << e.what() << endl;
	}

	cout << "\n========================================================\n";
	cout << "=== All Unit Tests Completed Successfully!           ===\n";
	cout << "========================================================\n";

	return 0;
}