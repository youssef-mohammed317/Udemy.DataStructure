#include "DoublyLinkedList.h"

DoublyLinkedList::DoublyLinkedList()
{
	head = tail = nullptr;
	length = 0;
}
DoublyLinkedList::~DoublyLinkedList()
{
	Clear();
}
void DoublyLinkedList::Clear()
{
	DoublyNode* temp;
	while (head != nullptr)
	{
		temp = head;
		head = head->GetNext();
		delete temp;
	}
	head = tail = nullptr;
	length = 0;
}
int DoublyLinkedList::GetLength()
{
	return length;
}
void DoublyLinkedList::Append(int data)
{
	DoublyNode* node = new DoublyNode(data);
	if (head == nullptr)
	{
		head = tail = node;
	}
	else {
		tail->SetNext(node);
		node->SetPrev(tail);
		tail = node;
	}
	length++;
}

void DoublyLinkedList::Insert(int pos, int data)
{
	if (pos < 0 || pos>length)
	{
		throw out_of_range("index out of range");
	}
	if (pos == length)
	{
		Append(data);
		return;
	}


	DoublyNode* node = new DoublyNode(data);
	if (pos == 0)
	{
		if (head == nullptr)
		{
			head = tail = node;
		}
		else {
			head->SetPrev(node);
			node->SetNext(head);
			head = node;
		}
	}
	else
	{
		DoublyNode* prev = head;
		for (int i = 0; i < pos - 1; i++)
			prev = prev->GetNext();

		DoublyNode* nextNode = prev->GetNext();

		node->SetNext(nextNode);
		node->SetPrev(prev);
		prev->SetNext(node);
		nextNode->SetPrev(node);
	}
	length++;
}
void DoublyLinkedList::Delete(int pos)
{
	if (pos < 0 || pos >= length)
	{
		throw out_of_range("index out of range");
	}

	if (pos == 0)
	{
		DoublyNode* temp = head;
		if (head == tail)
		{
			head = tail = nullptr;
		}
		else {
			head = head->GetNext();
			head->SetPrev(nullptr);
		}
		delete temp;
	}
	else if (pos == length - 1)
	{
		DoublyNode* temp = tail;
		tail = tail->GetPrev();
		tail->SetNext(nullptr);
		delete temp;
	}
	else {

		DoublyNode* target = head;
		for (int i = 0; i < pos; i++)
			target = target->GetNext();

		DoublyNode* prevNode = target->GetPrev();
		DoublyNode* nextNode = target->GetNext();

		prevNode->SetNext(nextNode);
		nextNode->SetPrev(prevNode);

		delete target;
	}
	length--;

}

void DoublyLinkedList::Reverse()
{
	if (head == nullptr)
		return;

	DoublyNode* prevNode = nullptr;
	DoublyNode* midNode = head;
	DoublyNode* nextNode = head->GetNext();

	while (midNode != nullptr)
	{
		midNode->SetNext(prevNode);
		midNode->SetPrev(nextNode);

		prevNode = midNode;
		midNode = nextNode;
		if (nextNode != nullptr)
			nextNode = nextNode->GetNext();

	}

	tail = head;
	head = prevNode;
}

void DoublyLinkedList::ReverseWithTwoPointers()
{
	if (head == nullptr)
		return;

	DoublyNode* curr = head;
	DoublyNode* next = head->GetNext();

	while (curr != nullptr)
	{
		curr->SetNext(curr->GetPrev());
		curr->SetPrev(next);

		curr = next;
		if (next != nullptr)
			next = next->GetNext();
	}

	DoublyNode* temp = head;
	head = tail;
	tail = temp;
}

void DoublyLinkedList::Display()
{
	cout << "{";
	if (head == nullptr)
	{
		cout << "}\n";
		return;
	}
	DoublyNode* curr = head;
	while (curr != nullptr) {
		cout << curr->GetData();
		if (curr != tail) cout << ", ";
		curr = curr->GetNext();
	}
	cout << "}\n";
}
void DoublyLinkedList::DisplayReverse()
{
	cout << "{";

	DoublyNode* curr = tail;
	while (curr != nullptr)
	{
		cout << curr->GetData();
		if (curr != head)
			cout << ", ";

		curr = curr->GetPrev();
	}

	cout << "}\n";
}

