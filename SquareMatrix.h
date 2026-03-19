#pragma once

enum MatrixType {
	DIAGONAL,
	LOWER_TRIANGULAR,
	UPPER_TRIANGULAR,
	SYMMETRIC,
	TRIDIAGONAL,
	FULL
};

class SquareMatrix
{
private:
	int rows;
	int size;
	int* A;
	MatrixType type;
	void ThrowIfRowOrColOutOfRange(int i, int j);
	int GetTargetRowMajorIndex(int i, int j);
	int GetTargetColMajorIndex(int i, int j);
public:
	SquareMatrix(int r, MatrixType t);

	void Set(int i, int j, int value);
	int Get(int i, int j);
	void Display();
	~SquareMatrix();

	static void TestBehavior();
};

