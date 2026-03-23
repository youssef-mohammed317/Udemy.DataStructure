#include "LinkedList.h"
Node::Node(int data, Node* next)
{
	this->next = next;
	this->data = data;
}
Node::~Node()
{}
void Node::SetData(int data)
{
	this->data = data;
}
int Node::GetData()
{
	return this->data;
}
Node* Node::GetNext()
{
	return this->next;
}
void Node::SetNext(Node* next)
{
	this->next = next;
}
LinkedList::LinkedList() {
	length = 0;
	head = nullptr;
}
LinkedList::~LinkedList() {
	while (head != nullptr)
	{
		Node* temp = head;
		head = head->GetNext();
		delete temp;
	}
	length = 0;
}
int LinkedList::GetLength()
{
	return length;
}
void LinkedList::Append(int data)
{
	Node* node = new Node(data, nullptr);

	if (head == nullptr)
	{
		head = node;
		length++;
		return;
	}

	Node* temp = head;
	while (temp->GetNext() != nullptr)
	{
		temp = temp->GetNext();
	}
	temp->SetNext(node);
	length++;
}
void LinkedList::Display()
{
	Node* temp = head;
	cout << "\n{";
	while (temp != nullptr)
	{
		cout << temp->GetData();
		temp = temp->GetNext();
		if (temp != nullptr)
			cout << ", ";
	}
	cout << "}\n";
}
void LinkedList::RDisplay()
{
	RDisplay(head);
}

void LinkedList::RDisplay(Node* temp)
{
	if (temp == nullptr)
		return;

	cout << temp->GetData();

	if (temp->GetNext() != nullptr)
		cout << ", ";

	RDisplay(temp->GetNext());
}
int LinkedList::Sum()
{
	int sum = 0;
	Node* temp = head;
	while (temp != nullptr)
	{
		sum += temp->GetData();
		temp = temp->GetNext();
	}
	return sum;
}
int LinkedList::RSum()
{
	return RSum(head);
}
int LinkedList::RSum(Node* temp)
{
	if (temp == nullptr)
		return 0;

	return temp->GetData() + RSum(temp->GetNext());
}
int LinkedList::Max()
{
	if (head == nullptr)
		throw runtime_error("List is empty");

	int max = head->GetData();
	Node* temp = head->GetNext();

	while (temp != nullptr)
	{
		if (temp->GetData() > max)
			max = temp->GetData();

		temp = temp->GetNext();
	}

	return max;
}
int LinkedList::RMax()
{
	if (head == nullptr)
		throw runtime_error("List is empty");

	int currentMax = head->GetData();

	return RMax(head->GetNext(), currentMax);
}

int LinkedList::RMax(Node* temp, int currentMax)
{
	if (temp == nullptr)
		return currentMax;

	if (temp->GetData() > currentMax)
		currentMax = temp->GetData();


	return RMax(temp->GetNext(), currentMax);
}
int LinkedList::R2Max()
{
	if (head == nullptr)
		throw runtime_error("List is empty");

	return R2Max(head);
}