int DoublyLinkedList::GetMiddleValue()
{
	DoublyNode* mid = GetMiddleNode();
	if (mid == nullptr)
		throw logic_error("list is empty");

	return mid->GetData();
}
DoublyNode* DoublyLinkedList::GetMiddleNode()
{
	DoublyNode* p, * q;
	p = q = head;

	while (q != nullptr)
	{
		q = q->GetNext();
		if (q != nullptr)
		{
			q = q->GetNext();
			p = p->GetNext();
		}
	}
	return p;
}
DoublyNode* DoublyLinkedList::GetMiddleNodeUsingOnePointerUsingStack()
{
	if (head == nullptr)
		return nullptr;
	DoublyNode* p = head;

	stack<DoublyNode*> s;
	while (p != nullptr)
	{
		s.push(p);
		p = p->GetNext();
	}

	int size = (int)s.size();
	for (int i = 0; i < (size - 1) / 2; i++)
		s.pop();

	return s.top();
}
DoublyNode* DoublyLinkedList::GetIntersectionNodeUsingStack(DoublyLinkedList* other)
{
	if (other == nullptr)
		return nullptr;
	stack<DoublyNode*> sp, sq;

	DoublyNode* p = head;
	DoublyNode* q = other->head;

	while (p != nullptr)
	{
		sp.push(p);
		p = p->GetNext();
	}
	while (q != nullptr)
	{
		sq.push(q);
		q = q->GetNext();
	}
	DoublyNode* lastone = nullptr;
	while (!sp.empty() && !sq.empty() && sp.top() == sq.top())
	{
		lastone = sp.top();
		sq.pop();
		sp.pop();
	}
	return lastone;
}


