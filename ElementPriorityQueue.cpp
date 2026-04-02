#include "ElementPriorityQueue.h"

ElementPriorityQueue::ElementPriorityQueue() {
	head = tail = nullptr;
	size = 0;
}
void ElementPriorityQueue::Clear() {
	Node* temp;
	while (head != nullptr)
	{
		temp = head;
		head = head->GetNext();
		delete temp;
	}
	head = tail = nullptr;
	size = 0;
}
ElementPriorityQueue::~ElementPriorityQueue()
{
	Clear();
}

void ElementPriorityQueue::Enqueue(int data)
{
	if (IsFull())
		throw logic_error("the queue is full");

	Node* node = new Node(data);
	if (head == nullptr)
	{
		head = tail = node;
	}
	else if (head->GetData() <= data)
	{
		node->SetNext(head);
		head = node;
	}
	else if (tail->GetData() >= data)
	{
		tail->SetNext(node);
		tail = node;
	}
	else
	{

		Node* curr = head->GetNext();
		Node* prev = head;

		while (curr != nullptr)
		{
			if (data >= curr->GetData() && data <= prev->GetData())
			{
				prev->SetNext(node);
				node->SetNext(curr);
				break;
			}
			else {
				prev = curr;
				curr = curr->GetNext();
			}
		}
	}
	size++;
}
int ElementPriorityQueue::Dequeue()
{
	if (IsEmpty())
		throw logic_error("the queue is empty");

	Node* temp = head;
	head = head->GetNext();
	int data = temp->GetData();
	delete temp;
	size--;
	if (head == nullptr)
	{
		head = tail = nullptr;
	}
	return data;
}

bool ElementPriorityQueue::IsFull()
{
	try {
		Node* temp = new Node(10);
		delete temp;
		return false;
	}
	catch (exception& e)
	{
		return true;
	}
}

bool ElementPriorityQueue::IsEmpty()
{
	return head == nullptr;
}

void ElementPriorityQueue::Display()
{
	cout << "{";
	Node* temp = head;
	while (temp != tail)
	{
		cout << temp->GetData() << ", ";
		temp = temp->GetNext();
	}
	if (tail != nullptr)
		cout << tail->GetData();

	cout << "}\n";
}

void ElementPriorityQueue::TestBehavior()
{
	cout << "========== ElementPriorityQueue TestBehavior ==========\n\n";

	ElementPriorityQueue pq;

	// 1) Empty Queue Tests
	cout << "1) Empty Queue Test\n";
	cout << "IsEmpty expected: 1 (true)\n";
	cout << "Actual:           " << pq.IsEmpty() << "\n";

	cout << "Dequeue on empty expected: Exception thrown\n";
	try
	{
		pq.Dequeue();
		cout << "Actual:           FAILED (No exception thrown)\n";
	}
	catch (const logic_error& e)
	{
		cout << "Actual:           PASSED -> " << e.what() << "\n";
	}
	cout << "---------------------------------------------\n";

	// 2) Enqueue Mixed Order
	cout << "2) Enqueue Mixed Order (10, 30, 20, 5, 40)\n";
	pq.Enqueue(10);
	pq.Enqueue(30);
	pq.Enqueue(20);
	pq.Enqueue(5);
	pq.Enqueue(40);

	cout << "Display expected: {40, 30, 20, 10, 5}\n";
	cout << "Actual:           ";
	pq.Display();
	cout << "---------------------------------------------\n";

	// 3) Enqueue Duplicates
	// Note: This tests the bug fix. If the bug was not fixed, 
	// the '5' would not be inserted correctly.
	cout << "3) Enqueue Duplicates (Insert 20 and 5)\n";
	pq.Enqueue(20);
	pq.Enqueue(5);

	cout << "Display expected: {40, 30, 20, 20, 10, 5, 5}\n";
	cout << "Actual:           ";
	pq.Display();
	cout << "---------------------------------------------\n";

	// 4) Dequeue Elements
	cout << "4) Dequeue Top Elements\n";
	cout << "Dequeue expected: 40\n";
	cout << "Actual:           " << pq.Dequeue() << "\n";

	cout << "Dequeue expected: 30\n";
	cout << "Actual:           " << pq.Dequeue() << "\n";

	cout << "Display expected: {20, 20, 10, 5, 5}\n";
	cout << "Actual:           ";
	pq.Display();
	cout << "---------------------------------------------\n";

	// 5) Clear Queue
	cout << "5) Clear Queue\n";
	pq.Clear();

	cout << "IsEmpty expected: 1 (true)\n";
	cout << "Actual:           " << pq.IsEmpty() << "\n";

	cout << "Display expected: {}\n";
	cout << "Actual:           ";
	pq.Display();
	cout << "---------------------------------------------\n";
}