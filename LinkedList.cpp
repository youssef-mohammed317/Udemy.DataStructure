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
	tail = nullptr;
}
LinkedList::~LinkedList() {
	while (head != nullptr)
	{
		Node* temp = head;
		head = head->GetNext();
		delete temp;
	}
	length = 0;
	head = tail = nullptr;
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
		tail = node; // for insert last
		length++;
		return;
	}

	Node* temp = head;
	while (temp->GetNext() != nullptr)
	{
		temp = temp->GetNext();
	}
	temp->SetNext(node);
	tail = node; // for insert last
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

Node* LinkedList::Search(int key)
{

	Node* temp = head;

	while (temp != nullptr)
	{

		if (temp->GetData() == key)
		{
			return temp;
		}
		temp = temp->GetNext();
	}
	return nullptr;
}

Node* LinkedList::RSearch(int key)
{
	return RSearch(head, key);
}
Node* LinkedList::RSearch(Node* temp, int key)
{
	if (temp == nullptr)
	{
		return nullptr;
	}

	if (temp->GetData() == key)
	{
		return temp;
	}

	return  RSearch(temp->GetNext(), key);
}


Node* LinkedList::SearchAndMoveToFront(int key)
{
	if (head == nullptr)
		return nullptr;

	if (head->GetData() == key)
	{
		return head;
	}

	Node* temp = head->GetNext();
	Node* prev = head;

	while (temp != nullptr)
	{
		if (temp->GetData() == key)
		{
			prev->SetNext(temp->GetNext());

			if (temp == tail)
				tail = prev;

			temp->SetNext(head);
			head = temp;
			return temp;
		}
		prev = temp;
		temp = temp->GetNext();
	}
	return nullptr;
}

Node* LinkedList::RSearchAndMoveToFront(int key)
{
	return RSearchAndMoveToFront(head, nullptr, key);
}
Node* LinkedList::RSearchAndMoveToFront(Node* temp, Node* prev, int key)
{
	if (temp == nullptr)
	{
		return nullptr;
	}

	if (temp->GetData() == key)
	{
		if (prev == nullptr)
			return temp;

		prev->SetNext(temp->GetNext());

		if (temp == tail)
			tail = prev;

		temp->SetNext(head);
		head = temp;
		return temp;
	}

	return  RSearchAndMoveToFront(temp->GetNext(), temp, key);
}
void LinkedList::Insert(int pos, int data) {
	if (pos < 0 || pos > length)
		throw runtime_error("Pos is not valid");

	Node* node = new Node(data, nullptr);

	if (pos == 0)
	{
		if (head == nullptr)
		{
			head = tail = node;
		}
		else {
			node->SetNext(head);
			head = node;
		}
	}
	else if (pos == length)
	{
		InsertLastUsingTail(data);
		return;
	}
	else {

		Node* temp = head;
		for (int i = 0; i < pos - 1; i++)
			temp = temp->GetNext();

		node->SetNext(temp->GetNext());
		temp->SetNext(node);
	}
	length++;
}
void LinkedList::RInsert(int pos, int data) {
	if (pos < 0 || pos > length)
		throw runtime_error("Pos is not valid");

	if (pos == 0)
	{
		if (head == nullptr)
		{
			head = tail = new Node(data, nullptr);
		}
		else {
			head = new Node(data, head);
		}
		length++;
		return;
	}
	else if (pos == length)
	{

		InsertLastUsingTail(data);
		return;
	}

	RInsert(head, 0, pos, data);
}
void LinkedList::RInsert(Node* temp, int index, int pos, int data) {
	if (temp == nullptr)
		return;

	if (index == pos - 1)
	{
		Node* node = new Node(data, temp->GetNext());
		temp->SetNext(node);
		length++;
		return;
	}

	RInsert(temp->GetNext(), index + 1, pos, data);
}

void LinkedList::InsertLastUsingTail(int data)
{
	Node* node = new Node(data, nullptr);

	if (head == nullptr)
	{
		head = tail = node;
	}
	else {
		tail->SetNext(node);
		tail = node;
	}

	length++;
}

