#include "CircularLinkedList.h"
CircularLinkedList::CircularLinkedList()
{
	head = tail = nullptr;
	length = 0;
}
CircularLinkedList::~CircularLinkedList()
{
	Clear();
}
void CircularLinkedList::Clear()
{
	if (head == nullptr)
		return;
	Node* temp;
	while (head != tail)
	{
		temp = head;
		head = head->GetNext();
		delete temp;
	}
	delete tail;
	head = tail = nullptr;
	length = 0;
}

void CircularLinkedList::Append(int data)
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
	tail->SetNext(head);
	length++;
}

void CircularLinkedList::Insert(int pos, int data)
{
	if (pos > length || pos < 0)
	{
		throw out_of_range("index is out of range");
	}
	if (pos == length)
	{
		Append(data);
		return;
	}

	Node* node = new Node(data, nullptr);
	if (pos == 0)
	{
		if (head == nullptr)
		{
			tail = head = node;
			node->SetNext(head);
		}
		else {
			node->SetNext(head);
			head = node;
			tail->SetNext(head);
		}
	}
	else {
		Node* temp = head;

		for (int i = 0; i < pos - 1; i++)
		{
			temp = temp->GetNext();
		}
		node->SetNext(temp->GetNext());
		temp->SetNext(node);
	}
	length++;

}
void CircularLinkedList::Delete(int pos)
{
	if (pos >= length || pos < 0)
	{
		throw out_of_range("index is out of range");
	}

	Node* curr = head;
	if (pos == 0)
	{
		if (head == tail)
		{
			delete head;
			head = tail = nullptr;
		}
		else {
			head = head->GetNext();
			tail->SetNext(head);
			delete curr;
		}
	}
	else {
		for (int i = 0; i < pos - 1; i++)
		{
			curr = curr->GetNext();
		}
		Node* temp = curr->GetNext();
		curr->SetNext(temp->GetNext());
		delete temp;
		if (pos == length - 1)
			tail = curr;
	}
	length--;
}

void CircularLinkedList::Display()
{
	cout << "{";

	if (head == nullptr)
	{
		cout << "}\n";
		return;
	}

	Node* curr = head;
	do
	{
		cout << curr->GetData();
		curr = curr->GetNext();

		if (curr != head)
			cout << ", ";

	} while (curr != head);

	cout << "}\n";
}

