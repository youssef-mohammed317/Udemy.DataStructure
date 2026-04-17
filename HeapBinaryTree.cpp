#include "HeapBinaryTreeByArray.h"

void HeapBinaryTreeByArray::DoubleCapacity()
{
	if (length == capacity - 1)
	{
		capacity *= 2;
		int* newArr = new int[capacity] {0};
		for (int i = 1; i <= length; i++)
		{
			newArr[i] = arr[i];
		};

		delete[]arr;
		arr = newArr;
	}
}
void HeapBinaryTreeByArray::Swap(int& x, int& y)
{
	int temp = x;
	x = y;
	y = temp;
}

HeapBinaryTreeByArray::HeapBinaryTreeByArray(bool maxHeap)
{
	capacity = 8;
	length = 0;
	this->maxHeap = maxHeap;
	arr = new int[capacity] {0};
}
HeapBinaryTreeByArray::~HeapBinaryTreeByArray()
{
	delete[] arr;
}

bool HeapBinaryTreeByArray::IsEmpty()
{
	return length == 0;
}

void HeapBinaryTreeByArray::Clear()
{
	delete[] arr;
	capacity = 8;
	arr = new int[capacity] {0};
	length = 0;
}
void HeapBinaryTreeByArray::Insert(int val)
{
	DoubleCapacity();
	arr[++length] = val;

	int childIndex = length;
	int parentIndex = length / 2; // int take floor value

	if (maxHeap)
	{
		while (parentIndex > 0 && arr[childIndex] > arr[parentIndex])
		{
			Swap(arr[childIndex], arr[parentIndex]);
			childIndex = parentIndex;
			parentIndex = childIndex / 2;
		}
	}
	else
	{
		while (parentIndex > 0 && arr[childIndex] < arr[parentIndex])
		{
			Swap(arr[childIndex], arr[parentIndex]);
			childIndex = parentIndex;
			parentIndex = childIndex / 2;
		}
	}
}
void HeapBinaryTreeByArray::Delete()
{
	if (IsEmpty()) return;

	Swap(arr[1], arr[length]);
	length--;

	int parentIndex = 1;
	int lChildIndex = 2;
	int rChildIndex = 3;

	while (lChildIndex <= length)
	{
		int targetIndex = parentIndex;

		if (maxHeap)
		{
			if (arr[lChildIndex] > arr[targetIndex])
				targetIndex = lChildIndex;

			if (rChildIndex <= length && arr[rChildIndex] > arr[targetIndex])
				targetIndex = rChildIndex;
		}
		else
		{
			if (arr[lChildIndex] < arr[targetIndex])
				targetIndex = lChildIndex;

			if (rChildIndex <= length && arr[rChildIndex] < arr[targetIndex])
				targetIndex = rChildIndex;
		}

		if (targetIndex == parentIndex)
			break;

		Swap(arr[parentIndex], arr[targetIndex]);
		parentIndex = targetIndex;
		lChildIndex = parentIndex * 2;
		rChildIndex = parentIndex * 2 + 1;
	}
}

int HeapBinaryTreeByArray::GetLength()
{
	return length;
}
int* HeapBinaryTreeByArray::Sort()
{
	int* sortedArr = new int[length];

	int oldLength = length;
	while (!IsEmpty())
	{
		Delete();
	}
	// now sorted asc if max and desc if min
	for (int i = 1; i <= oldLength; i++)
	{
		sortedArr[i - 1] = arr[i];
	}
	// re insert old values to the heap
	for (int i = 0; i < oldLength; i++)
	{
		Insert(sortedArr[i]);
	}
	return sortedArr;
}
void HeapBinaryTreeByArray::Display()
{
	int* sortedArr = Sort();
	std::cout << "{";
	for (int i = 0; i < length; i++)
	{
		std::cout << sortedArr[i];
		if (i < length - 1)
			std::cout << ", ";
	}
	std::cout << "}\n";
	delete[] sortedArr;
}

void HeapBinaryTreeByArray::TestBehavior()
{
	std::cout << "========== Testing Max Heap ==========\n";
	HeapBinaryTreeByArray maxH(true);

	// إدخال بيانات عشوائية
	maxH.Insert(50);
	maxH.Insert(30);
	maxH.Insert(80);
	maxH.Insert(20);
	maxH.Insert(90);
	maxH.Insert(10);

	std::cout << "Original Heap values sorted (Ascending for Max Heap):\n";
	maxH.Display(); // Expected: {10, 20, 30, 50, 80, 90}

	maxH.Delete();
	std::cout << "\nAfter Deleting Root (The Max value 90):\n";
	maxH.Display(); // Expected: {10, 20, 30, 50, 80}

	maxH.Clear();
	std::cout << "\nAfter Clear, Is Empty? " << (maxH.IsEmpty() ? "Yes" : "No") << "\n\n";


	std::cout << "========== Testing Min Heap ==========\n";
	HeapBinaryTreeByArray minH(false);

	// إدخال نفس البيانات
	minH.Insert(50);
	minH.Insert(30);
	minH.Insert(80);
	minH.Insert(20);
	minH.Insert(90);
	minH.Insert(10);

	std::cout << "Original Heap values sorted (Descending for Min Heap):\n";
	minH.Display(); // Expected: {90, 80, 50, 30, 20, 10}

	minH.Delete();
	std::cout << "\nAfter Deleting Root (The Min value 10):\n";
	minH.Display(); // Expected: {90, 80, 50, 30, 20}

	std::cout << "======================================\n";
}