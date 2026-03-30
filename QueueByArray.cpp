#include "QueueByArray.h"
QueueByArray::QueueByArray(int size)
{
	this->size = size;
	arr = new int[size];
	rear = front = -1;
	length = 0;
}
void QueueByArray::Clear()
{
	rear = front = -1;
	length = 0;
}
QueueByArray::~QueueByArray()
{
	delete[] arr;
	arr = nullptr;
}

bool QueueByArray::IsFull()
{
	return rear == size - 1;
}

bool QueueByArray::IsEmpty()
{
	return front == rear;
}
void QueueByArray::Enqueue(int data)
{
	if (IsFull())
		throw runtime_error("the queue is full");

	arr[++rear] = data;

	length++;
}
int QueueByArray::Dequeue()
{
	if (IsEmpty())
		throw runtime_error("the queue is empty");

	return arr[++front];
}
int QueueByArray::Size()
{
	return length;
}
int QueueByArray::First()
{
	if (IsEmpty())
		throw runtime_error("the queue is empty");

	return arr[front + 1];
}
int QueueByArray::Last()
{
	if (IsEmpty())
		throw runtime_error("the queue is empty");

	return arr[rear];
}
void QueueByArray::Display()
{
	cout << "{";
	for (int i = front + 1; i <= rear; i++)
	{
		cout << arr[i];
		if (i < rear)
		{
			cout << ", ";
		}
	}
	cout << "}\n";
}

void QueueByArray::TestBehavior()
{
	cout << "===== QueueByArray TestBehavior Start =====\n";

	// Test 1: Initial state
	cout << "\n========== Test 1: Initial State ==========\n";
	{
		QueueByArray q(10);
		cout << "QueueByArray content: ";
		q.Display();

		cout << (q.IsEmpty() ? "[PASS] " : "[FAIL] ") << "QueueByArray should be empty" << endl;
		cout << ((q.Size() == 0) ? "[PASS] " : "[FAIL] ") << "QueueByArray size should be 0" << endl;
	}

	// Test 2: Enqueue one item
	cout << "\n========== Test 2: Enqueue One Item ==========\n";
	{
		QueueByArray q(10);
		q.Enqueue(10);

		cout << "QueueByArray content after Enqueue(10): ";
		q.Display();

		cout << (!q.IsEmpty() ? "[PASS] " : "[FAIL] ") << "QueueByArray should not be empty" << endl;
		cout << ((q.Size() == 1) ? "[PASS] " : "[FAIL] ") << "Size should be 1" << endl;
		cout << ((q.First() == 10) ? "[PASS] " : "[FAIL] ") << "First should be 10" << endl;
		cout << ((q.Last() == 10) ? "[PASS] " : "[FAIL] ") << "Last should be 10" << endl;
	}

	// Test 3: Enqueue multiple items
	cout << "\n========== Test 3: Enqueue Multiple Items ==========\n";
	{
		QueueByArray q(10);
		q.Enqueue(10);
		q.Enqueue(20);
		q.Enqueue(30);

		cout << "QueueByArray content after Enqueue(10), Enqueue(20), Enqueue(30): ";
		q.Display();

		cout << ((q.Size() == 3) ? "[PASS] " : "[FAIL] ") << "Size should be 3" << endl;
		cout << ((q.First() == 10) ? "[PASS] " : "[FAIL] ") << "First should be 10" << endl;
		cout << ((q.Last() == 30) ? "[PASS] " : "[FAIL] ") << "Last should be 30" << endl;
	}

	// Test 4: FIFO behavior
	cout << "\n========== Test 4: FIFO Behavior ==========\n";
	{
		QueueByArray q(10);
		q.Enqueue(10);
		q.Enqueue(20);
		q.Enqueue(30);

		cout << "QueueByArray before dequeues: ";
		q.Display();

		bool passed = true;

		int x1 = q.Dequeue();
		cout << "After first Dequeue() -> removed: " << x1 << ", QueueByArray: ";
		q.Display();
		passed &= (x1 == 10);

		int x2 = q.Dequeue();
		cout << "After second Dequeue() -> removed: " << x2 << ", QueueByArray: ";
		q.Display();
		passed &= (x2 == 20);

		int x3 = q.Dequeue();
		cout << "After third Dequeue() -> removed: " << x3 << ", QueueByArray: ";
		q.Display();
		passed &= (x3 == 30);

		cout << (passed ? "[PASS] " : "[FAIL] ") << "QueueByArray should follow FIFO" << endl;
		cout << (q.IsEmpty() ? "[PASS] " : "[FAIL] ") << "QueueByArray should be empty after all dequeues" << endl;
		cout << ((q.Size() == 0) ? "[PASS] " : "[FAIL] ") << "Size should be 0 after all dequeues" << endl;
	}

	// Test 5: First and Last after dequeue
	cout << "\n========== Test 5: First and Last After Dequeue ==========\n";
	{
		QueueByArray q(10);
		q.Enqueue(5);
		q.Enqueue(10);
		q.Enqueue(15);

		cout << "QueueByArray before Dequeue(): ";
		q.Display();

		q.Dequeue();

		cout << "QueueByArray after one Dequeue(): ";
		q.Display();

		cout << ((q.First() == 10) ? "[PASS] " : "[FAIL] ") << "First should become 10" << endl;
		cout << ((q.Last() == 15) ? "[PASS] " : "[FAIL] ") << "Last should remain 15" << endl;
		cout << ((q.Size() == 2) ? "[PASS] " : "[FAIL] ") << "Size should become 2" << endl;
	}

	// Test 6: Single element case
	cout << "\n========== Test 6: Single Element Case ==========\n";
	{
		QueueByArray q(10);
		q.Enqueue(42);

		cout << "QueueByArray after Enqueue(42): ";
		q.Display();

		int removed = q.Dequeue();

		cout << "QueueByArray after Dequeue(): ";
		q.Display();

		bool passed = (removed == 42) && q.IsEmpty() && q.Size() == 0;
		cout << (passed ? "[PASS] " : "[FAIL] ") << "Single element enqueue/dequeue works correctly" << endl;
	}

	// Test 7: Clear
	cout << "\n========== Test 7: Clear ==========\n";
	{
		QueueByArray q(10);
		q.Enqueue(1);
		q.Enqueue(2);
		q.Enqueue(3);

		cout << "QueueByArray before Clear(): ";
		q.Display();

		q.Clear();

		cout << "QueueByArray after Clear(): ";
		q.Display();

		cout << (q.IsEmpty() ? "[PASS] " : "[FAIL] ") << "QueueByArray should be empty after Clear()" << endl;
		cout << ((q.Size() == 0) ? "[PASS] " : "[FAIL] ") << "Size should be 0 after Clear()" << endl;
	}

	// Test 8: Reuse after clear
	cout << "\n========== Test 8: Reuse After Clear ==========\n";
	{
		QueueByArray q(10);
		q.Enqueue(1);
		q.Enqueue(2);
		q.Clear();
		q.Enqueue(100);

		cout << "QueueByArray after Clear() then Enqueue(100): ";
		q.Display();

		bool passed = (q.First() == 100) && (q.Last() == 100) && (q.Size() == 1);
		cout << (passed ? "[PASS] " : "[FAIL] ") << "QueueByArray can be reused after Clear()" << endl;
	}

	// Test 9: Dequeue on empty
	cout << "\n========== Test 9: Exception - Dequeue on Empty ==========\n";
	{
		QueueByArray q(10);
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
		QueueByArray q(10);
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
		QueueByArray q(10);
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

	cout << "\n===== QueueByArray TestBehavior End =====\n";
}