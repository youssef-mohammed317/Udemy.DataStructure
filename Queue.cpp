#include "Queue.h"
Queue::Queue()
{
	rear = front = nullptr;
	size = 0;
}
void Queue::Clear()
{
	Node* temp;
	while (front != nullptr)
	{
		temp = front;
		front = front->GetNext();
		delete temp;
	}
	front = rear = nullptr;
	size = 0;
}
Queue::~Queue()
{
	Clear();
}

bool Queue::IsFull()
{
	try {
		Node* temp = new Node(10);
		delete temp;
		return false;
	}
	catch (const exception& e)
	{
		return true;
	}
}

bool Queue::IsEmpty()
{
	return front == nullptr;
}
void Queue::Enqueue(int data)
{
	if (IsFull())
		throw runtime_error("the queue is full");

	Node* node = new Node(data);
	if (front == nullptr)
	{
		front = rear = node;
	}
	else {
		rear->SetNext(node);
		rear = node;
	}
	size++;
}
int Queue::Dequeue()
{
	if (IsEmpty())
		throw runtime_error("the queue is empty");

	Node* temp = front;
	front = front->GetNext();
	int data = temp->GetData();
	delete temp;
	size--;

	if (front == nullptr)
		rear = nullptr;

	return data;
}
int Queue::Size()
{
	return size;
}
int Queue::First()
{
	if (IsEmpty())
		throw runtime_error("the queue is empty");

	return front->GetData();
}
int Queue::Last()
{
	if (IsEmpty())
		throw runtime_error("the queue is empty");

	return rear->GetData();
}
void Queue::Display()
{
	cout << "{";
	Node* curr = front;
	while (curr != nullptr)
	{
		cout << curr->GetData();
		curr = curr->GetNext();
		if (curr != nullptr)
			cout << ", ";
	}
	cout << "}\n";
}

void PrintTestResult(const string& testName, bool passed)
{
	cout << (passed ? "[PASS] " : "[FAIL] ") << testName << endl;
}

void PrintSection(const string& title)
{
	cout << "\n========== " << title << " ==========\n";
}

