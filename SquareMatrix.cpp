#include "SquareMatrix.h"
#include <iostream>
#include<stdexcept>
using namespace std;
SquareMatrix::SquareMatrix(int r, MatrixType t)
{
	rows = r;
	type = t;

	if (t == DIAGONAL)
	{
		size = r;
	}
	else if (t == LOWER_TRIANGULAR || t == UPPER_TRIANGULAR)
	{
		size = (r * (r + 1)) / 2;
	}
	else {
		throw logic_error("Unsupported matrix type");
	}
	A = new int[size] {0};
}
void SquareMatrix::ThrowIfRowOrColOutOfRange(int i, int j)
{
	if (!(i <= rows && i > 0 && j <= rows && j > 0))
		throw std::out_of_range("row or col out of range");
}
int SquareMatrix::GetTargetRowMajorIndex(int i, int j)
{
	return ((i * (i - 1)) / 2) + (j - 1);// row major formula
}
int SquareMatrix::GetTargetColMajorIndex(int i, int j)
{
	return ((j * (j - 1)) / 2) + (i - 1);// col major formula
}
void SquareMatrix::Set(int i, int j, int value)
{
	ThrowIfRowOrColOutOfRange(i, j);

	if (type == DIAGONAL)
	{
		if (i == j)
		{
			A[i - 1] = value;
		}
	}
	else if (type == LOWER_TRIANGULAR)
	{
		if (i >= j)
		{
			A[GetTargetRowMajorIndex(i, j)] = value;
		}
	}
	else if (type == UPPER_TRIANGULAR)
	{
		if (i <= j)
		{
			A[GetTargetColMajorIndex(i, j)] = value;
		}
	}
}
int SquareMatrix::Get(int i, int j)
{
	ThrowIfRowOrColOutOfRange(i, j);

	if (type == DIAGONAL)
	{
		if (i == j)
		{
			return A[i - 1];
		}
		else
		{
			return 0;
		}
	}
	else if (type == LOWER_TRIANGULAR)
	{
		if (i >= j)
		{
			return 	A[GetTargetRowMajorIndex(i, j)];
		}
		else
		{
			return 0;
		}
	}
	else if (type == UPPER_TRIANGULAR)
	{
		if (i <= j)
		{

			return A[GetTargetColMajorIndex(i, j)];
		}
		else
		{
			return 0;
		}
	}

	throw logic_error("Unsupported matrix type");
}
void SquareMatrix::Display()
{
	for (int i = 1; i <= rows; i++)
	{
		cout << "{ ";
		for (int j = 1; j <= rows; j++)
		{
			cout << Get(i, j);
			if (j < rows)
			{
				cout << ", ";
			}
		}
		cout << " }" << endl;
	}
}

SquareMatrix::~SquareMatrix()
{
	delete[] A;
}void SquareMatrix::TestBehavior()
{
	try
	{
		cout << "========== DIAGONAL MATRIX TEST ==========\n";
		SquareMatrix d(4, DIAGONAL);

		d.Set(1, 1, 10);
		d.Set(2, 2, 20);
		d.Set(3, 3, 30);
		d.Set(4, 4, 40);

		// خارج القطر، المفروض لا يتخزن
		d.Set(1, 2, 99);

		cout << "Display diagonal matrix:\n";
		d.Display();
		cout << endl;

		cout << "Testing Get for diagonal:\n";
		cout << "d.Get(1,1) = " << d.Get(1, 1) << endl;
		cout << "d.Get(2,2) = " << d.Get(2, 2) << endl;
		cout << "d.Get(3,3) = " << d.Get(3, 3) << endl;
		cout << "d.Get(4,4) = " << d.Get(4, 4) << endl;
		cout << "d.Get(1,2) = " << d.Get(1, 2) << endl;
		cout << "d.Get(4,1) = " << d.Get(4, 1) << endl;

		cout << "\n========== LOWER TRIANGULAR MATRIX TEST ==========\n";
		SquareMatrix l(4, LOWER_TRIANGULAR);

		l.Set(1, 1, 1);

		l.Set(2, 1, 2);
		l.Set(2, 2, 3);

		l.Set(3, 1, 4);
		l.Set(3, 2, 5);
		l.Set(3, 3, 6);

		l.Set(4, 1, 7);
		l.Set(4, 2, 8);
		l.Set(4, 3, 9);
		l.Set(4, 4, 10);

		// فوق القطر، المفروض لا يتخزن
		l.Set(1, 3, 99);

		cout << "Display lower triangular matrix:\n";
		l.Display();
		cout << endl;

		cout << "Testing Get for lower triangular:\n";
		cout << "l.Get(1,1) = " << l.Get(1, 1) << endl;
		cout << "l.Get(2,1) = " << l.Get(2, 1) << endl;
		cout << "l.Get(2,2) = " << l.Get(2, 2) << endl;
		cout << "l.Get(3,1) = " << l.Get(3, 1) << endl;
		cout << "l.Get(3,2) = " << l.Get(3, 2) << endl;
		cout << "l.Get(3,3) = " << l.Get(3, 3) << endl;
		cout << "l.Get(4,1) = " << l.Get(4, 1) << endl;
		cout << "l.Get(4,2) = " << l.Get(4, 2) << endl;
		cout << "l.Get(4,3) = " << l.Get(4, 3) << endl;
		cout << "l.Get(4,4) = " << l.Get(4, 4) << endl;
		cout << "l.Get(1,3) = " << l.Get(1, 3) << endl;
		cout << "l.Get(2,4) = " << l.Get(2, 4) << endl;

		cout << "\n========== UPPER TRIANGULAR MATRIX TEST ==========\n";
		SquareMatrix u(4, UPPER_TRIANGULAR);

		u.Set(1, 1, 1);
		u.Set(1, 2, 2);
		u.Set(1, 3, 3);
		u.Set(1, 4, 4);

		u.Set(2, 2, 5);
		u.Set(2, 3, 6);
		u.Set(2, 4, 7);

		u.Set(3, 3, 8);
		u.Set(3, 4, 9);

		u.Set(4, 4, 10);

		// تحت القطر، المفروض لا يتخزن
		u.Set(3, 1, 99);

		cout << "Display upper triangular matrix:\n";
		u.Display();
		cout << endl;

		cout << "Testing Get for upper triangular:\n";
		cout << "u.Get(1,1) = " << u.Get(1, 1) << endl; // 1
		cout << "u.Get(1,2) = " << u.Get(1, 2) << endl; // 2
		cout << "u.Get(1,3) = " << u.Get(1, 3) << endl; // 3
		cout << "u.Get(1,4) = " << u.Get(1, 4) << endl; // 4
		cout << "u.Get(2,2) = " << u.Get(2, 2) << endl; // 5
		cout << "u.Get(2,3) = " << u.Get(2, 3) << endl; // 6
		cout << "u.Get(2,4) = " << u.Get(2, 4) << endl; // 7
		cout << "u.Get(3,3) = " << u.Get(3, 3) << endl; // 8
		cout << "u.Get(3,4) = " << u.Get(3, 4) << endl; // 9
		cout << "u.Get(4,4) = " << u.Get(4, 4) << endl; // 10
		cout << "u.Get(3,1) = " << u.Get(3, 1) << endl; // 0
		cout << "u.Get(4,2) = " << u.Get(4, 2) << endl; // 0

		cout << "\n========== OUT OF RANGE TEST ==========\n";
		cout << d.Get(5, 5) << endl; // should throw
	}
	catch (const exception& ex)
	{
		cout << "Exception: " << ex.what() << endl;
	}
}