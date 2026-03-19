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
	else if (t == LOWER_TRIANGULAR || t == UPPER_TRIANGULAR || t == SYMMETRIC)
	{
		size = (r * (r + 1)) / 2;
	}
	else if (t == TRIDIAGONAL)
	{
		size = 3 * r - 2;
	}
	else if (t == TOEPLITZ)
	{
		size = 2 * r - 1;
	}
	else if (t == FULL)
	{
		size = r * r;
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
int SquareMatrix::GetTargetRowMajorLowerTriangularIndex(int i, int j)
{
	return ((i * (i - 1)) / 2) + (j - 1);// row major formula
}
int SquareMatrix::GetTargetColMajorUpperTriangularIndex(int i, int j)
{
	return ((j * (j - 1)) / 2) + (i - 1);// col major formula
}
int SquareMatrix::GetTargetTridiagonalIndex(int i, int j)
{
	if (i - j == 1)
	{
		return i - 2;
	}
	else if (i == j)
	{
		return (rows - 1) + (i - 1);
	}
	else if (j - i == 1)
	{
		return (2 * rows - 1) + i - 1;
	}
	return -1;
}
int SquareMatrix::GetTargetColMajorToeplitzIndex(int i, int j)
{

	if (i >= j)
	{
		return i - j;
	}
	else
	{
		return (rows - 1) + (j - i);
	}
}
int SquareMatrix::GetTargetRowMajorFullIndex(int i, int j)
{
	return (i - 1) * rows + (j - 1);
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
			A[GetTargetRowMajorLowerTriangularIndex(i, j)] = value;
		}
	}
	else if (type == UPPER_TRIANGULAR)
	{
		if (i <= j)
		{
			A[GetTargetColMajorUpperTriangularIndex(i, j)] = value;
		}
	}
	else if (type == SYMMETRIC)
	{
		if (i >= j)
		{
			A[GetTargetRowMajorLowerTriangularIndex(i, j)] = value;
		}
		else {
			A[GetTargetRowMajorLowerTriangularIndex(j, i)] = value;
		}
	}
	else if (type == TRIDIAGONAL)
	{
		int targetIndex = GetTargetTridiagonalIndex(i, j);

		if (targetIndex >= 0)
		{
			A[targetIndex] = value;
		}
	}
	else if (type == TOEPLITZ)
	{
		A[GetTargetColMajorToeplitzIndex(i, j)] = value;
	}
	else if (type == FULL)
	{
		A[GetTargetRowMajorFullIndex(i, j)] = value;
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
			return 	A[GetTargetRowMajorLowerTriangularIndex(i, j)];
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

			return A[GetTargetColMajorUpperTriangularIndex(i, j)];
		}
		else
		{
			return 0;
		}
	}
	else if (type == SYMMETRIC)
	{
		if (i >= j)
		{
			return 	A[GetTargetRowMajorLowerTriangularIndex(i, j)];
		}
		else {
			return 	A[GetTargetRowMajorLowerTriangularIndex(j, i)];
		}
	}
	else if (type == TRIDIAGONAL)
	{
		int targetIndex = GetTargetTridiagonalIndex(i, j);

		if (targetIndex >= 0)
		{
			return A[targetIndex];
		}
		else {
			return 0;
		}
	}
	else if (type == TOEPLITZ)
	{
		return A[GetTargetColMajorToeplitzIndex(i, j)];
	}
	else if (type == FULL)
	{
		return A[GetTargetRowMajorFullIndex(i, j)];
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
}

