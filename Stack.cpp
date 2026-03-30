#include "Stack.h"

Stack::Stack() {
	this->top = nullptr;
	size = 0;
}
void Stack::Clear()
{
	Node* temp;
	while (top != nullptr)
	{
		temp = top;
		top = top->GetNext();
		delete temp;
	}
	size = 0;
	top = nullptr;
}
Stack::~Stack()
{
	Clear();
}
int Stack::Top()
{
	if (IsEmpty())
	{
		throw std::logic_error("Stack is empty");
	}

	return top->GetData();
}
void Stack::Pop()
{
	if (IsEmpty())
	{
		throw std::logic_error("Stack is empty");
	}

	Node* temp = top;
	top = top->GetNext();
	delete temp;
	size--;
}
int Stack::Size()
{
	return this->size;
}
void Stack::Push(int data)
{
	if (IsFull())
	{
		throw std::logic_error("Stack is full");
	}
	Node* node = new Node(data, top);
	top = node;
	size++;
}
bool Stack::IsFull()
{
	try
	{
		Node* temp = new Node(10);
		delete temp;
		return false;
	}
	catch (const std::bad_alloc&)
	{
		return true;
	}
}
bool Stack::IsEmpty()
{
	return top == nullptr;
}
int Stack::Peek(int pos) // zero-based
{
	if (pos < 0 || pos >= size)
		throw std::out_of_range("index out of range");

	Node* curr = top;

	for (int i = 0; i < pos; i++)
	{
		curr = curr->GetNext();
	}

	return curr->GetData();
}
void Stack::Display()
{
	Node* curr = top;
	std::cout << "{";


	while (curr != nullptr)
	{
		std::cout << curr->GetData();

		curr = curr->GetNext();

		if (curr != nullptr)
			std::cout << ", ";

	}

	std::cout << "}\n";
}

void Stack::TestBehavior()
{
	using std::cout;
	using std::endl;

	Stack s;

	cout << "===== Stack Test Start =====" << endl;

	cout << "\n[1] Initial state" << endl;
	cout << "IsEmpty(): " << (s.IsEmpty() ? "true" : "false") << endl;
	cout << "Size(): " << s.Size() << endl;
	s.Display();

	cout << "\n[2] Top() on empty stack" << endl;
	try
	{
		cout << s.Top() << endl;
	}
	catch (const std::exception& e)
	{
		cout << "Caught exception: " << e.what() << endl;
	}

	cout << "\n[3] Pop() on empty stack" << endl;
	try
	{
		s.Pop();
	}
	catch (const std::exception& e)
	{
		cout << "Caught exception: " << e.what() << endl;
	}

	cout << "\n[4] Push 10, 20, 30, 40" << endl;
	s.Push(10);
	s.Push(20);
	s.Push(30);
	s.Push(40);

	s.Display();
	cout << "Top(): " << s.Top() << endl;
	cout << "Size(): " << s.Size() << endl;
	cout << "IsEmpty(): " << (s.IsEmpty() ? "true" : "false") << endl;

	cout << "\n[5] Peek test" << endl;
	try
	{
		cout << "Peek(0): " << s.Peek(0) << endl;
		cout << "Peek(1): " << s.Peek(1) << endl;
		cout << "Peek(2): " << s.Peek(2) << endl;
		cout << "Peek(3): " << s.Peek(3) << endl;
	}
	catch (const std::exception& e)
	{
		cout << "Caught exception: " << e.what() << endl;
	}

	cout << "\n[6] Peek invalid position" << endl;
	try
	{
		cout << s.Peek(10) << endl;
	}
	catch (const std::exception& e)
	{
		cout << "Caught exception: " << e.what() << endl;
	}

	cout << "\n[7] Pop()" << endl;
	s.Pop();
	s.Display();
	cout << "Top(): " << s.Top() << endl;
	cout << "Size(): " << s.Size() << endl;

	cout << "\n[8] IsFull()" << endl;
	cout << "IsFull(): " << (s.IsFull() ? "true" : "false") << endl;

	cout << "\n[9] Clear()" << endl;
	s.Clear();
	s.Display();
	cout << "IsEmpty(): " << (s.IsEmpty() ? "true" : "false") << endl;
	cout << "Size(): " << s.Size() << endl;

	cout << "\n[10] Top() after Clear()" << endl;
	try
	{
		cout << s.Top() << endl;
	}
	catch (const std::exception& e)
	{
		cout << "Caught exception: " << e.what() << endl;
	}

	cout << "\n===== Stack Test End =====" << endl;
}