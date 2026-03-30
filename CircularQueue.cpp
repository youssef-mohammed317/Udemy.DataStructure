#include "CircularQueue.h"
CircularQueue::CircularQueue(int size)
{
	this->size = size + 1;
	arr = new int[size + 1]; // I make one place free always in the queue
	rear = front = 0;
	length = 0;
}
void CircularQueue::Clear()
{
	rear = front = 0;
	length = 0;
}
CircularQueue::~CircularQueue()
{
	delete[] arr;
	arr = nullptr;
}

bool CircularQueue::IsFull()
{
	return (rear + 1) % size == front;
}

bool CircularQueue::IsEmpty()
{
	return front == rear;
}
void CircularQueue::Enqueue(int data)
{
	if (IsFull())
		throw runtime_error("the queue is full");
	rear = (rear + 1) % size;
	arr[rear] = data;
	length++;
}
int CircularQueue::Dequeue()
{
	if (IsEmpty())
		throw runtime_error("the queue is empty");
	front = (front + 1) % size;
	int data = arr[front];
	length--;
	return data;
}
int CircularQueue::Size()
{
	return length;
}
int CircularQueue::First()
{
	if (IsEmpty())
		throw runtime_error("the queue is empty");

	return arr[(front + 1) % size];
}
int CircularQueue::Last()
{
	if (IsEmpty())
		throw runtime_error("the queue is empty");

	return arr[rear];
}
void CircularQueue::Display()
{
	cout << "{";
	if (!IsEmpty())
	{
		int i = (front + 1) % size;
		while (i != rear)
		{
			cout << arr[i] << ", ";
			i = (i + 1) % size;
		}
		cout << arr[rear];
	}
	cout << "}\n";
}
void CircularQueue::TestBehavior()
{
	cout << "===== CircularQueue TestBehavior Start =====\n";

	// Test 1: Initial state
	cout << "\n========== Test 1: Initial State ==========\n";
	{
		CircularQueue q(10);
		cout << "CircularQueue content: ";
		q.Display();

		cout << (q.IsEmpty() ? "[PASS] " : "[FAIL] ") << "CircularQueue should be empty" << endl;
		cout << ((q.Size() == 0) ? "[PASS] " : "[FAIL] ") << "CircularQueue size should be 0" << endl;
	}

	// Test 2: Enqueue one item
	cout << "\n========== Test 2: Enqueue One Item ==========\n";
	{
		CircularQueue q(10);
		q.Enqueue(10);

		cout << "CircularQueue content after Enqueue(10): ";
		q.Display();

		cout << (!q.IsEmpty() ? "[PASS] " : "[FAIL] ") << "CircularQueue should not be empty" << endl;
		cout << ((q.Size() == 1) ? "[PASS] " : "[FAIL] ") << "Size should be 1" << endl;
		cout << ((q.First() == 10) ? "[PASS] " : "[FAIL] ") << "First should be 10" << endl;
		cout << ((q.Last() == 10) ? "[PASS] " : "[FAIL] ") << "Last should be 10" << endl;
	}

	// Test 3: Enqueue multiple items
	cout << "\n========== Test 3: Enqueue Multiple Items ==========\n";
	{
		CircularQueue q(10);
		q.Enqueue(10);
		q.Enqueue(20);
		q.Enqueue(30);

		cout << "CircularQueue content after Enqueue(10), Enqueue(20), Enqueue(30): ";
		q.Display();

		cout << ((q.Size() == 3) ? "[PASS] " : "[FAIL] ") << "Size should be 3" << endl;
		cout << ((q.First() == 10) ? "[PASS] " : "[FAIL] ") << "First should be 10" << endl;
		cout << ((q.Last() == 30) ? "[PASS] " : "[FAIL] ") << "Last should be 30" << endl;
	}

	// Test 4: FIFO behavior
	cout << "\n========== Test 4: FIFO Behavior ==========\n";
	{
		CircularQueue q(10);
		q.Enqueue(10);
		q.Enqueue(20);
		q.Enqueue(30);

		cout << "CircularQueue before dequeues: ";
		q.Display();

		bool passed = true;

		int x1 = q.Dequeue();
		cout << "After first Dequeue() -> removed: " << x1 << ", CircularQueue: ";
		q.Display();
		passed &= (x1 == 10);

		int x2 = q.Dequeue();
		cout << "After second Dequeue() -> removed: " << x2 << ", CircularQueue: ";
		q.Display();
		passed &= (x2 == 20);

		int x3 = q.Dequeue();
		cout << "After third Dequeue() -> removed: " << x3 << ", CircularQueue: ";
		q.Display();
		passed &= (x3 == 30);

		cout << (passed ? "[PASS] " : "[FAIL] ") << "CircularQueue should follow FIFO" << endl;
		cout << (q.IsEmpty() ? "[PASS] " : "[FAIL] ") << "CircularQueue should be empty after all dequeues" << endl;
		cout << ((q.Size() == 0) ? "[PASS] " : "[FAIL] ") << "Size should be 0 after all dequeues" << endl;
	}

	// Test 5: First and Last after dequeue
	cout << "\n========== Test 5: First and Last After Dequeue ==========\n";
	{
		CircularQueue q(10);
		q.Enqueue(5);
		q.Enqueue(10);
		q.Enqueue(15);

		cout << "CircularQueue before Dequeue(): ";
		q.Display();

		q.Dequeue();

		cout << "CircularQueue after one Dequeue(): ";
		q.Display();

		cout << ((q.First() == 10) ? "[PASS] " : "[FAIL] ") << "First should become 10" << endl;
		cout << ((q.Last() == 15) ? "[PASS] " : "[FAIL] ") << "Last should remain 15" << endl;
		cout << ((q.Size() == 2) ? "[PASS] " : "[FAIL] ") << "Size should become 2" << endl;
	}

	// Test 6: Single element case
	cout << "\n========== Test 6: Single Element Case ==========\n";
	{
		CircularQueue q(10);
		q.Enqueue(42);

		cout << "CircularQueue after Enqueue(42): ";
		q.Display();

		int removed = q.Dequeue();

		cout << "CircularQueue after Dequeue(): ";
		q.Display();

		bool passed = (removed == 42) && q.IsEmpty() && q.Size() == 0;
		cout << (passed ? "[PASS] " : "[FAIL] ") << "Single element enqueue/dequeue works correctly" << endl;
	}

	// Test 7: Clear
	cout << "\n========== Test 7: Clear ==========\n";
	{
		CircularQueue q(10);
		q.Enqueue(1);
		q.Enqueue(2);
		q.Enqueue(3);

		cout << "CircularQueue before Clear(): ";
		q.Display();

		q.Clear();

		cout << "CircularQueue after Clear(): ";
		q.Display();

		cout << (q.IsEmpty() ? "[PASS] " : "[FAIL] ") << "CircularQueue should be empty after Clear()" << endl;
		cout << ((q.Size() == 0) ? "[PASS] " : "[FAIL] ") << "Size should be 0 after Clear()" << endl;
	}

	// Test 8: Reuse after clear
	cout << "\n========== Test 8: Reuse After Clear ==========\n";
	{
		CircularQueue q(10);
		q.Enqueue(1);
		q.Enqueue(2);
		q.Clear();
		q.Enqueue(100);

		cout << "CircularQueue after Clear() then Enqueue(100): ";
		q.Display();

		bool passed = (q.First() == 100) && (q.Last() == 100) && (q.Size() == 1);
		cout << (passed ? "[PASS] " : "[FAIL] ") << "CircularQueue can be reused after Clear()" << endl;
	}

	// Test 9: Dequeue on empty
	cout << "\n========== Test 9: Exception - Dequeue on Empty ==========\n";
	{
		CircularQueue q(10);
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
		CircularQueue q(10);
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
		CircularQueue q(10);
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

	// Test 12: Circular Wrap-Around
	cout << "\n========== Test 12: Circular Wrap-Around ==========\n";
	{
		CircularQueue q(3); // Small size to force wrap-around quickly
		q.Enqueue(1);
		q.Enqueue(2);
		q.Enqueue(3);

		cout << "CircularQueue after 3 enqueues (Full): ";
		q.Display();

		q.Dequeue(); // remove 1
		q.Dequeue(); // remove 2

		cout << "CircularQueue after 2 dequeues: ";
		q.Display();

		// This will force the rear pointer to wrap around to the beginning of the array
		q.Enqueue(4);
		q.Enqueue(5);

		cout << "CircularQueue after 2 more enqueues (Wrap-around): ";
		q.Display();

		bool passed = (q.Size() == 3) && (q.First() == 3) && (q.Last() == 5);
		cout << (passed ? "[PASS] " : "[FAIL] ") << "Queue handles circular wrap-around correctly" << endl;
	}

	cout << "\n===== CircularQueue TestBehavior End =====\n";
}