void CircularLinkedList::TestBehavior()
{
	cout << "========== CircularLinkedList TestBehavior ==========\n\n";

	{
		cout << "1) Empty list\n";
		CircularLinkedList list;
		cout << "Expected: {}\n";
		cout << "Actual:   ";
		list.Display();

		cout << "\nTry Clear() on empty list:\n";
		list.Clear();
		cout << "Expected: {}\n";
		cout << "Actual:   ";
		list.Display();

		cout << "---------------------------------------------\n";
	}

	{
		cout << "2) Append elements\n";
		CircularLinkedList list;
		list.Append(10);
		list.Append(20);
		list.Append(30);

		cout << "Expected: {10, 20, 30}\n";
		cout << "Actual:   ";
		list.Display();

		cout << "---------------------------------------------\n";
	}

	{
		cout << "3) Insert at beginning\n";
		CircularLinkedList list;
		list.Append(20);
		list.Append(30);
		list.Insert(0, 10);

		cout << "Expected: {10, 20, 30}\n";
		cout << "Actual:   ";
		list.Display();

		cout << "---------------------------------------------\n";
	}

	{
		cout << "4) Insert at middle\n";
		CircularLinkedList list;
		list.Append(10);
		list.Append(30);
		list.Insert(1, 20);

		cout << "Expected: {10, 20, 30}\n";
		cout << "Actual:   ";
		list.Display();

		cout << "---------------------------------------------\n";
	}

	{
		cout << "5) Insert at end using Insert(pos == length)\n";
		CircularLinkedList list;
		list.Append(10);
		list.Append(20);
		list.Insert(2, 30);

		cout << "Expected: {10, 20, 30}\n";
		cout << "Actual:   ";
		list.Display();

		cout << "---------------------------------------------\n";
	}

	{
		cout << "6) Insert into empty list at position 0\n";
		CircularLinkedList list;
		list.Insert(0, 99);

		cout << "Expected: {99}\n";
		cout << "Actual:   ";
		list.Display();

		cout << "---------------------------------------------\n";
	}

	{
		cout << "7) Delete first element\n";
		CircularLinkedList list;
		list.Append(10);
		list.Append(20);
		list.Append(30);
		list.Delete(0);

		cout << "Expected: {20, 30}\n";
		cout << "Actual:   ";
		list.Display();

		cout << "---------------------------------------------\n";
	}

	{
		cout << "8) Delete middle element\n";
		CircularLinkedList list;
		list.Append(10);
		list.Append(20);
		list.Append(30);
		list.Delete(1);

		cout << "Expected: {10, 30}\n";
		cout << "Actual:   ";
		list.Display();

		cout << "---------------------------------------------\n";
	}

	{
		cout << "9) Delete last element\n";
		CircularLinkedList list;
		list.Append(10);
		list.Append(20);
		list.Append(30);
		list.Delete(2);

		cout << "Expected: {10, 20}\n";
		cout << "Actual:   ";
		list.Display();

		cout << "---------------------------------------------\n";
	}

	{
		cout << "10) Delete the only element\n";
		CircularLinkedList list;
		list.Append(50);
		list.Delete(0);

		cout << "Expected: {}\n";
		cout << "Actual:   ";
		list.Display();

		cout << "---------------------------------------------\n";
	}

	{
		cout << "11) Delete all elements one by one\n";
		CircularLinkedList list;
		list.Append(10);
		list.Append(20);
		list.Append(30);

		list.Delete(0);
		cout << "After Delete(0), expected: {20, 30}\n";
		cout << "Actual:   ";
		list.Display();

		list.Delete(1);
		cout << "After Delete(1), expected: {20}\n";
		cout << "Actual:   ";
		list.Display();

		list.Delete(0);
		cout << "After Delete(0), expected: {}\n";
		cout << "Actual:   ";
		list.Display();

		cout << "---------------------------------------------\n";
	}

	{
		cout << "12) Clear non-empty list\n";
		CircularLinkedList list;
		list.Append(1);
		list.Append(2);
		list.Append(3);
		list.Append(4);

		cout << "Before Clear(), expected: {1, 2, 3, 4}\n";
		cout << "Actual:   ";
		list.Display();

		list.Clear();

		cout << "After Clear(), expected: {}\n";
		cout << "Actual:   ";
		list.Display();

		cout << "---------------------------------------------\n";
	}

	{
		cout << "13) Exception test: Insert with invalid negative position\n";
		CircularLinkedList list;
		try
		{
			list.Insert(-1, 100);
			cout << "Expected: exception\n";
			cout << "Actual:   no exception\n";
		}
		catch (const out_of_range& ex)
		{
			cout << "Expected: exception\n";
			cout << "Actual:   " << ex.what() << "\n";
		}

		cout << "---------------------------------------------\n";
	}

	{
		cout << "14) Exception test: Insert with position > length\n";
		CircularLinkedList list;
		list.Append(10);

		try
		{
			list.Insert(2, 100);
			cout << "Expected: exception\n";
			cout << "Actual:   no exception\n";
		}
		catch (const out_of_range& ex)
		{
			cout << "Expected: exception\n";
			cout << "Actual:   " << ex.what() << "\n";
		}

		cout << "---------------------------------------------\n";
	}

	{
		cout << "15) Exception test: Delete from empty list\n";
		CircularLinkedList list;

		try
		{
			list.Delete(0);
			cout << "Expected: exception\n";
			cout << "Actual:   no exception\n";
		}
		catch (const out_of_range& ex)
		{
			cout << "Expected: exception\n";
			cout << "Actual:   " << ex.what() << "\n";
		}

		cout << "---------------------------------------------\n";
	}

	{
		cout << "16) Exception test: Delete with invalid position\n";
		CircularLinkedList list;
		list.Append(10);
		list.Append(20);

		try
		{
			list.Delete(2);
			cout << "Expected: exception\n";
			cout << "Actual:   no exception\n";
		}
		catch (const out_of_range& ex)
		{
			cout << "Expected: exception\n";
			cout << "Actual:   " << ex.what() << "\n";
		}

		cout << "---------------------------------------------\n";
	}

	cout << "========== End of CircularLinkedList TestBehavior ==========\n";
}