#include "SparseMatrix.h"
#include <iostream>
#include<stdexcept>
using namespace std;
SparseElement::SparseElement(int r, int c, int val)
{
	row = r;
	col = c;
	value = val;
}
int SparseElement::GetValue()
{
	return value;
}
int SparseElement::GetRow()
{
	return row;
}
int SparseElement::GetCol()
{
	return col;
}
void SparseElement::SetValue(int val)
{
	value = val;
}
SparseElement::~SparseElement()
{}

SparseMatrix::SparseMatrix(int r, int c, int cap)
{
	if (r <= 0 || c <= 0 || cap <= 0)
	{
		throw invalid_argument("Rows, cols, and capacity must be positive");
	}
	rows = r;
	cols = c;
	capacity = cap;
	length = 0;
	elements = new SparseElement * [capacity];
	for (int i = 0; i < capacity; i++)
	{
		elements[i] = nullptr;
	}
}
SparseMatrix::~SparseMatrix()
{
	for (int i = 0; i < length; i++)
	{
		delete elements[i];
	}
	delete[] elements;
}

void SparseMatrix::ThrowIfFull()
{
	if (length == capacity)
	{
		throw out_of_range("The sparse matrix is full");
	}
}

void SparseMatrix::ThrowIfIndexOutOfRange(int r, int c)
{
	if (r < 1 || c < 1 || r > rows || c > cols)
	{
		throw out_of_range("Row or column out of range");
	}
}
int SparseMatrix::FindIndex(int r, int c)
{
	for (int i = 0; i < length; i++)
	{
		if (elements[i] != nullptr &&
			elements[i]->GetRow() == r &&
			elements[i]->GetCol() == c)
		{
			return i;
		}
	}
	return -1;
}
int SparseMatrix::GetCapacity()
{
	return capacity;
}
int SparseMatrix::GetLength()
{
	return length;
}
int SparseMatrix::GetCols()
{
	return cols;
}
int SparseMatrix::GetRows()
{
	return rows;
}

void SparseMatrix::Set(int r, int c, int value)
{
	ThrowIfIndexOutOfRange(r, c);
	int index = FindIndex(r, c);

	if (index != -1)
	{
		if (value == 0)
		{
			delete elements[index];
			for (int i = index; i < length - 1; i++)
			{
				elements[i] = elements[i + 1];
			}
			elements[length - 1] = nullptr;
			length--;
		}
		else {
			elements[index]->SetValue(value);
		}
		return;
	}

	if (value == 0)
		return;

	ThrowIfFull();

	SparseElement* ele = new SparseElement(r, c, value);
	int k = 0;
	int targetIndex = length;
	for (int k = 0; k < length; k++)
	{
		if (elements[k]->GetRow() > r ||
			(elements[k]->GetRow() == r && elements[k]->GetCol() > c))
		{
			targetIndex = k;
			break;
		}
	}
	for (int i = length; i > targetIndex; i--)
	{
		elements[i] = elements[i - 1];
	}

	elements[targetIndex] = ele;
	length++;
}

int SparseMatrix::Get(int r, int c)
{
	ThrowIfIndexOutOfRange(r, c);

	int index = FindIndex(r, c);
	if (index != -1)
	{
		return	elements[index]->GetValue();
	}

	return 0;

}

void SparseMatrix::Display()
{
	for (int i = 1; i <= rows; i++)
	{
		std::cout << "{ ";
		for (int j = 1; j <= cols; j++)
		{
			std::cout << Get(i, j);
			if (j < cols)
			{
				std::cout << ", ";
			}
		}
		std::cout << " }" << endl;
	}
}

void SparseMatrix::TestBehavior()
{
	cout << "========== SparseMatrix TestBehavior ==========\n\n";

	try
	{
		SparseMatrix sm(4, 4, 3);

		cout << "Create matrix 4x4 with capacity 3\n";
		cout << "Rows     = " << sm.GetRows() << endl;
		cout << "Cols     = " << sm.GetCols() << endl;
		cout << "Capacity = " << sm.GetCapacity() << endl;
		cout << "Length   = " << sm.GetLength() << endl;

		cout << "\nInitial matrix:\n";
		sm.Display();

		cout << "\n=============================\n";
		cout << "Test Get from empty matrix\n";
		cout << "Get(1,1) = " << sm.Get(1, 1) << "  expected: 0\n";
		cout << "Get(4,4) = " << sm.Get(4, 4) << "  expected: 0\n";

		cout << "\n=============================\n";
		cout << "Test insert elements\n";
		sm.Set(1, 4, 5);
		sm.Set(3, 1, 7);
		sm.Set(4, 3, 9);

		cout << "Length = " << sm.GetLength() << "  expected: 3\n";
		sm.Display();

		cout << "Get(1,4) = " << sm.Get(1, 4) << "  expected: 5\n";
		cout << "Get(3,1) = " << sm.Get(3, 1) << "  expected: 7\n";
		cout << "Get(4,3) = " << sm.Get(4, 3) << "  expected: 9\n";

		cout << "\n=============================\n";
		cout << "Test update existing element\n";
		sm.Set(3, 1, 20);
		cout << "Get(3,1) = " << sm.Get(3, 1) << "  expected: 20\n";
		cout << "Length = " << sm.GetLength() << "  expected: 3\n";
		sm.Display();

		cout << "\n=============================\n";
		cout << "Test delete element by setting it to 0\n";
		sm.Set(4, 3, 0);
		cout << "Get(4,3) = " << sm.Get(4, 3) << "  expected: 0\n";
		cout << "Length = " << sm.GetLength() << "  expected: 2\n";
		sm.Display();

		cout << "\n=============================\n";
		cout << "Test setting 0 in empty place\n";
		sm.Set(2, 2, 0);
		cout << "Get(2,2) = " << sm.Get(2, 2) << "  expected: 0\n";
		cout << "Length = " << sm.GetLength() << "  expected: 2\n";

		cout << "\n=============================\n";
		cout << "Test insert again after delete\n";
		sm.Set(2, 2, 11);
		cout << "Get(2,2) = " << sm.Get(2, 2) << "  expected: 11\n";
		cout << "Length = " << sm.GetLength() << "  expected: 3\n";
		sm.Display();

		cout << "\n=============================\n";
		cout << "Test full matrix\n";
		try
		{
			sm.Set(4, 4, 99);
			cout << "No exception thrown\n";
		}
		catch (const exception& e)
		{
			cout << "Caught exception: " << e.what() << endl;
		}

		cout << "\n=============================\n";
		cout << "Test out of range\n";
		try
		{
			sm.Get(0, 1);
		}
		catch (const exception& e)
		{
			cout << "Get(0,1) exception: " << e.what() << endl;
		}

		try
		{
			sm.Set(5, 1, 10);
		}
		catch (const exception& e)
		{
			cout << "Set(5,1,10) exception: " << e.what() << endl;
		}

		try
		{
			sm.Get(1, 5);
		}
		catch (const exception& e)
		{
			cout << "Get(1,5) exception: " << e.what() << endl;
		}

		cout << "\nFinal matrix:\n";
		sm.Display();

		cout << "\n========== End of TestBehavior ==========\n";
	}
	catch (const exception& e)
	{
		cout << "Unexpected exception: " << e.what() << endl;
	}
}