void LinkedList::InsertInSortedAsc(int data)
{
	if (head == nullptr)
	{
		head = tail = new Node(data, nullptr);

	}
	else if (data < head->GetData())
	{
		head = new Node(data, head);
	}
	else {
		Node* temp = head->GetNext();
		Node* prev = head;
		Node* node = new Node(data, nullptr);
		while (temp != nullptr && temp->GetData() < data)
		{
			prev = temp;
			temp = temp->GetNext();
		}
		node->SetNext(temp);
		prev->SetNext(node);

		if (temp == nullptr)
		{
			tail = node;
		}
	}
	length++;
}
bool LinkedList::CheckSortedAsc()
{
	if (head == nullptr)
	{
		return true;
	}

	Node* temp = head->GetNext();
	int prevData = head->GetData();

	while (temp != nullptr)
	{
		if (prevData > temp->GetData())
			return false;

		prevData = temp->GetData();
		temp = temp->GetNext();

	}
	return true;
}

void LinkedList::RemoveDuplicatesInSortedAscList()
{
	if (head == nullptr)
		return;

	Node* prev = head;
	Node* curr = head->GetNext();
	Node* temp;

	while (curr != nullptr)
	{
		if (prev->GetData() == curr->GetData())
		{
			temp = curr;
			curr = curr->GetNext();
			prev->SetNext(curr);
			delete temp;
			length--;
		}
		else {
			prev = curr;
			curr = curr->GetNext();
		}
	}
	tail = prev;
}
void LinkedList::Delete(int pos)
{
	if (pos < 0 || pos >= length)
		throw runtime_error("Pos is not valid");

	Node* curr = head;
	Node* prev = nullptr;

	for (int i = 0; i < pos; i++)
	{
		prev = curr;
		curr = curr->GetNext();
	}

	if (prev == nullptr)
	{
		head = head->GetNext();
	}
	else
	{
		prev->SetNext(curr->GetNext());
	}

	if (curr == tail)
	{
		tail = prev;
	}

	delete curr;
	length--;

	if (length == 0)
	{
		head = tail = nullptr;
	}
}