void Queue::TestBehavior()
{
	cout << "===== Queue TestBehavior Start =====\n";

	// Test 1: Initial state
	PrintSection("Test 1: Initial State");
	{
		Queue q;
		cout << "Queue content: ";
		q.Display();

		PrintTestResult("Queue should be empty", q.IsEmpty());
		PrintTestResult("Queue size should be 0", q.Size() == 0);
	}

	// Test 2: Enqueue one item
	PrintSection("Test 2: Enqueue One Item");
	{
		Queue q;
		q.Enqueue(10);

		cout << "Queue content after Enqueue(10): ";
		q.Display();

		PrintTestResult("Queue should not be empty", !q.IsEmpty());
		PrintTestResult("Size should be 1", q.Size() == 1);
		PrintTestResult("First should be 10", q.First() == 10);
		PrintTestResult("Last should be 10", q.Last() == 10);
	}

	// Test 3: Enqueue multiple items
	PrintSection("Test 3: Enqueue Multiple Items");
	{
		Queue q;
		q.Enqueue(10);
		q.Enqueue(20);
		q.Enqueue(30);

		cout << "Queue content after Enqueue(10), Enqueue(20), Enqueue(30): ";
		q.Display();

		PrintTestResult("Size should be 3", q.Size() == 3);
		PrintTestResult("First should be 10", q.First() == 10);
		PrintTestResult("Last should be 30", q.Last() == 30);
	}

	// Test 4: FIFO behavior
	PrintSection("Test 4: FIFO Behavior");
	{
		Queue q;
		q.Enqueue(10);
		q.Enqueue(20);
		q.Enqueue(30);

		cout << "Queue before dequeues: ";
		q.Display();

		bool passed = true;

		int x1 = q.Dequeue();
		cout << "After first Dequeue() -> removed: " << x1 << ", queue: ";
		q.Display();
		passed &= (x1 == 10);

		int x2 = q.Dequeue();
		cout << "After second Dequeue() -> removed: " << x2 << ", queue: ";
		q.Display();
		passed &= (x2 == 20);

		int x3 = q.Dequeue();
		cout << "After third Dequeue() -> removed: " << x3 << ", queue: ";
		q.Display();
		passed &= (x3 == 30);

		PrintTestResult("Queue should follow FIFO", passed);
		PrintTestResult("Queue should be empty after all dequeues", q.IsEmpty());
		PrintTestResult("Size should be 0 after all dequeues", q.Size() == 0);
	}

	// Test 5: First and Last after dequeue
	PrintSection("Test 5: First and Last After Dequeue");
	{
		Queue q;
		q.Enqueue(5);
		q.Enqueue(10);
		q.Enqueue(15);

		cout << "Queue before Dequeue(): ";
		q.Display();

		q.Dequeue();

		cout << "Queue after one Dequeue(): ";
		q.Display();

		PrintTestResult("First should become 10", q.First() == 10);
		PrintTestResult("Last should remain 15", q.Last() == 15);
		PrintTestResult("Size should become 2", q.Size() == 2);
	}

	// Test 6: Single element enqueue/dequeue
	PrintSection("Test 6: Single Element Case");
	{
		Queue q;
		q.Enqueue(42);

		cout << "Queue after Enqueue(42): ";
		q.Display();

		int removed = q.Dequeue();

		cout << "Queue after Dequeue(): ";
		q.Display();

		bool passed = (removed == 42) && q.IsEmpty() && q.Size() == 0;
		PrintTestResult("Single element enqueue/dequeue works correctly", passed);
	}

	// Test 7: Clear
	PrintSection("Test 7: Clear");
	{
		Queue q;
		q.Enqueue(1);
		q.Enqueue(2);
		q.Enqueue(3);

		cout << "Queue before Clear(): ";
		q.Display();

		q.Clear();

		cout << "Queue after Clear(): ";
		q.Display();

		PrintTestResult("Queue should be empty after Clear()", q.IsEmpty());
		PrintTestResult("Size should be 0 after Clear()", q.Size() == 0);
	}

	// Test 8: Reuse after clear
	PrintSection("Test 8: Reuse After Clear");
	{
		Queue q;
		q.Enqueue(1);
		q.Enqueue(2);
		q.Clear();
		q.Enqueue(100);

		cout << "Queue after Clear() then Enqueue(100): ";
		q.Display();

		bool passed = (q.First() == 100) && (q.Last() == 100) && (q.Size() == 1);
		PrintTestResult("Queue can be reused after Clear()", passed);
	}

	// Test 9: Dequeue on empty
	PrintSection("Test 9: Exception - Dequeue on Empty");
	{
		Queue q;
		bool passed = false;

		try
		{
			q.Dequeue();
		}
		catch (const exception& e)
		{
			passed = true;
			cout << "Caught expected exception: " << e.what() << endl;
		}

		PrintTestResult("Dequeue on empty should throw exception", passed);
	}

	// Test 10: First on empty
	PrintSection("Test 10: Exception - First on Empty");
	{
		Queue q;
		bool passed = false;

		try
		{
			q.First();
		}
		catch (const exception& e)
		{
			passed = true;
			cout << "Caught expected exception: " << e.what() << endl;
		}

		PrintTestResult("First on empty should throw exception", passed);
	}

	// Test 11: Last on empty
	PrintSection("Test 11: Exception - Last on Empty");
	{
		Queue q;
		bool passed = false;

		try
		{
			q.Last();
		}
		catch (const exception& e)
		{
			passed = true;
			cout << "Caught expected exception: " << e.what() << endl;
		}

		PrintTestResult("Last on empty should throw exception", passed);
	}

	cout << "\n===== Queue TestBehavior End =====\n";
}