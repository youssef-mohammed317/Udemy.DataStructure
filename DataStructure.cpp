#include <iostream>
#include <stdexcept>
#include "AdjList.h"

using namespace std;

int main()
{
	cout << "========================================================\n";
	cout << "=== Testing Adjacency List (With Exceptions & Print) ===\n";
	cout << "========================================================\n\n";

	// 1. Test Constructor & AddEdge
	cout << "[+] Building connections for Node 1...\n";
	AdjList node1(1);
	node1.AddEdge(2, 15);
	node1.AddEdge(3, 8);
	node1.AddEdge(4, 25);

	// Use the class's built-in print method
	node1.Print();

	// 2. Test Exceptions in GetWeight
	cout << "[?] Testing Exception Handling in GetWeight()...\n";

	// Path exists
	try
	{
		cout << "  Weight of path to Node 3: " << node1.GetWeight(3) << "\n";
	}
	catch (const invalid_argument& e)
	{
		cout << "  Error: " << e.what() << "\n";
	}

	// Path does not exist (will throw an exception)
	try
	{
		cout << "  Weight of path to Node 5: ";
		cout << node1.GetWeight(5) << "\n";
	}
	catch (const invalid_argument& e)
	{
		// Catch the exception and print the custom error message
		cout << "[Exception Caught] " << e.what() << "\n\n";
	}

	// 3. Test Deep Copy (Copy Constructor)
	cout << "[+] Testing Deep Copy (Copy Constructor)...\n";
	AdjList copiedNode(node1);

	cout << "  -> Removing Node 3 from the Original List...\n\n";
	node1.RemoveEdge(3); // Remove from the original list only

	cout << "--- Original List (After Deletion) ---\n";
	node1.Print();

	cout << "--- Copied List (Should still have Node 3) ---\n";
	copiedNode.Print();

	// 4. Test Assignment Operator (=)
	cout << "[+] Testing Assignment Operator...\n";
	AdjList assignedNode(99);
	assignedNode.AddEdge(100, 50);

	assignedNode = node1;

	cout << "--- Assigned List (Should match the modified Original) ---\n";
	assignedNode.Print();

	// 5. Test Clear
	cout << "[-] Testing Clear on Copied List...\n";
	copiedNode.Clear();
	copiedNode.Print();

	return 0;
}