void DoublyLinkedList::TestBehavior()
{
	cout << "========== DoublyLinkedList TestBehavior ==========\n\n";

	DoublyLinkedList list;

	// 1) Empty list
	cout << "1) Empty list\n";
	cout << "Length expected: 0\n";
	cout << "Actual length:   " << list.GetLength() << "\n";

	cout << "Display expected:        {}\n";
	cout << "Actual:                  ";
	list.Display();

	cout << "DisplayReverse expected: {}\n";
	cout << "Actual:                  ";
	list.DisplayReverse();

	cout << "---------------------------------------------\n";

	// 2) Append
	cout << "2) Append 10, 20, 30\n";
	list.Append(10);
	list.Append(20);
	list.Append(30);

	cout << "Length expected: 3\n";
	cout << "Actual length:   " << list.GetLength() << "\n";

	cout << "Display expected:        {10, 20, 30}\n";
	cout << "Actual:                  ";
	list.Display();

	cout << "DisplayReverse expected: {30, 20, 10}\n";
	cout << "Actual:                  ";
	list.DisplayReverse();

	cout << "---------------------------------------------\n";

	// 3) Insert at beginning
	cout << "3) Insert(0, 5)\n";
	list.Insert(0, 5);

	cout << "Length expected: 4\n";
	cout << "Actual length:   " << list.GetLength() << "\n";

	cout << "Display expected:        {5, 10, 20, 30}\n";
	cout << "Actual:                  ";
	list.Display();

	cout << "DisplayReverse expected: {30, 20, 10, 5}\n";
	cout << "Actual:                  ";
	list.DisplayReverse();

	cout << "---------------------------------------------\n";

	// 4) Insert in middle
	cout << "4) Insert(2, 15)\n";
	list.Insert(2, 15);

	cout << "Length expected: 5\n";
	cout << "Actual length:   " << list.GetLength() << "\n";

	cout << "Display expected:        {5, 10, 15, 20, 30}\n";
	cout << "Actual:                  ";
	list.Display();

	cout << "DisplayReverse expected: {30, 20, 15, 10, 5}\n";
	cout << "Actual:                  ";
	list.DisplayReverse();

	cout << "---------------------------------------------\n";

	// 5) Insert at end
	cout << "5) Insert(length, 40)\n";
	list.Insert(list.GetLength(), 40);

	cout << "Length expected: 6\n";
	cout << "Actual length:   " << list.GetLength() << "\n";

	cout << "Display expected:        {5, 10, 15, 20, 30, 40}\n";
	cout << "Actual:                  ";
	list.Display();

	cout << "DisplayReverse expected: {40, 30, 20, 15, 10, 5}\n";
	cout << "Actual:                  ";
	list.DisplayReverse();

	cout << "---------------------------------------------\n";

	// 6) Delete first
	cout << "6) Delete(0)\n";
	list.Delete(0);

	cout << "Length expected: 5\n";
	cout << "Actual length:   " << list.GetLength() << "\n";

	cout << "Display expected:        {10, 15, 20, 30, 40}\n";
	cout << "Actual:                  ";
	list.Display();

	cout << "DisplayReverse expected: {40, 30, 20, 15, 10}\n";
	cout << "Actual:                  ";
	list.DisplayReverse();

	cout << "---------------------------------------------\n";

	// 7) Delete middle
	cout << "7) Delete(2)\n";
	list.Delete(2);

	cout << "Length expected: 4\n";
	cout << "Actual length:   " << list.GetLength() << "\n";

	cout << "Display expected:        {10, 15, 30, 40}\n";
	cout << "Actual:                  ";
	list.Display();

	cout << "DisplayReverse expected: {40, 30, 15, 10}\n";
	cout << "Actual:                  ";
	list.DisplayReverse();

	cout << "---------------------------------------------\n";

	// 8) Delete last
	cout << "8) Delete(last)\n";
	list.Delete(list.GetLength() - 1);

	cout << "Length expected: 3\n";
	cout << "Actual length:   " << list.GetLength() << "\n";

	cout << "Display expected:        {10, 15, 30}\n";
	cout << "Actual:                  ";
	list.Display();

	cout << "DisplayReverse expected: {30, 15, 10}\n";
	cout << "Actual:                  ";
	list.DisplayReverse();

	cout << "---------------------------------------------\n";

	// 9) Reverse
	cout << "9) Reverse()\n";
	list.Reverse();

	cout << "Length expected: 3\n";
	cout << "Actual length:   " << list.GetLength() << "\n";

	cout << "Display expected:        {30, 15, 10}\n";
	cout << "Actual:                  ";
	list.Display();

	cout << "DisplayReverse expected: {10, 15, 30}\n";
	cout << "Actual:                  ";
	list.DisplayReverse();

	cout << "---------------------------------------------\n";

	// 10) ReverseWithTwoPointers
	cout << "10) ReverseWithTwoPointers()\n";
	list.ReverseWithTwoPointers();

	cout << "Length expected: 3\n";
	cout << "Actual length:   " << list.GetLength() << "\n";

	cout << "Display expected:        {10, 15, 30}\n";
	cout << "Actual:                  ";
	list.Display();

	cout << "DisplayReverse expected: {30, 15, 10}\n";
	cout << "Actual:                  ";
	list.DisplayReverse();

	cout << "---------------------------------------------\n";

	// 11) Clear
	cout << "11) Clear()\n";
	list.Clear();

	cout << "Length expected: 0\n";
	cout << "Actual length:   " << list.GetLength() << "\n";

	cout << "Display expected:        {}\n";
	cout << "Actual:                  ";
	list.Display();

	cout << "DisplayReverse expected: {}\n";
	cout << "Actual:                  ";
	list.DisplayReverse();

	cout << "---------------------------------------------\n";

	// 12) Insert into empty list
	cout << "12) Insert into empty list: Insert(0, 99)\n";
	list.Insert(0, 99);

	cout << "Length expected: 1\n";
	cout << "Actual length:   " << list.GetLength() << "\n";

	cout << "Display expected:        {99}\n";
	cout << "Actual:                  ";
	list.Display();

	cout << "DisplayReverse expected: {99}\n";
	cout << "Actual:                  ";
	list.DisplayReverse();

	cout << "---------------------------------------------\n";

	// 13) Delete only element
	cout << "13) Delete only element: Delete(0)\n";
	list.Delete(0);

	cout << "Length expected: 0\n";
	cout << "Actual length:   " << list.GetLength() << "\n";

	cout << "Display expected:        {}\n";
	cout << "Actual:                  ";
	list.Display();

	cout << "DisplayReverse expected: {}\n";
	cout << "Actual:                  ";
	list.DisplayReverse();

	cout << "---------------------------------------------\n";

	// 14) Reverse empty list
	cout << "14) Reverse() on empty list\n";
	list.Reverse();

	cout << "Length expected: 0\n";
	cout << "Actual length:   " << list.GetLength() << "\n";

	cout << "Display expected:        {}\n";
	cout << "Actual:                  ";
	list.Display();

	cout << "---------------------------------------------\n";

	// 15) ReverseWithTwoPointers empty list
	cout << "15) ReverseWithTwoPointers() on empty list\n";
	list.ReverseWithTwoPointers();

	cout << "Length expected: 0\n";
	cout << "Actual length:   " << list.GetLength() << "\n";

	cout << "Display expected:        {}\n";
	cout << "Actual:                  ";
	list.Display();

	cout << "---------------------------------------------\n";

	// 16) Exception tests
	cout << "16) Exception tests\n";

	try
	{
		list.Delete(0);
		cout << "Delete(0) on empty list: FAILED (no exception)\n";
	}
	catch (const out_of_range& ex)
	{
		cout << "Delete(0) on empty list: PASSED -> " << ex.what() << "\n";
	}

	try
	{
		list.Insert(-1, 100);
		cout << "Insert(-1, 100): FAILED (no exception)\n";
	}
	catch (const out_of_range& ex)
	{
		cout << "Insert(-1, 100): PASSED -> " << ex.what() << "\n";
	}

	try
	{
		list.Insert(2, 100);
		cout << "Insert(2, 100) on empty list: FAILED (no exception)\n";
	}
	catch (const out_of_range& ex)
	{
		cout << "Insert(2, 100) on empty list: PASSED -> " << ex.what() << "\n";
	}

	cout << "---------------------------------------------\n";

	cout << "17) Middle tests\n";

	DoublyLinkedList m1;
	m1.Append(10);
	m1.Append(20);
	m1.Append(30);
	m1.Append(40);
	m1.Append(50);

	cout << "List: ";
	m1.Display();
	cout << "GetMiddleValue expected: 30\n";
	cout << "Actual:                   " << m1.GetMiddleValue() << "\n";
	cout << "GetMiddleNodeUsingOnePointerUsingStack expected: 30\n";
	cout << "Actual:                   "
		<< m1.GetMiddleNodeUsingOnePointerUsingStack()->GetData() << "\n";
	cout << "---------------------------------------------\n";

	DoublyLinkedList m2;
	m2.Append(10);
	m2.Append(20);
	m2.Append(30);
	m2.Append(40);

	cout << "Even-length list: ";
	m2.Display();
	cout << "GetMiddleValue expected: 30\n";
	cout << "Actual:                   " << m2.GetMiddleValue() << "\n";
	cout << "GetMiddleNodeUsingOnePointerUsingStack expected: 30\n";
	cout << "Actual:                   "
		<< m2.GetMiddleNodeUsingOnePointerUsingStack()->GetData() << "\n";
	cout << "---------------------------------------------\n";

	DoublyLinkedList m3;
	m3.Append(99);

	cout << "Single-node list: ";
	m3.Display();
	cout << "GetMiddleValue expected: 99\n";
	cout << "Actual:                   " << m3.GetMiddleValue() << "\n";
	cout << "GetMiddleNodeUsingOnePointerUsingStack expected: 99\n";
	cout << "Actual:                   "
		<< m3.GetMiddleNodeUsingOnePointerUsingStack()->GetData() << "\n";
	cout << "---------------------------------------------\n";

	DoublyLinkedList m4;
	cout << "Empty list middle test\n";
	try
	{
		cout << m4.GetMiddleValue() << "\n";
		cout << "FAILED: no exception\n";
	}
	catch (const logic_error& ex)
	{
		cout << "PASSED -> " << ex.what() << "\n";
	}
	cout << "GetMiddleNode expected: nullptr\n";
	cout << "Actual:                 "
		<< (m4.GetMiddleNode() == nullptr ? "nullptr" : "not nullptr") << "\n";
	cout << "GetMiddleNodeUsingOnePointerUsingStack expected: nullptr\n";
	cout << "Actual:                 "
		<< (m4.GetMiddleNodeUsingOnePointerUsingStack() == nullptr ? "nullptr" : "not nullptr") << "\n";
	cout << "---------------------------------------------\n";
}