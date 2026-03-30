#include "PriorityQueue.h"
PriorityQueue::PriorityQueue()
{
	size = 0;
}
void PriorityQueue::Clear()
{
	low.Clear();
	high.Clear();
	highest.Clear();
	size = 0;
}
PriorityQueue::~PriorityQueue()
{
	Clear();
}

bool PriorityQueue::IsFull(PeriorityNumber periority)
{
	switch (periority)
	{

	case ALL:
		return low.IsFull() && high.IsFull() && highest.IsFull();
	case LOW:
		return low.IsFull();
	case HIGH:
		return high.IsFull();
	case HIGHEST:
		return highest.IsFull();
	default:
		return low.IsFull() && high.IsFull() && highest.IsFull();
	}
}
bool PriorityQueue::IsEmpty(PeriorityNumber periority)
{
	switch (periority)
	{
	case ALL:
		return low.IsEmpty() && high.IsEmpty() && highest.IsEmpty();
	case LOW:
		return low.IsEmpty();
	case HIGH:
		return high.IsEmpty();
	case HIGHEST:
		return highest.IsEmpty();
	default:
		return low.IsEmpty() && high.IsEmpty() && highest.IsEmpty();
	}
}

void PriorityQueue::Enqueue(int data, PeriorityNumber periority)
{
	if (IsFull(periority))
		throw runtime_error("the queue is full");

	if (periority == LOW)
	{
		low.Enqueue(data);
	}
	else if (periority == HIGH)
	{
		high.Enqueue(data);
	}
	else
	{
		highest.Enqueue(data);
	}

	size++;
}
int PriorityQueue::Dequeue()
{
	if (IsEmpty())
		throw runtime_error("the queue is empty");
	int data;
	if (!IsEmpty(HIGHEST))
	{
		data = highest.Dequeue();
	}
	else if (!IsEmpty(HIGH))
	{
		data = high.Dequeue();
	}
	else
	{
		data = low.Dequeue();
	}
	size--;
	return data;
}
int PriorityQueue::Size()
{
	return size;
}
int PriorityQueue::First()
{
	if (IsEmpty())
		throw runtime_error("the queue is empty");

	if (!IsEmpty(HIGHEST))
	{
		return highest.First();
	}
	if (!IsEmpty(HIGH))
	{
		return high.First();
	}
	return low.First();

}
int PriorityQueue::Last()
{
	if (IsEmpty())
		throw runtime_error("the queue is empty");

	if (!IsEmpty(HIGHEST))
	{
		return highest.Last();
	}
	if (!IsEmpty(HIGH))
	{
		return high.Last();
	}
	return low.Last();
}
void PriorityQueue::Display()
{
	cout << "{\n";
	if (!IsEmpty())
	{
		highest.Display();
		high.Display();
		low.Display();
	}
	cout << "}\n";
}

void PriorityQueue::TestBehavior() {
	cout << "================================================" << endl;
	cout << "     STARTING PRIORITY QUEUE SYSTEM TESTS      " << endl;
	cout << "================================================" << endl;

	// --- TEST 1: Basic Enqueue/Dequeue (FIFO within same priority) ---
	cout << "\n[Test 1] Basic FIFO within same priority: ";
	try {
		PriorityQueue q;
		q.Enqueue(10, LOW);
		q.Enqueue(20, LOW);
		if (q.Dequeue() == 10 && q.Dequeue() == 20) cout << "PASS";
		else cout << "FAIL (Incorrect order)";
	}
	catch (...) { cout << "FAIL (Exception thrown)"; }

	// --- TEST 2: Priority Precedence (The core feature) ---
	cout << "\n[Test 2] Priority Precedence (HIGHEST > HIGH > LOW): ";
	try {
		PriorityQueue q;
		q.Enqueue(1, LOW);      // Added 1st
		q.Enqueue(2, HIGH);     // Added 2nd
		q.Enqueue(3, HIGHEST);  // Added 3rd

		// Should dequeue in order: 3, 2, 1
		bool success = (q.Dequeue() == 3);
		success &= (q.Dequeue() == 2);
		success &= (q.Dequeue() == 1);

		if (success) cout << "PASS";
		else cout << "FAIL (Priority ignored)";
	}
	catch (...) { cout << "FAIL (Exception)"; }

	// --- TEST 3: Mixed Insertion Order ---
	cout << "\n[Test 3] Interleaved Insertion: ";
	try {
		PriorityQueue q;
		q.Enqueue(100, LOW);
		q.Enqueue(10, HIGHEST);
		q.Enqueue(200, LOW);
		q.Enqueue(20, HIGH);

		bool success = (q.Dequeue() == 10);  // Highest
		success &= (q.Dequeue() == 20);      // High
		success &= (q.Dequeue() == 100);     // Low
		success &= (q.Dequeue() == 200);     // Low (FIFO)

		if (success) cout << "PASS";
		else cout << "FAIL";
	}
	catch (...) { cout << "FAIL"; }

	// --- TEST 4: Boundary & Size Checks ---
	cout << "\n[Test 4] Size and Empty state tracking: ";
	PriorityQueue qSize;
	qSize.Enqueue(5, HIGH);
	qSize.Enqueue(10, LOW);
	if (qSize.Size() == 2 && !qSize.IsEmpty()) {
		qSize.Clear();
		if (qSize.Size() == 0 && qSize.IsEmpty()) cout << "PASS";
		else cout << "FAIL (Clear failed)";
	}
	else cout << "FAIL (Size mismatch)";

	// --- TEST 5: Exception Handling ---
	cout << "\n[Test 5] Exception - Dequeue Empty: ";
	try {
		PriorityQueue qEmpty;
		qEmpty.Dequeue();
		cout << "FAIL (No exception)";
	}
	catch (const runtime_error& e) {
		cout << "PASS (" << e.what() << ")";
	}

	// --- TEST 6: First/Last Peek Logic ---
	cout << "\n[Test 6] First/Last Logic: ";
	try {
		PriorityQueue qPeek;
		qPeek.Enqueue(50, LOW);
		qPeek.Enqueue(100, HIGHEST);
		// Even though 50 was added first, 100 is "First" in line to be dequeued
		if (qPeek.First() == 100) cout << "PASS";
		else cout << "FAIL (First() showed " << qPeek.First() << ")";
	}
	catch (...) { cout << "FAIL"; }

	// --- TEST 7: Display Verification ---
	cout << "\n\n[Test 7] Visual Display Test (Should show HIGHEST -> HIGH -> LOW):" << endl;
	PriorityQueue qShow;
	qShow.Enqueue(1, LOW);
	qShow.Enqueue(2, HIGH);
	qShow.Enqueue(3, HIGHEST);
	qShow.Display();

	cout << "\n================================================" << endl;
	cout << "                TESTS COMPLETE                  " << endl;
	cout << "================================================" << endl;
}