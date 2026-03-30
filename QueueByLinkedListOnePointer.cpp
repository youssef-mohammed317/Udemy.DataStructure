#include "QueueByLinkedListOnePointer.h"
QueueByLinkedListOnePointer::QueueByLinkedListOnePointer()
{
	front = nullptr;
	size = 0;
}
void QueueByLinkedListOnePointer::Clear()
{
	Node* temp;
	while (front != nullptr)
	{
		temp = front;
		front = front->GetNext();
		delete temp;
	}
	front = nullptr;
	size = 0;
}
QueueByLinkedListOnePointer::~QueueByLinkedListOnePointer()
{
	Clear();
}

bool QueueByLinkedListOnePointer::IsFull()
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

bool QueueByLinkedListOnePointer::IsEmpty()
{
	return front == nullptr;
}
void QueueByLinkedListOnePointer::Enqueue(int data)
{
	if (IsFull())
		throw runtime_error("the queue is full");

	Node* node = new Node(data);
	if (front == nullptr)
	{
		front = node;
	}
	else {
		Node* temp = front;

		while (temp->GetNext() != nullptr)
			temp = temp->GetNext();

		temp->SetNext(node);
	}
	size++;
}
int QueueByLinkedListOnePointer::Dequeue()
{
	if (IsEmpty())
		throw runtime_error("the queue is empty");

	Node* temp = front;
	front = front->GetNext();
	int data = temp->GetData();
	delete temp;
	size--;
	return data;
}
int QueueByLinkedListOnePointer::Size()
{
	return size;
}
int QueueByLinkedListOnePointer::First()
{
	if (IsEmpty())
		throw runtime_error("the queue is empty");

	return front->GetData();
}
int QueueByLinkedListOnePointer::Last()
{
	if (IsEmpty())
		throw runtime_error("the queue is empty");
	Node* temp = front;
	while (temp->GetNext() != nullptr)
		temp = temp->GetNext();
	return temp->GetData();
}
void QueueByLinkedListOnePointer::Display()
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
void QueueByLinkedListOnePointer::TestBehavior()
{
	cout << "===== QueueByLinkedListOnePointer TestBehavior Start =====\n";

	// Test 1: Initial state
	cout << "\n========== Test 1: Initial State ==========\n";
	{
		QueueByLinkedListOnePointer q;
		cout << "QueueByLinkedListOnePointer content: ";
		q.Display();

		cout << (q.IsEmpty() ? "[PASS] " : "[FAIL] ") << "QueueByLinkedListOnePointer should be empty" << endl;
		cout << ((q.Size() == 0) ? "[PASS] " : "[FAIL] ") << "QueueByLinkedListOnePointer size should be 0" << endl;
	}

	// Test 2: Enqueue one item
	cout << "\n========== Test 2: Enqueue One Item ==========\n";
	{
		QueueByLinkedListOnePointer q;
		q.Enqueue(10);

		cout << "QueueByLinkedListOnePointer content after Enqueue(10): ";
		q.Display();

		cout << (!q.IsEmpty() ? "[PASS] " : "[FAIL] ") << "QueueByLinkedListOnePointer should not be empty" << endl;
		cout << ((q.Size() == 1) ? "[PASS] " : "[FAIL] ") << "Size should be 1" << endl;
		cout << ((q.First() == 10) ? "[PASS] " : "[FAIL] ") << "First should be 10" << endl;
		cout << ((q.Last() == 10) ? "[PASS] " : "[FAIL] ") << "Last should be 10" << endl;
	}

	// Test 3: Enqueue multiple items
	cout << "\n========== Test 3: Enqueue Multiple Items ==========\n";
	{
		QueueByLinkedListOnePointer q;
		q.Enqueue(10);
		q.Enqueue(20);
		q.Enqueue(30);

		cout << "QueueByLinkedListOnePointer content after Enqueue(10), Enqueue(20), Enqueue(30): ";
		q.Display();

		cout << ((q.Size() == 3) ? "[PASS] " : "[FAIL] ") << "Size should be 3" << endl;
		cout << ((q.First() == 10) ? "[PASS] " : "[FAIL] ") << "First should be 10" << endl;
		cout << ((q.Last() == 30) ? "[PASS] " : "[FAIL] ") << "Last should be 30" << endl;
	}

	// Test 4: FIFO behavior
	cout << "\n========== Test 4: FIFO Behavior ==========\n";
	{
		QueueByLinkedListOnePointer q;
		q.Enqueue(10);
		q.Enqueue(20);
		q.Enqueue(30);

		cout << "QueueByLinkedListOnePointer before dequeues: ";
		q.Display();

		bool passed = true;

		int x1 = q.Dequeue();
		cout << "After first Dequeue() -> removed: " << x1 << ", QueueByLinkedListOnePointer: ";
		q.Display();
		passed &= (x1 == 10);

		int x2 = q.Dequeue();
		cout << "After second Dequeue() -> removed: " << x2 << ", QueueByLinkedListOnePointer: ";
		q.Display();
		passed &= (x2 == 20);

		int x3 = q.Dequeue();
		cout << "After third Dequeue() -> removed: " << x3 << ", QueueByLinkedListOnePointer: ";
		q.Display();
		passed &= (x3 == 30);

		cout << (passed ? "[PASS] " : "[FAIL] ") << "QueueByLinkedListOnePointer should follow FIFO" << endl;
		cout << (q.IsEmpty() ? "[PASS] " : "[FAIL] ") << "QueueByLinkedListOnePointer should be empty after all dequeues" << endl;
		cout << ((q.Size() == 0) ? "[PASS] " : "[FAIL] ") << "Size should be 0 after all dequeues" << endl;
	}

	// Test 5: First and Last after dequeue
	cout << "\n========== Test 5: First and Last After Dequeue ==========\n";
	{
		QueueByLinkedListOnePointer q;
		q.Enqueue(5);
		q.Enqueue(10);
		q.Enqueue(15);

		cout << "QueueByLinkedListOnePointer before Dequeue(): ";
		q.Display();

		q.Dequeue();

		cout << "QueueByLinkedListOnePointer after one Dequeue(): ";
		q.Display();

		cout << ((q.First() == 10) ? "[PASS] " : "[FAIL] ") << "First should become 10" << endl;
		cout << ((q.Last() == 15) ? "[PASS] " : "[FAIL] ") << "Last should remain 15" << endl;
		cout << ((q.Size() == 2) ? "[PASS] " : "[FAIL] ") << "Size should become 2" << endl;
	}

	// Test 6: Single element case
	cout << "\n========== Test 6: Single Element Case ==========\n";
	{
		QueueByLinkedListOnePointer q;
		q.Enqueue(42);

		cout << "QueueByLinkedListOnePointer after Enqueue(42): ";
		q.Display();

		int removed = q.Dequeue();

		cout << "QueueByLinkedListOnePointer after Dequeue(): ";
		q.Display();

		bool passed = (removed == 42) && q.IsEmpty() && q.Size() == 0;
		cout << (passed ? "[PASS] " : "[FAIL] ") << "Single element enqueue/dequeue works correctly" << endl;
	}

	// Test 7: Clear
	cout << "\n========== Test 7: Clear ==========\n";
	{
		QueueByLinkedListOnePointer q;
		q.Enqueue(1);
		q.Enqueue(2);
		q.Enqueue(3);

		cout << "QueueByLinkedListOnePointer before Clear(): ";
		q.Display();

		q.Clear();

		cout << "QueueByLinkedListOnePointer after Clear(): ";
		q.Display();

		cout << (q.IsEmpty() ? "[PASS] " : "[FAIL] ") << "QueueByLinkedListOnePointer should be empty after Clear()" << endl;
		cout << ((q.Size() == 0) ? "[PASS] " : "[FAIL] ") << "Size should be 0 after Clear()" << endl;
	}

	// Test 8: Reuse after clear
	cout << "\n========== Test 8: Reuse After Clear ==========\n";
	{
		QueueByLinkedListOnePointer q;
		q.Enqueue(1);
		q.Enqueue(2);
		q.Clear();
		q.Enqueue(100);

		cout << "QueueByLinkedListOnePointer after Clear() then Enqueue(100): ";
		q.Display();

		bool passed = (q.First() == 100) && (q.Last() == 100) && (q.Size() == 1);
		cout << (passed ? "[PASS] " : "[FAIL] ") << "QueueByLinkedListOnePointer can be reused after Clear()" << endl;
	}

	// Test 9: Dequeue on empty
	cout << "\n========== Test 9: Exception - Dequeue on Empty ==========\n";
	{
		QueueByLinkedListOnePointer q;
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

		cout << (passed ? "[PASS] " : "[FAIL] ") << "Dequeue on empty should throw exception" << endl;
	}

	// Test 10: First on empty
	cout << "\n========== Test 10: Exception - First on Empty ==========\n";
	{
		QueueByLinkedListOnePointer q;
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

		cout << (passed ? "[PASS] " : "[FAIL] ") << "First on empty should throw exception" << endl;
	}

	// Test 11: Last on empty
	cout << "\n========== Test 11: Exception - Last on Empty ==========\n";
	{
		QueueByLinkedListOnePointer q;
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

		cout << (passed ? "[PASS] " : "[FAIL] ") << "Last on empty should throw exception" << endl;
	}

	cout << "\n===== QueueByLinkedListOnePointer TestBehavior End =====\n";
}