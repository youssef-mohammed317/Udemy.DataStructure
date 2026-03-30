#include "DoubleEndedQueue.h"
DoubleEndedQueue::DoubleEndedQueue()
{
	rear = front = nullptr;
	size = 0;
}
void DoubleEndedQueue::Clear()
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
DoubleEndedQueue::~DoubleEndedQueue()
{
	Clear();
}

bool DoubleEndedQueue::IsFull()
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

bool DoubleEndedQueue::IsEmpty()
{
	return front == nullptr;
}

void DoubleEndedQueue::EnqueueFromRear(int data)
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
void DoubleEndedQueue::EnqueueFromFront(int data)
{
	if (IsFull())
		throw runtime_error("the queue is full");

	Node* node = new Node(data);
	if (front == nullptr)
	{
		front = rear = node;
	}
	else {
		node->SetNext(front);
		front = node;
	}
	size++;
}
int DoubleEndedQueue::DequeueFromFront()
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
int DoubleEndedQueue::DequeueFromRear()
{
	if (IsEmpty())
		throw runtime_error("the queue is empty");
	int data = rear->GetData();

	if (front == rear)
	{
		delete rear;
		front = rear = nullptr;
	}
	else {
		Node* temp = front;
		while (temp->GetNext() != rear)
		{
			temp = temp->GetNext();
		}
		delete rear;
		rear = temp;
		rear->SetNext(nullptr);
	}


	size--;
	return data;
}
int DoubleEndedQueue::Size()
{
	return size;
}
int DoubleEndedQueue::First()
{
	if (IsEmpty())
		throw runtime_error("the queue is empty");

	return front->GetData();
}
int DoubleEndedQueue::Last()
{
	if (IsEmpty())
		throw runtime_error("the queue is empty");

	return rear->GetData();
}
void DoubleEndedQueue::Display()
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
void DoubleEndedQueue::TestBehavior()
{
	cout << "================================================" << endl;
	cout << "     DOUBLE-ENDED QUEUE (DEQUE) TEST SUITE      " << endl;
	cout << "================================================" << endl;

	// Test 1: Front vs Rear Insertion
	cout << "\n[Test 1] Mixed Enqueue (Front & Rear): ";
	try {
		DoubleEndedQueue dq;
		dq.EnqueueFromRear(20);  // {20}
		dq.EnqueueFromFront(10); // {10, 20}
		dq.EnqueueFromRear(30);  // {10, 20, 30}

		if (dq.First() == 10 && dq.Last() == 30 && dq.Size() == 3) cout << "PASS";
		else cout << "FAIL";
	}
	catch (...) { cout << "FAIL (Exception)"; }

	// Test 2: Dequeue from Front
	cout << "\n[Test 2] Dequeue from Front: ";
	try {
		DoubleEndedQueue dq;
		dq.EnqueueFromRear(10);
		dq.EnqueueFromRear(20);
		if (dq.DequeueFromFront() == 10 && dq.First() == 20) cout << "PASS";
		else cout << "FAIL";
	}
	catch (...) { cout << "FAIL"; }

	// Test 3: Dequeue from Rear (The most complex part for Singly Linked)
	cout << "\n[Test 3] Dequeue from Rear: ";
	try {
		DoubleEndedQueue dq;
		dq.EnqueueFromRear(10);
		dq.EnqueueFromRear(20);
		dq.EnqueueFromRear(30);   // {10, 20, 30}

		int val = dq.DequeueFromRear(); // Should be 30
		if (val == 30 && dq.Last() == 20 && dq.Size() == 2) cout << "PASS";
		else cout << "FAIL (Check DequeueFromRear logic)";
	}
	catch (...) { cout << "FAIL"; }

	// Test 4: Palindrome/Stack behavior (LIFO via DEQueue)
	cout << "\n[Test 4] Stack-like behavior (Front Only): ";
	try {
		DoubleEndedQueue dq;
		dq.EnqueueFromFront(1);
		dq.EnqueueFromFront(2);
		dq.EnqueueFromFront(3); // {3, 2, 1}

		if (dq.DequeueFromFront() == 3 && dq.DequeueFromFront() == 2) cout << "PASS";
		else cout << "FAIL";
	}
	catch (...) { cout << "FAIL"; }

	// Test 5: Emptying the Queue from Rear
	cout << "\n[Test 5] Emptying via Rear: ";
	try {
		DoubleEndedQueue dq;
		dq.EnqueueFromRear(100);
		dq.DequeueFromRear();
		if (dq.IsEmpty() && dq.Size() == 0) cout << "PASS";
		else cout << "FAIL";
	}
	catch (...) { cout << "FAIL"; }

	// Test 6: Visual Integrity
	cout << "\n\n[Test 6] Visual Display Test (Expected: {5, 10, 15}):" << endl;
	DoubleEndedQueue dqShow;
	dqShow.EnqueueFromRear(10);
	dqShow.EnqueueFromFront(5);
	dqShow.EnqueueFromRear(15);
	dqShow.Display();

	cout << "\n================================================" << endl;
	cout << "                TESTS COMPLETE                  " << endl;
	cout << "================================================" << endl;
}