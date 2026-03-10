#pragma once
class MyArray
{
private:
	int* arr;
	int size;
	int length;
	void Swap(int& x, int& y);
	void ThrowIfOutOfRange(int index);
	void ThrowIfFull();
	void ThrowIfEmpty();
public:
	MyArray(int size = 10);
	void Display();
	void Append(int value);
	void Insert(int index, int value);
	int Delete(int index); // return value deleted

	int Get(int index);
	void Set(int index, int value);
	int Max(); // return value
	int Min(); // return value
	int Sum();
	int Avg();
	void Reverse();
	void ShiftLeft();
	void ShiftRight();
	void RotateLeft();
	void RotateRight();


	void static TestBehavior();
	~MyArray();

};

