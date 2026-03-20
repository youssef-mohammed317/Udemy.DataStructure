#pragma once

class SparseElement;

class SparseMatrix
{
private:
	int rows;
	int cols;
	int capacity;
	int length;
	SparseElement** elements;
	void ThrowIfFull();
	void ThrowIfIndexOutOfRange(int r, int c);
public:

	SparseMatrix(int rows, int cols, int cap);
	~SparseMatrix();
	int GetRows();
	int GetCols();
	int GetLength();
	int GetCapacity();

	void Set(int row, int col, int value);
	int Get(int row, int col);
	int FindIndex(int row, int col);
	void Display();

	static void TestBehavior();

	SparseMatrix operator+(SparseMatrix& s);

};


class SparseElement
{
private:
	int row;
	int col;
	int value;
public:
	SparseElement(int r, int c, int v);
	int GetRow();
	int GetCol();
	int GetValue();
	void SetValue(int v);
	~SparseElement();
};