void SquareMatrix::TestBehavior()
{
	try
	{
		cout << "========== DIAGONAL MATRIX TEST ==========\n";
		SquareMatrix d(4, DIAGONAL);

		d.Set(1, 1, 10);
		d.Set(2, 2, 20);
		d.Set(3, 3, 30);
		d.Set(4, 4, 40);
		d.Set(1, 2, 99); // ignored

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
		l.Set(2, 1, 2); l.Set(2, 2, 3);
		l.Set(3, 1, 4); l.Set(3, 2, 5); l.Set(3, 3, 6);
		l.Set(4, 1, 7); l.Set(4, 2, 8); l.Set(4, 3, 9); l.Set(4, 4, 10);
		l.Set(1, 3, 99); // ignored

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

		u.Set(1, 1, 1); u.Set(1, 2, 2); u.Set(1, 3, 3); u.Set(1, 4, 4);
		u.Set(2, 2, 5); u.Set(2, 3, 6); u.Set(2, 4, 7);
		u.Set(3, 3, 8); u.Set(3, 4, 9);
		u.Set(4, 4, 10);
		u.Set(3, 1, 99); // ignored

		cout << "Display upper triangular matrix:\n";
		u.Display();
		cout << endl;

		cout << "Testing Get for upper triangular:\n";
		cout << "u.Get(1,1) = " << u.Get(1, 1) << endl;
		cout << "u.Get(1,2) = " << u.Get(1, 2) << endl;
		cout << "u.Get(1,3) = " << u.Get(1, 3) << endl;
		cout << "u.Get(1,4) = " << u.Get(1, 4) << endl;
		cout << "u.Get(2,2) = " << u.Get(2, 2) << endl;
		cout << "u.Get(2,3) = " << u.Get(2, 3) << endl;
		cout << "u.Get(2,4) = " << u.Get(2, 4) << endl;
		cout << "u.Get(3,3) = " << u.Get(3, 3) << endl;
		cout << "u.Get(3,4) = " << u.Get(3, 4) << endl;
		cout << "u.Get(4,4) = " << u.Get(4, 4) << endl;
		cout << "u.Get(3,1) = " << u.Get(3, 1) << endl;
		cout << "u.Get(4,2) = " << u.Get(4, 2) << endl;


		cout << "\n========== SYMMETRIC MATRIX TEST ==========\n";
		SquareMatrix s(4, SYMMETRIC);

		s.Set(1, 1, 1);
		s.Set(2, 1, 2); s.Set(2, 2, 3);
		s.Set(3, 1, 4); s.Set(3, 2, 5); s.Set(3, 3, 6);
		s.Set(4, 1, 7); s.Set(4, 2, 8); s.Set(4, 3, 9); s.Set(4, 4, 10);
		s.Set(2, 4, 11);

		cout << "Display symmetric matrix:\n";
		s.Display();
		cout << endl;

		cout << "Testing Get for symmetric:\n";
		cout << "s.Get(1,1) = " << s.Get(1, 1) << endl;
		cout << "s.Get(2,1) = " << s.Get(2, 1) << endl;
		cout << "s.Get(1,2) = " << s.Get(1, 2) << endl;
		cout << "s.Get(3,1) = " << s.Get(3, 1) << endl;
		cout << "s.Get(1,3) = " << s.Get(1, 3) << endl;
		cout << "s.Get(3,2) = " << s.Get(3, 2) << endl;
		cout << "s.Get(2,3) = " << s.Get(2, 3) << endl;
		cout << "s.Get(4,1) = " << s.Get(4, 1) << endl;
		cout << "s.Get(1,4) = " << s.Get(1, 4) << endl;
		cout << "s.Get(4,2) = " << s.Get(4, 2) << endl;
		cout << "s.Get(2,4) = " << s.Get(2, 4) << endl;
		cout << "s.Get(4,3) = " << s.Get(4, 3) << endl;
		cout << "s.Get(3,4) = " << s.Get(3, 4) << endl;
		cout << "s.Get(4,4) = " << s.Get(4, 4) << endl;


		cout << "\n========== TRIDIAGONAL MATRIX TEST ==========\n";
		SquareMatrix tri(4, TRIDIAGONAL);

		tri.Set(2, 1, 1);
		tri.Set(3, 2, 2);
		tri.Set(4, 3, 3);

		tri.Set(1, 1, 4);
		tri.Set(2, 2, 5);
		tri.Set(3, 3, 6);
		tri.Set(4, 4, 7);

		tri.Set(1, 2, 8);
		tri.Set(2, 3, 9);
		tri.Set(3, 4, 10);

		tri.Set(1, 3, 99); // ignored
		tri.Set(4, 1, 88); // ignored

		cout << "Display tridiagonal matrix:\n";
		tri.Display();
		cout << endl;

		cout << "Testing Get for tridiagonal:\n";
		cout << "tri.Get(1,1) = " << tri.Get(1, 1) << endl;
		cout << "tri.Get(1,2) = " << tri.Get(1, 2) << endl;
		cout << "tri.Get(1,3) = " << tri.Get(1, 3) << endl;
		cout << "tri.Get(1,4) = " << tri.Get(1, 4) << endl;
		cout << "tri.Get(2,1) = " << tri.Get(2, 1) << endl;
		cout << "tri.Get(2,2) = " << tri.Get(2, 2) << endl;
		cout << "tri.Get(2,3) = " << tri.Get(2, 3) << endl;
		cout << "tri.Get(2,4) = " << tri.Get(2, 4) << endl;
		cout << "tri.Get(3,1) = " << tri.Get(3, 1) << endl;
		cout << "tri.Get(3,2) = " << tri.Get(3, 2) << endl;
		cout << "tri.Get(3,3) = " << tri.Get(3, 3) << endl;
		cout << "tri.Get(3,4) = " << tri.Get(3, 4) << endl;
		cout << "tri.Get(4,1) = " << tri.Get(4, 1) << endl;
		cout << "tri.Get(4,2) = " << tri.Get(4, 2) << endl;
		cout << "tri.Get(4,3) = " << tri.Get(4, 3) << endl;
		cout << "tri.Get(4,4) = " << tri.Get(4, 4) << endl;


		cout << "\n========== TOEPLITZ MATRIX TEST ==========\n";
		SquareMatrix tp(4, TOEPLITZ);

		// first column
		tp.Set(1, 1, 1);
		tp.Set(2, 1, 2);
		tp.Set(3, 1, 3);
		tp.Set(4, 1, 4);

		// first row except first element
		tp.Set(1, 2, 5);
		tp.Set(1, 3, 6);
		tp.Set(1, 4, 7);

		cout << "Display toeplitz matrix:\n";
		tp.Display();
		cout << endl;

		cout << "Testing Get for toeplitz:\n";
		cout << "tp.Get(1,1) = " << tp.Get(1, 1) << endl; // 1
		cout << "tp.Get(1,2) = " << tp.Get(1, 2) << endl; // 5
		cout << "tp.Get(1,3) = " << tp.Get(1, 3) << endl; // 6
		cout << "tp.Get(1,4) = " << tp.Get(1, 4) << endl; // 7
		cout << "tp.Get(2,1) = " << tp.Get(2, 1) << endl; // 2
		cout << "tp.Get(2,2) = " << tp.Get(2, 2) << endl; // 1
		cout << "tp.Get(2,3) = " << tp.Get(2, 3) << endl; // 5
		cout << "tp.Get(2,4) = " << tp.Get(2, 4) << endl; // 6
		cout << "tp.Get(3,1) = " << tp.Get(3, 1) << endl; // 3
		cout << "tp.Get(3,2) = " << tp.Get(3, 2) << endl; // 2
		cout << "tp.Get(3,3) = " << tp.Get(3, 3) << endl; // 1
		cout << "tp.Get(3,4) = " << tp.Get(3, 4) << endl; // 5
		cout << "tp.Get(4,1) = " << tp.Get(4, 1) << endl; // 4
		cout << "tp.Get(4,2) = " << tp.Get(4, 2) << endl; // 3
		cout << "tp.Get(4,3) = " << tp.Get(4, 3) << endl; // 2
		cout << "tp.Get(4,4) = " << tp.Get(4, 4) << endl; // 1


		cout << "\n========== FULL MATRIX TEST ==========\n";
		SquareMatrix f(4, FULL);

		int value = 1;
		for (int i = 1; i <= 4; i++)
		{
			for (int j = 1; j <= 4; j++)
			{
				f.Set(i, j, value++);
			}
		}

		cout << "Display full matrix:\n";
		f.Display();
		cout << endl;

		cout << "Testing Get for full:\n";
		cout << "f.Get(1,1) = " << f.Get(1, 1) << endl; // 1
		cout << "f.Get(1,2) = " << f.Get(1, 2) << endl; // 2
		cout << "f.Get(2,1) = " << f.Get(2, 1) << endl; // 5
		cout << "f.Get(3,3) = " << f.Get(3, 3) << endl; // 11
		cout << "f.Get(4,4) = " << f.Get(4, 4) << endl; // 16


		cout << "\n========== OUT OF RANGE TEST ==========\n";
		try
		{
			cout << d.Get(5, 5) << endl;
		}
		catch (const exception& ex)
		{
			cout << "Expected exception: " << ex.what() << endl;
		}
	}
	catch (const exception& ex)
	{
		cout << "Exception: " << ex.what() << endl;
	}
}