#include <iostream>
#include <stdexcept>
#include "AdjList.h"
#include "VertexQueue.h"
#include "VertexStack.h"

using namespace std;

int main()
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
	catch (const invalid_argument& e)
	{
		cout << "  Error: " << e.what() << "\n";
	}

	try
	{
		cout << "  Weight of path to Node 5: ";
		cout << node1.GetWeight(5) << "\n";
	}
	catch (const invalid_argument& e)
	{
		cout << "[Exception Caught] " << e.what() << "\n\n";
	}

	cout << "[+] Testing Deep Copy (Copy Constructor)...\n";
	AdjList copiedNode(node1);
	cout << "  -> Removing Node 3 from the Original List...\n\n";
	node1.RemoveEdge(3);

	cout << "--- Original List (After Deletion) ---\n";
	node1.Print();
	cout << "--- Copied List (Should still have Node 3) ---\n";
	copiedNode.Print();

	// ========================================================
	// SECTION 2: Testing VertexQueue (FIFO for BFS)
	// ========================================================
	cout << "========================================================\n";
	cout << "=== Testing VertexQueue (FIFO for BFS)               ===\n";
	cout << "========================================================\n\n";

	VertexQueue q;
	cout << "[+] Enqueuing vertices: 10, 20, 30...\n";
	q.Enqueue(10);
	q.Enqueue(20);
	q.Enqueue(30);

	cout << "  Queue Size: " << q.GetSize() << "\n";
	cout << "  Front Element (Peek): " << q.Peek() << "\n\n";

	cout << "[+] Dequeuing all elements:\n";
	while (!q.IsEmpty())
	{
		cout << "  Dequeued: " << q.Dequeue() << "\n";
	}

	cout << "\n[?] Testing Queue Underflow Exception...\n";
	try
	{
		q.Dequeue();
	}
	catch (const underflow_error& e)
	{
		cout << "  [Exception Caught] " << e.what() << "\n\n";
	}

	// ========================================================
	// SECTION 3: Testing VertexStack (LIFO for DFS)
	// ========================================================
	cout << "========================================================\n";
	cout << "=== Testing VertexStack (LIFO for DFS)               ===\n";
	cout << "========================================================\n\n";

	VertexStack s;
	cout << "[+] Pushing vertices: 100, 200, 300...\n";
	s.Push(100);
	s.Push(200);
	s.Push(300);

	cout << "  Stack Size: " << s.GetSize() << "\n";
	cout << "  Top Element (Peek): " << s.Peek() << "\n\n";

	cout << "[+] Popping all elements (LIFO Order):\n";
	while (!s.IsEmpty())
	{
		cout << "  Popped: " << s.Pop() << "\n";
	}

	cout << "\n[?] Testing Stack Underflow Exception...\n";
	try
	{
		s.Pop();
	}
	catch (const underflow_error& e)
	{
		cout << "  [Exception Caught] " << e.what() << "\n\n";
	}

	cout << "========================================================\n";
	cout << "=== All Tests Completed Successfully                 ===\n";
	cout << "========================================================\n";

	return 0;
}