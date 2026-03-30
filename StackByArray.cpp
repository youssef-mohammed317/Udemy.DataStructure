#include "StackByArray.h"
StackByArray::StackByArray(int size)
{
	if (size <= 0)
		throw std::logic_error("cant create a stack with size negative");

	arr = new int[size];
	this->size = size;
	top = -1;
	length = 0;
}
StackByArray::~StackByArray()
{
	Clear();
}
void StackByArray::Clear()
{
	delete[] arr;
	arr = nullptr;
	top = -1;
	length = 0;
	size = 0;
}
int StackByArray::Top() {
	if (IsEmpty())
		throw std::logic_error("Stack is empty");

	return arr[top];
}
void StackByArray::Pop()
{
	if (IsEmpty())
		throw std::logic_error("Stack is empty");

	top--;
	length--;
}
int StackByArray::Size()
{
	return size;
}
int StackByArray::Length()
{
	return length;
}
void StackByArray::Push(int data)
{
	if (IsFull())
		throw std::logic_error("Stack is full");

	arr[++top] = data;
	length++;
}
bool StackByArray::IsFull()
{
	return top == size - 1;
}
bool StackByArray::IsEmpty()
{
	return top == -1;
}
void StackByArray::Display()
{
	std::cout << "{";
	for (int i = top; i >= 0; i--)
	{
		std::cout << arr[i];

		if (i > 0)
			std::cout << ", ";
	}
	std::cout << "}\n";
}

int StackByArray::Peek(int pos) // zero-based
{
	int target = top - pos;
	if (pos < 0 || target < 0)
		throw std::out_of_range("index out of range");
	return arr[target];
}

void StackByArray::TestBehavior()
{
    using std::cout;
    using std::endl;

    cout << "===== StackByArray Test Start =====" << endl;

    StackByArray s(5);

    cout << "\n[1] Initial state" << endl;
    cout << "IsEmpty(): " << (s.IsEmpty() ? "true" : "false") << endl;
    cout << "IsFull(): " << (s.IsFull() ? "true" : "false") << endl;
    cout << "Size(): " << s.Size() << endl;
    cout << "Length(): " << s.Length() << endl;
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

    cout << "\n[4] Push 10, 20, 30" << endl;
    s.Push(10);
    s.Push(20);
    s.Push(30);

    s.Display();
    cout << "Top(): " << s.Top() << endl;
    cout << "Size(): " << s.Size() << endl;
    cout << "Length(): " << s.Length() << endl;
    cout << "IsEmpty(): " << (s.IsEmpty() ? "true" : "false") << endl;
    cout << "IsFull(): " << (s.IsFull() ? "true" : "false") << endl;

    cout << "\n[5] Peek test" << endl;
    try
    {
        cout << "Peek(0): " << s.Peek(0) << endl; // 30
        cout << "Peek(1): " << s.Peek(1) << endl; // 20
        cout << "Peek(2): " << s.Peek(2) << endl; // 10
    }
    catch (const std::exception& e)
    {
        cout << "Caught exception: " << e.what() << endl;
    }

    cout << "\n[6] Peek invalid index" << endl;
    try
    {
        cout << s.Peek(5) << endl;
    }
    catch (const std::exception& e)
    {
        cout << "Caught exception: " << e.what() << endl;
    }

    cout << "\n[7] Fill stack" << endl;
    s.Push(40);
    s.Push(50);
    s.Display();
    cout << "Top(): " << s.Top() << endl;
    cout << "Length(): " << s.Length() << endl;
    cout << "IsFull(): " << (s.IsFull() ? "true" : "false") << endl;

    cout << "\n[8] Push() on full stack" << endl;
    try
    {
        s.Push(60);
    }
    catch (const std::exception& e)
    {
        cout << "Caught exception: " << e.what() << endl;
    }

    cout << "\n[9] Pop()" << endl;
    s.Pop();
    s.Display();
    cout << "Top(): " << s.Top() << endl;
    cout << "Length(): " << s.Length() << endl;
    cout << "IsFull(): " << (s.IsFull() ? "true" : "false") << endl;

    cout << "\n[10] Clear()" << endl;
    s.Clear();
    cout << "IsEmpty(): " << (s.IsEmpty() ? "true" : "false") << endl;
    cout << "Size(): " << s.Size() << endl;
    cout << "Length(): " << s.Length() << endl;

    cout << "\n===== StackByArray Test End =====" << endl;
}