void LinkedList::ReverseLinks()
{
	Node* temp = nullptr;
	Node* prev = nullptr;
	Node* curr = head;
	tail = head;
	while (curr != nullptr)
	{
		temp = curr;
		curr = curr->GetNext();
		temp->SetNext(prev);
		prev = temp;
	}
	head = prev;
}
void LinkedList::ReverseLinksCourseMethod()
{
	Node* prevPrev = nullptr;
	Node* prev = nullptr;
	Node* curr = head;
	tail = head;
	while (curr != nullptr)
	{
		prevPrev = prev;
		prev = curr;
		curr = curr->GetNext();
		prev->SetNext(prevPrev);
	}
	head = prev;
}
void LinkedList::ReverseElements()
{
	if (length <= 1)
		return;
	int* arr = new int[length];
	int i = 0;
	Node* curr = head;
	while (curr != nullptr && i < length)
	{
		arr[i] = curr->GetData();
		curr = curr->GetNext();
		i++;
	}
	curr = head;
	i = length - 1;
	while (curr != nullptr && i >= 0)
	{
		curr->SetData(arr[i]);
		curr = curr->GetNext();
		i--;
	}
	delete[] arr;
}
void LinkedList::RReverseLinks()
{
	tail = head;
	RReverseLinks(nullptr, head);

}
void LinkedList::RReverseLinks(Node* prev, Node* curr)
{
	if (curr == nullptr)
	{
		head = prev;
		return;
	}
	Node* next = curr->GetNext();
	curr->SetNext(prev);

	RReverseLinks(curr, next);
}
void LinkedList::RReverseLinksCourseMethod()
{
	tail = head;
	RReverseLinksCourseMethod(nullptr, head);

}
void LinkedList::RReverseLinks(Node* prev, Node* curr)
{
	if (curr == nullptr)
	{
		head = prev;
		return;
	}
	RReverseLinks(curr, curr->GetNext());
	curr->SetNext(prev);
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

		Node* found1 = list.Search(10);
		cout << "Search(10) = "
			<< (found1 ? to_string(found1->GetData()) : "nullptr")
			<< "   expected: nullptr\n";

		Node* found2 = list.RSearch(10);
		cout << "RSearch(10) = "
			<< (found2 ? to_string(found2->GetData()) : "nullptr")
			<< "   expected: nullptr\n";

		Node* moved1 = list.SearchAndMoveToFront(10);
		cout << "SearchAndMoveToFront(10) = "
			<< (moved1 ? to_string(moved1->GetData()) : "nullptr")
			<< "   expected: nullptr\n";

		Node* moved2 = list.RSearchAndMoveToFront(10);
		cout << "RSearchAndMoveToFront(10) = "
			<< (moved2 ? to_string(moved2->GetData()) : "nullptr")
			<< "   expected: nullptr\n";

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
	// 2) Single node
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

	// =============================
	// 6) Search and RSearch
	// =============================
	{
		LinkedList list;
		list.Append(10);
		list.Append(20);
		list.Append(30);
		list.Append(20);

		cout << "\n---------------------------------------------\n";
		cout << "6) Search and RSearch\n";
		cout << "Expected list: {10, 20, 30, 20}\nActual:   ";
		list.Display();

		Node* found1 = list.Search(20);
		cout << "Search(20) = "
			<< (found1 ? to_string(found1->GetData()) : "nullptr")
			<< "   expected: 20\n";

		Node* found2 = list.RSearch(30);
		cout << "RSearch(30) = "
			<< (found2 ? to_string(found2->GetData()) : "nullptr")
			<< "   expected: 30\n";

		Node* found3 = list.Search(99);
		cout << "Search(99) = "
			<< (found3 ? to_string(found3->GetData()) : "nullptr")
			<< "   expected: nullptr\n";

		Node* found4 = list.RSearch(77);
		cout << "RSearch(77) = "
			<< (found4 ? to_string(found4->GetData()) : "nullptr")
			<< "   expected: nullptr\n";
	}

	// =============================
	// 7) SearchAndMoveToFront
	// =============================
	{
		LinkedList list;
		list.Append(10);
		list.Append(20);
		list.Append(30);
		list.Append(40);

		cout << "\n---------------------------------------------\n";
		cout << "7) SearchAndMoveToFront\n";
		cout << "Original expected: {10, 20, 30, 40}\nActual:   ";
		list.Display();

		Node* moved1 = list.SearchAndMoveToFront(30);
		cout << "After SearchAndMoveToFront(30)\n";
		cout << "Expected: {30, 10, 20, 40}\nActual:   ";
		list.Display();
		cout << "Returned = "
			<< (moved1 ? to_string(moved1->GetData()) : "nullptr")
			<< "   expected: 30\n";

		Node* moved2 = list.SearchAndMoveToFront(99);
		cout << "After SearchAndMoveToFront(99)\n";
		cout << "Expected: {30, 10, 20, 40}\nActual:   ";
		list.Display();
		cout << "Returned = "
			<< (moved2 ? to_string(moved2->GetData()) : "nullptr")
			<< "   expected: nullptr\n";
	}

	// =============================
	// 8) Move last to front + tail validity
	// =============================
	{
		LinkedList list;
		list.Append(10);
		list.Append(20);
		list.Append(30);
		list.Append(40);

		cout << "\n---------------------------------------------\n";
		cout << "8) Move last to front then InsertLastUsingTail\n";
		cout << "Original expected: {10, 20, 30, 40}\nActual:   ";
		list.Display();

		list.SearchAndMoveToFront(40);
		cout << "After SearchAndMoveToFront(40)\n";
		cout << "Expected: {40, 10, 20, 30}\nActual:   ";
		list.Display();

		list.InsertLastUsingTail(50);
		cout << "After InsertLastUsingTail(50)\n";
		cout << "Expected: {40, 10, 20, 30, 50}\nActual:   ";
		list.Display();
		cout << "Length = " << list.GetLength() << "   expected: 5\n";
	}

	// =============================
	// 9) RSearchAndMoveToFront
	// =============================
	{
		LinkedList list;
		list.Append(1);
		list.Append(2);
		list.Append(3);
		list.Append(4);

		cout << "\n---------------------------------------------\n";
		cout << "9) RSearchAndMoveToFront\n";
		cout << "Original expected: {1, 2, 3, 4}\nActual:   ";
		list.Display();

		Node* moved1 = list.RSearchAndMoveToFront(3);
		cout << "After RSearchAndMoveToFront(3)\n";
		cout << "Expected: {3, 1, 2, 4}\nActual:   ";
		list.Display();
		cout << "Returned = "
			<< (moved1 ? to_string(moved1->GetData()) : "nullptr")
			<< "   expected: 3\n";

		Node* moved2 = list.RSearchAndMoveToFront(100);
		cout << "After RSearchAndMoveToFront(100)\n";
		cout << "Expected: {3, 1, 2, 4}\nActual:   ";
		list.Display();
		cout << "Returned = "
			<< (moved2 ? to_string(moved2->GetData()) : "nullptr")
			<< "   expected: nullptr\n";
	}

	// =============================
	// 10) Recursive move last to front + tail validity
	// =============================
	{
		LinkedList list;
		list.Append(11);
		list.Append(22);
		list.Append(33);
		list.Append(44);

		cout << "\n---------------------------------------------\n";
		cout << "10) RSearchAndMoveToFront + InsertLastUsingTail\n";
		cout << "Original expected: {11, 22, 33, 44}\nActual:   ";
		list.Display();

		list.RSearchAndMoveToFront(44);
		cout << "After RSearchAndMoveToFront(44)\n";
		cout << "Expected: {44, 11, 22, 33}\nActual:   ";
		list.Display();

		list.InsertLastUsingTail(55);
		cout << "After InsertLastUsingTail(55)\n";
		cout << "Expected: {44, 11, 22, 33, 55}\nActual:   ";
		list.Display();
		cout << "Length = " << list.GetLength() << "   expected: 5\n";
	}

	// =============================
	// 11) Insert
	// =============================
	{
		LinkedList list;

		cout << "\n---------------------------------------------\n";
		cout << "11) Insert\n";

		list.Insert(0, 10);
		cout << "After Insert(0, 10)\n";
		cout << "Expected: {10}\nActual:   ";
		list.Display();

		list.Insert(0, 5);
		cout << "After Insert(0, 5)\n";
		cout << "Expected: {5, 10}\nActual:   ";
		list.Display();

		list.Insert(2, 20);
		cout << "After Insert(2, 20)\n";
		cout << "Expected: {5, 10, 20}\nActual:   ";
		list.Display();

		list.Insert(2, 15);
		cout << "After Insert(2, 15)\n";
		cout << "Expected: {5, 10, 15, 20}\nActual:   ";
		list.Display();

		cout << "Length = " << list.GetLength() << "   expected: 4\n";

		try
		{
			list.Insert(-1, 99);
			cout << "Insert(-1, 99) did not throw   expected: throw\n";
		}
		catch (const exception& ex)
		{
			cout << "Insert(-1, 99) throws: " << ex.what() << '\n';
		}

		try
		{
			list.Insert(100, 99);
			cout << "Insert(100, 99) did not throw   expected: throw\n";
		}
		catch (const exception& ex)
		{
			cout << "Insert(100, 99) throws: " << ex.what() << '\n';
		}
	}

	// =============================
	// 12) RInsert
	// =============================
	{
		LinkedList list;

		cout << "\n---------------------------------------------\n";
		cout << "12) RInsert\n";

		list.RInsert(0, 10);
		cout << "After RInsert(0, 10)\n";
		cout << "Expected: {10}\nActual:   ";
		list.Display();

		list.RInsert(0, 5);
		cout << "After RInsert(0, 5)\n";
		cout << "Expected: {5, 10}\nActual:   ";
		list.Display();

		list.RInsert(2, 20);
		cout << "After RInsert(2, 20)\n";
		cout << "Expected: {5, 10, 20}\nActual:   ";
		list.Display();

		list.RInsert(2, 15);
		cout << "After RInsert(2, 15)\n";
		cout << "Expected: {5, 10, 15, 20}\nActual:   ";
		list.Display();

		cout << "Length = " << list.GetLength() << "   expected: 4\n";

		try
		{
			list.RInsert(-1, 99);
			cout << "RInsert(-1, 99) did not throw   expected: throw\n";
		}
		catch (const exception& ex)
		{
			cout << "RInsert(-1, 99) throws: " << ex.what() << '\n';
		}

		try
		{
			list.RInsert(100, 99);
			cout << "RInsert(100, 99) did not throw   expected: throw\n";
		}
		catch (const exception& ex)
		{
			cout << "RInsert(100, 99) throws: " << ex.what() << '\n';
		}
	}

	// =============================
	// 13) InsertLastUsingTail
	// =============================
	{
		LinkedList list;

		cout << "\n---------------------------------------------\n";
		cout << "13) InsertLastUsingTail\n";

		list.InsertLastUsingTail(10);
		cout << "After InsertLastUsingTail(10)\n";
		cout << "Expected: {10}\nActual:   ";
		list.Display();

		list.InsertLastUsingTail(20);
		cout << "After InsertLastUsingTail(20)\n";
		cout << "Expected: {10, 20}\nActual:   ";
		list.Display();

		list.InsertLastUsingTail(30);
		cout << "After InsertLastUsingTail(30)\n";
		cout << "Expected: {10, 20, 30}\nActual:   ";
		list.Display();

		cout << "Length = " << list.GetLength() << "   expected: 3\n";
	}

	cout << "\n========== End LinkedList TestBehavior ==========\n";
}