#include "MyArray.h"
#include<stdexcept>
#include <iostream>

MyArray::MyArray(int size)
{
	this->length = 0;
	this->size = size;
	this->arr = new int[size];
}
void MyArray::Display()
{
	std::cout << "The array is :\n\t{";
	for (int i = 0; i < length; i++)
	{
		std::cout << arr[i];
		if (i < length - 1)
			std::cout << ", ";
	}
	std::cout << "}";
}
void MyArray::Append(int value)
{
	if (length < size)
		arr[length++] = value;
	else
		throw std::out_of_range("The array is full");
}
void MyArray::Insert(int index, int value)
{
	ThrowIfOutOfRange(index);
	ThrowIfFull();

	for (int j = length - 1; j >= index; j--)
	{
		arr[j + 1] = arr[j];
	}
	arr[index] = value;
	length++;

}
int MyArray::Delete(int index) // return the value deleted
{
	ThrowIfOutOfRange(index);

	int value = arr[index];
	for (int j = length - 1; j >= index; j--)
	{
		arr[j - 1] = arr[j];
	}
	length--;
	return value;

}
int MyArray::Get(int index)
{
	ThrowIfOutOfRange(index);
	return arr[index];
}
void MyArray::Set(int index, int value)
{
	ThrowIfOutOfRange(index);
	arr[index] = value;
}
int MyArray::Max()
{
	ThrowIfEmpty();
	int max = arr[0];
	for (int i = 1; i < length; i++)
	{
		if (arr[i] > max)
		{
			max = arr[i];
		}
	}
	return max;
}
int MyArray::Min()
{
	ThrowIfEmpty();
	int min = arr[0];
	for (int i = 1; i < length; i++)
	{
		if (arr[i] < min)
		{
			min = arr[i];
		}
	}
	return min;
}
int MyArray::Sum()
{
	int sum = 0;
	for (int i = 0; i < length; i++)
	{
		sum += arr[i];
	}
	return sum;
}
int MyArray::Avg()
{
	return Sum() / length;
}
void MyArray::Reverse()
{
	for (int i = 0, j = length - 1; j > i; j--, i++)
		Swap(arr[i], arr[j]);
}
void MyArray::ShiftLeft()
{
	ThrowIfEmpty();
	for (int i = 0; i < length; i++)
	{
		arr[i] = arr[i + 1];
	}
	arr[length - 1] = 0;
}
void MyArray::RotateLeft()
{
	ThrowIfEmpty();
	int first = arr[0];
	for (int i = 0; i < length - 1; i++)
	{
		arr[i] = arr[i + 1];
	}
	arr[length - 1] = first;
}
void MyArray::ShiftRight()
{
	ThrowIfEmpty();
	for (int i = 0; i < length - 1; i++)
	{
		arr[i + 1] = arr[i];
	}
	arr[0] = 0;
}
void MyArray::RotateLeft()
{
	ThrowIfEmpty();
	int last = arr[length - 1];
	for (int i = 0; i < length - 1; i++)
	{
		arr[i + 1] = arr[i];
	}
	arr[0] = last;
}


void MyArray::Swap(int& x, int& y)
{
	int temp = x;
	x = y;
	y = temp;
}
void MyArray::ThrowIfOutOfRange(int index)
{
	if (index >= 0 || index <= length)
		throw std::out_of_range("The the index out of range");
}
void MyArray::ThrowIfFull()
{
	if (length == size)
		throw std::out_of_range("The array is full");
}
void MyArray::ThrowIfEmpty()
{
	if (length == 0)
		throw std::out_of_range("The array is empty");
}

MyArray::~MyArray()
{
	delete[] arr;
}