int LinkedList::R2Max(Node* temp)
{
	if (temp == nullptr)
		return INT_MIN;

	int maxInTheRest = R2Max(temp->GetNext());

	if (temp->GetData() > maxInTheRest)
	{
		return temp->GetData();
	}
	else {
		return maxInTheRest;
	}
}
void LinkedList::TestBehavior()
{
	cout << "========== LinkedList TestBehavior ==========\n";

	// =============================
	// 1) Empty list
	// =============================
	{
		LinkedList list;
		cout << "\n1) Empty list\n";
		cout << "Length = " << list.GetLength() << "   expected: 0\n";
		cout << "Sum()  = " << list.Sum() << "   expected: 0\n";
		cout << "RSum() = " << list.RSum() << "   expected: 0\n";

		cout << "Display expected: {}\nActual:   ";
		list.Display();

		cout << "RDisplay expected: {}\nActual:   {";
		list.RDisplay();
		cout << "}\n";

		try
		{
			cout << "Max()  = " << list.Max() << '\n';
		}
		catch (const exception& ex)
		{
			cout << "Max()  throws: " << ex.what() << "   expected: List is empty\n";
		}

		try
		{
			cout << "RMax() = " << list.RMax() << '\n';
		}
		catch (const exception& ex)
		{
			cout << "RMax() throws: " << ex.what() << "   expected: List is empty\n";
		}

		try
		{
			cout << "R2Max() = " << list.R2Max() << '\n';
		}
		catch (const exception& ex)
		{
			cout << "R2Max() throws: " << ex.what() << "   expected: List is empty\n";
		}
	}

	// =============================
	// 2) One node
	// =============================
	{
		LinkedList list;
		list.Append(10);

		cout << "\n---------------------------------------------\n";
		cout << "2) Single node\n";
		cout << "Expected: {10}\nActual:   ";
		list.Display();

		cout << "RDisplay expected: {10}\nActual:   {";
		list.RDisplay();
		cout << "}\n";

		cout << "Length = " << list.GetLength() << "   expected: 1\n";
		cout << "Sum()  = " << list.Sum() << "   expected: 10\n";
		cout << "RSum() = " << list.RSum() << "   expected: 10\n";
		cout << "Max()  = " << list.Max() << "   expected: 10\n";
		cout << "RMax() = " << list.RMax() << "   expected: 10\n";
		cout << "R2Max()= " << list.R2Max() << "   expected: 10\n";
	}

	// =============================
	// 3) Multiple positive values
	// =============================
	{
		LinkedList list;
		list.Append(5);
		list.Append(12);
		list.Append(3);
		list.Append(20);
		list.Append(7);

		cout << "\n---------------------------------------------\n";
		cout << "3) Multiple positive values\n";
		cout << "Expected: {5, 12, 3, 20, 7}\nActual:   ";
		list.Display();

		cout << "RDisplay expected: {5, 12, 3, 20, 7}\nActual:   {";
		list.RDisplay();
		cout << "}\n";

		cout << "Length = " << list.GetLength() << "   expected: 5\n";
		cout << "Sum()  = " << list.Sum() << "   expected: 47\n";
		cout << "RSum() = " << list.RSum() << "   expected: 47\n";
		cout << "Max()  = " << list.Max() << "   expected: 20\n";
		cout << "RMax() = " << list.RMax() << "   expected: 20\n";
		cout << "R2Max()= " << list.R2Max() << "   expected: 20\n";
	}

	// =============================
	// 4) Negative values
	// =============================
	{
		LinkedList list;
		list.Append(-8);
		list.Append(-3);
		list.Append(-15);
		list.Append(-1);
		list.Append(-6);

		cout << "\n---------------------------------------------\n";
		cout << "4) Negative values\n";
		cout << "Expected: {-8, -3, -15, -1, -6}\nActual:   ";
		list.Display();

		cout << "RDisplay expected: {-8, -3, -15, -1, -6}\nActual:   {";
		list.RDisplay();
		cout << "}\n";

		cout << "Length = " << list.GetLength() << "   expected: 5\n";
		cout << "Sum()  = " << list.Sum() << "   expected: -33\n";
		cout << "RSum() = " << list.RSum() << "   expected: -33\n";
		cout << "Max()  = " << list.Max() << "   expected: -1\n";
		cout << "RMax() = " << list.RMax() << "   expected: -1\n";
		cout << "R2Max()= " << list.R2Max() << "   expected: -1\n";
	}

	// =============================
	// 5) Duplicate maximum values
	// =============================
	{
		LinkedList list;
		list.Append(4);
		list.Append(9);
		list.Append(2);
		list.Append(9);
		list.Append(1);

		cout << "\n---------------------------------------------\n";
		cout << "5) Duplicate maximum values\n";
		cout << "Expected: {4, 9, 2, 9, 1}\nActual:   ";
		list.Display();

		cout << "RDisplay expected: {4, 9, 2, 9, 1}\nActual:   {";
		list.RDisplay();
		cout << "}\n";

		cout << "Length = " << list.GetLength() << "   expected: 5\n";
		cout << "Sum()  = " << list.Sum() << "   expected: 25\n";
		cout << "RSum() = " << list.RSum() << "   expected: 25\n";
		cout << "Max()  = " << list.Max() << "   expected: 9\n";
		cout << "RMax() = " << list.RMax() << "   expected: 9\n";
		cout << "R2Max()= " << list.R2Max() << "   expected: 9\n";
	}

	cout << "\n========== End LinkedList TestBehavior ==========\n";
}