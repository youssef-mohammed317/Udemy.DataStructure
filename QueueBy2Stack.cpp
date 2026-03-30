#include "QueueBy2Stack.h"
QueueBy2Stack::QueueBy2Stack()
{
	size = 0;
}
void QueueBy2Stack::Clear()
{
	while (!s1.empty()) s1.pop();
	while (!s2.empty()) s2.pop();
	size = 0;
}
QueueBy2Stack::~QueueBy2Stack()
{
	Clear();
}

bool QueueBy2Stack::IsFull()
{
	try {
		s1.push(10);
		s1.pop();
		return false;
	}
	catch (const exception& e)
	{
		return true;
	}
}

bool QueueBy2Stack::IsEmpty()
{
	return s1.empty() && s2.empty();
}
void QueueBy2Stack::Enqueue(int data)
{
	if (IsFull())
		throw runtime_error("the queue is full");

	s1.push(data);
	size++;
}
int QueueBy2Stack::Dequeue()
{
	if (IsEmpty())
		throw runtime_error("the queue is empty");

	int data;
	if (!s2.empty())
	{
		data = s2.top();
		s2.pop();
	}
	else
	{
		while (!s1.empty())
		{
			data = s1.top();
			s1.pop();
			s2.push(data);
		}
		s2.pop();
	}
	size--;
	return data;
}
int QueueBy2Stack::Size()
{
	return size;
}
int QueueBy2Stack::First()
{
	if (IsEmpty())
		throw runtime_error("the queue is empty");

	int data = -1;
	if (!s2.empty())
	{
		data = s2.top();
	}
	else
	{
		while (!s1.empty())
		{
			data = s1.top();
			s1.pop();
			s2.push(data);
		}
	}
	return data;
}
int QueueBy2Stack::Last()
{
	if (IsEmpty())
		throw runtime_error("the queue is empty");

	int data = -1;
	if (!s1.empty())
	{
		data = s1.top();
	}
	else
	{
		while (!s2.empty())
		{
			data = s2.top();
			s2.pop();
			s1.push(data);
		}
	}
	return data;
}
void QueueBy2Stack::Display()
{
	cout << "{";

	stack<int> s3, s4;
	int temp;
	while (!s2.empty())
	{
		temp = s2.top();
		cout << temp;
		s2.pop();
		if (!s2.empty())
			cout << ", ";
		s3.push(temp);
	}
	while (!s3.empty())
	{
		temp = s3.top();
		s3.pop();
		s4.push(temp);
	}
	while (!s1.empty())
	{
		temp = s1.top();
		s1.pop();
		s2.push(temp);
	}

	if (!s2.empty())
		cout << ", ";
	while (!s2.empty())
	{
		temp = s2.top();
		cout << temp;
		s2.pop();

		if (!s2.empty())
			cout << ", ";

		s3.push(temp);
	}

	while (!s4.empty())
	{
		temp = s4.top();
		s4.pop();
		s1.push(temp);
	}
	while (!s1.empty())
	{
		temp = s1.top();
		s1.pop();
		s2.push(temp);
	}
	while (!s3.empty())
	{
		temp = s3.top();
		s3.pop();
		s4.push(temp);
	}
	while (!s4.empty())
	{
		temp = s4.top();
		s4.pop();
		s1.push(temp);
	}
	cout << "}\n";
}
void QueueBy2Stack::TestBehavior()
{
	cout << "================================================" << endl;
	cout << "      QUEUE BY 2 STACKS TEST SUITE              " << endl;
	cout << "================================================" << endl;

	// Test 1: Interleaved Enqueue/Dequeue (Core 2-Stack Logic)
	cout << "\n[Test 1] Interleaved Enqueue & Dequeue (s1 & s2 split): ";
	try {
		QueueBy2Stack q;
		q.Enqueue(10);
		q.Enqueue(20);

		bool passed = (q.Dequeue() == 10); // Forces s1 -> s2. s2=[20], s1=[]

		q.Enqueue(30); // s1=[30], s2=[20]
		q.Enqueue(40); // s1=[30, 40], s2=[20]

		passed &= (q.Dequeue() == 20); // Pops directly from s2. s2=[], s1=[30, 40]
		passed &= (q.Dequeue() == 30); // Forces s1 -> s2 again. s2=[40], s1=[]

		if (passed && q.Size() == 1 && q.First() == 40) cout << "PASS";
		else cout << "FAIL";
	}
	catch (...) { cout << "FAIL (Exception)"; }

	// Test 2: First() and Last() Integrity with Mixed Stacks
	cout << "\n[Test 2] First() and Last() with mixed stacks: ";
	try {
		QueueBy2Stack q;
		q.Enqueue(1);
		q.Enqueue(2);
		q.Dequeue();  // Removes 1. s2=[2], s1=[]
		q.Enqueue(3); // s2=[2], s1=[3]

		// At this point, front is 2 (in s2), rear is 3 (in s1)
		bool passed = (q.First() == 2 && q.Last() == 3);

		// Ensure state wasn't ruined by First()/Last() memory shifting
		passed &= (q.Size() == 2);
		passed &= (q.Dequeue() == 2);
		passed &= (q.Dequeue() == 3);

		if (passed) cout << "PASS";
		else cout << "FAIL (Check First/Last state restoration)";
	}
	catch (...) { cout << "FAIL"; }

	// Test 3: Last() when s1 is empty (Forces s2 -> s1 transfer)
	cout << "\n[Test 3] Last() boundary condition (s1 empty): ";
	try {
		QueueBy2Stack q;
		q.Enqueue(100);
		q.Enqueue(200);
		q.Dequeue(); // Removes 100. s2=[200], s1=[]

		// Calling Last() when s1 is empty forces the class to pour s2 into s1
		if (q.Last() == 200 && q.Dequeue() == 200 && q.IsEmpty()) cout << "PASS";
		else cout << "FAIL";
	}
	catch (...) { cout << "FAIL"; }

	// Test 4: Exception Handling
	cout << "\n[Test 4] Exceptions on Empty Queue: ";
	try {
		QueueBy2Stack q;
		q.Dequeue();
		cout << "FAIL (No exception thrown)";
	}
	catch (const runtime_error& e) {
		cout << "PASS";
	}

	// Test 5: Display Integrity Check
	cout << "\n\n[Test 5] Display Integrity Test (Checking if Display corrupts memory):" << endl;
	QueueBy2Stack qDisplay;
	qDisplay.Enqueue(1);
	qDisplay.Enqueue(2);
	qDisplay.Dequeue(); // 1 is removed. s2=[2], s1=[]
	qDisplay.Enqueue(3);
	qDisplay.Enqueue(4); // s2=[2], s1=[3, 4]

	cout << "   Expected output : {2, 3, 4}" << endl;
	cout << "   Actual output   : ";
	qDisplay.Display();
	cout << "   Expected output : {2, 3, 4}" << endl;
	cout << "   Actual output   : ";
	qDisplay.Display();

	cout << "   State post-display : ";
	// If Display() breaks the stacks, these dequeues will return wrong values
	if (qDisplay.Dequeue() == 2 && qDisplay.Dequeue() == 3 && qDisplay.Dequeue() == 4) {
		cout << "[PASS] Display did not break internal stacks." << endl;
	}
	else {
		cout << "[FAIL] Display corrupted the stacks!" << endl;
	}

	cout << "\n================================================" << endl;
	cout << "                TESTS COMPLETE                  " << endl;
	cout << "================================================" << endl;
}