#include "MyArray.h"
#include<stdexcept>
#include <iostream>

MyArray::MyArray(int size)
{
	if (size <= 0)
		throw std::invalid_argument("Size must be greater than 0");

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
	std::cout << "}\n";
}
void MyArray::Append(int value)
{
	ThrowIfFull();
	arr[length++] = value;
}
void MyArray::Insert(int index, int value)
{
	ThrowIfFull();
	if (index != length)
		ThrowIfOutOfRange(index);

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
	for (int j = index; j < length - 1; j++)
	{
		arr[j] = arr[j + 1];
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
double MyArray::Avg()
{
	ThrowIfEmpty();
	return  (double)Sum() / length;
}
void MyArray::Reverse()
{
	for (int i = 0, j = length - 1; j > i; j--, i++)
		Swap(arr[i], arr[j]);
}
void MyArray::ShiftLeft()
{
	ThrowIfEmpty();
	for (int i = 0; i < length - 1; i++)
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
	for (int i = length - 1; i > 0; i--)
	{
		arr[i] = arr[i - 1];
	}
	arr[0] = 0;
}
void MyArray::RotateRight()
{
	ThrowIfEmpty();
	int last = arr[length - 1];
	for (int i = length - 1; i > 0; i--)
	{
		arr[i] = arr[i - 1];
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
	if (index < 0 || index >= length)
		throw std::out_of_range("The index is out of range");
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

int MyArray::LinearSearch(int key)
{
	for (int i = 0; i < length; i++)
		if (arr[i] == key)
			return i;
	return -1;
}
int MyArray::ImprovedLinearSearch(int key)
{
	for (int i = 0; i < length; i++)
		if (arr[i] == key)
		{
			if (i > 0)
				Swap(arr[i - 1], arr[i]);
			return (i > 0) ? i - 1 : i;
		}
	return -1;
}
int MyArray::BinarySearchInSortedAsc(int key)
{
	if (IsSortedAsc())
	{
		int low = 0;
		int high = length - 1;

		while (low <= high) {
			int mid = (low + high) / 2;

			if (arr[mid] == key)
				return mid;
			else if (arr[mid] > key)
				high = mid - 1;
			else if (arr[mid] < key)
				low = mid + 1;
		}
	}
	return -1;
}
int MyArray::RBinarySearch(int low, int high, int key)
{
	if (low > high)
		return -1;

	int mid = (low + high) / 2;

	if (arr[mid] == key)
		return mid;
	else if (arr[mid] > key)
		return RBinarySearch(low, mid - 1, key);
	else
		return RBinarySearch(mid + 1, high, key);
}

void MyArray::InsertInSortedAsc(int value)
{
	ThrowIfFull();

	int j = length - 1;
	while (j >= 0 && arr[j] > value)
	{
		arr[j + 1] = arr[j];
		j--;
	}
	arr[j + 1] = value;
	length++;
}
bool MyArray::IsSortedAsc()
{
	for (int i = 0; i < length - 1; i++)
	{
		if (arr[i] > arr[i + 1])
			return false;
	}
	return true;
}

void MyArray::ArrangingNegativesToLeftSide()
{
	int j = length - 1, i = 0;
	while (i < j)
	{

		while (i < j && arr[i] < 0) i++;
		while (i < j && arr[j] >= 0) j--;

		if (i < j)
		{
			Swap(arr[i], arr[j]);
		}
	}
}
void MyArray::MergeWithSortedAscArray(int* arr2, int size2)
{
	int* newArr = new int[this->length + size2];
	int i = 0, j = 0, k = 0;

	while (i < this->length && j < size2)
	{
		if (arr[i] == arr2[j])
		{
			newArr[k++] = arr[i];
			i++; j++;
		}
		else if (arr[i] < arr2[j])
		{
			newArr[k++] = arr[i++];
		}
		else if (arr[i] > arr2[j])
		{
			newArr[k++] = arr2[j++];
		}
	}
	while (i < this->length)
	{
		newArr[k++] = arr[i++];
	}
	while (j < size2)
	{
		newArr[k++] = arr2[j++];
	}

	delete[] arr;
	this->arr = newArr;
	this->size = this->length + size2;
	this->length = k;

}


int* MyArray::UnionTwoSortedAscArraysIntoSortedOne(int* arr1, int size1, int* arr2, int size2)
{
	int* arr = new int[size1 + size2];
	int i = 0, j = 0, k = 0;

	while (i < size1 && j < size2)
	{
		if (arr1[i] == arr2[j])
		{
			arr[k++] = arr1[i];
			i++; j++;
		}
		else if (arr1[i] < arr2[j])
		{
			arr[k++] = arr1[i++];
		}
		else if (arr1[i] > arr2[j])
		{
			arr[k++] = arr2[j++];
		}
	}
	while (i < size1)
	{
		arr[k++] = arr1[i++];
	}
	while (j < size2)
	{
		arr[k++] = arr2[j++];
	}
	return arr;
}
int* MyArray::UnionTwoUnsortedArraysIntoUnSortedOne(int* arr1, int size1, int* arr2, int size2)
{
	int* arr = new int[size1 + size2];
	int i = 0, j = 0, k = 0;

	while (i < size1)
	{
		arr[k++] = arr1[i++];
	}

	while (j < size2)
	{
		bool found = false;
		for (int l = 0; l < k; l++)
		{
			if (arr[l] == arr2[j])
			{
				found = true;
				break;
			}
		}
		if (!found)
		{
			arr[k++] = arr2[j];
		}
		j++;
	}
	return arr;
}
int* MyArray::IntersectionTwoSortedAscArraysIntoSortedOne(int* arr1, int size1, int* arr2, int size2)
{

	int* arr = new int[size1 > size2 ? size1 : size2];
	int i = 0, j = 0, k = 0;
	while (j < size2 && i < size1)
	{
		if (arr1[i] == arr2[j])
		{
			arr[k++] = arr1[i++];
			j++;
		}
		else if (arr1[i] < arr2[j])
		{
			i++;
		}
		else if (arr1[i] > arr2[j]) {
			j++;
		}
	}
	return arr;
}
int* MyArray::IntersectionTwoUnsortedArraysIntoUnSortedOne(int* arr1, int size1, int* arr2, int size2)
{

	int* arr = new int[size1 > size2 ? size1 : size2];
	int  j = 0, k = 0;
	while (j < size2)
	{

		bool found = false;
		for (int l = 0; l < size1; l++)
		{
			if (arr1[l] == arr2[j])
			{
				found = true;
				break;
			}
		}

		bool exist = false;
		for (int l = 0; l < k; l++)
		{
			if (arr[l] == arr2[j])
			{
				exist = true;
				break;
			}
		}

		if (found && !exist)
		{
			arr[k++] = arr2[j];
		}
		j++;
	}

	int* result = new int[k];
	for (int l = 0; l < k; l++)
	{
		result[l] = arr[l];
	}
	delete[] arr;
	return result;
}
int* MyArray::DifferenceTwoUnsortedArraysIntoUnSortedOne(int* arr1, int size1, int* arr2, int size2)
{

	int* arr = new int[size1];
	int i = 0, k = 0;
	while (i < size1)
	{

		bool found = false;
		for (int l = 0; l < size2; l++)
		{
			if (arr1[i] == arr2[l])
			{
				found = true;
				break;
			}
		}
		if (!found)
		{
			arr[k++] = arr1[i];
		}
		i++;
	}
	return arr;
}
int* MyArray::DifferenceTwoSortedAscArraysIntoSortedOne(int* arr1, int size1, int* arr2, int size2)
{

	int* arr = new int[size1];
	int i = 0, j = 0, k = 0;
	while (i < size1 && j < size2)
	{

		if (arr1[i] < arr2[j])
		{
			arr[k++] = arr1[i++];
		}
		else if (arr1[i] > arr2[j])
		{
			j++;
		}
		else if (arr1[i] == arr2[j])
		{
			i++;
			j++;
		}
	}
	while (i < size1)
	{
		arr[k++] = arr1[i++];
	}

	return arr;
}
int MyArray::FindSingleMissingElementInSortedAscArray(int* arr, int size)
{
	int diff = arr[0];
	for (int i = 1; i < size; i++)
	{
		if (arr[i] - i != diff)
		{
			return arr[i] - 1;
		}
	}
	return -1;
}
int MyArray::FindSingleMissingElementInUnsortedArray(int* arr, int size)
{
	int max = arr[0];
	int min = arr[0];
	int sum = arr[0];
	for (int i = 1; i < size; i++)
	{
		if (arr[i] > max)
		{
			max = arr[i];
		}
		else if (arr[i] < min)
		{
			min = arr[i];
		}
		sum += arr[i];
	}

	return (max * (max + 1) / 2) - (min * (min - 1) / 2) - sum;
}
int* MyArray::FindAllMissingElementsInSortedAscArray(int* arr, int size)
{



	int max = arr[size - 1];
	int min = arr[0];
	int range = max - min + 1;

	if (range < 64)
	{
		return FindAllMissingElementsInUnsortedArray(arr, size);
	}

	unsigned long long hash = 0;

	for (int i = 0; i < size; i++)
	{
		hash |= (1ULL << (arr[i] - min));
	}

	int* temp = new int[range];
	int countMissing = 0;

	for (int i = 0; i < range; i++)
	{
		int bit = (hash >> i) & 1ULL;
		if (bit == 0)
			temp[countMissing++] = min + i;
	}

	int* result = new int[countMissing];
	for (int i = 0; i < countMissing; i++)
		result[i] = temp[i];

	delete[] temp;
	return result;
}
int* MyArray::FindAllMissingElementsInUnsortedArray(int* arr, int size)
{
	// use Hash Array
	int max = arr[0];
	int min = arr[0];
	for (int i = 1; i < size; i++)
	{
		if (arr[i] > max)
		{
			max = arr[i];
		}
		else if (arr[i] < min)
		{
			min = arr[i];
		}
	}

	int* hash = new int[max - min + 1] {0};

	for (int i = 0; i < size; i++)
	{
		hash[arr[i] - min] = 1;
	}

	int countMessing = 0;

	for (int i = 0; i < max - min + 1; i++)
	{
		if (hash[i] == 0)
		{
			countMessing++;
		}
	}

	int* result = new int[countMessing];

	for (int i = 0, j = 0; i < max - min + 1; i++)
	{
		if (hash[i] == 0)
		{
			result[j++] = min + i;
		}
	}
	delete[] hash;
	return result;
}
DuplicateElement** MyArray::FindAllDuplicateElementsInUnsortedArrayUsingHash(int* arr, int size)
{
	// use Hash Array
	int max = arr[0]; // if sorted get min and max directly
	int min = arr[0];
	for (int i = 1; i < size; i++)
	{
		if (arr[i] > max)
		{
			max = arr[i];
		}
		else if (arr[i] < min)
		{
			min = arr[i];
		}
	}
	int* hash = new int[max - min + 1] {0};

	for (int i = 0; i < size; i++)
	{
		hash[arr[i] - min]++;
	}

	int countDuplicate = 0;

	for (int i = 0; i < max - min + 1; i++)
	{
		if (hash[i] > 1)
		{
			countDuplicate++;
		}
	}

	DuplicateElement** result = new DuplicateElement * [countDuplicate];

	for (int i = 0, j = 0; i < max - min + 1; i++)
	{
		if (hash[i] > 1)
		{
			result[j++] = new DuplicateElement(min + i, hash[i]);
		}
	}

	delete[] hash;
	return result;
}

DuplicateElement** MyArray::FindAllDuplicateElementsInUnsortedArrayUsingLoops(int* arr, int size)
{
	DuplicateElement** temp = new DuplicateElement * [size] {nullptr};
	int k = 0;

	for (int i = 0; i < size; i++)
	{
		bool alreadyProcessed = false;
		for (int p = 0; p < i; p++)
		{
			if (arr[p] == arr[i])
			{
				alreadyProcessed = true;
				break;
			}
		}
		if (alreadyProcessed) continue;

		int count = 1;
		for (int j = i + 1; j < size; j++)
		{
			if (arr[i] == arr[j])
			{
				count++;
			}
		}
		if (count > 1)
		{
			temp[k++] = new DuplicateElement(arr[i], count);
		}
	}

	DuplicateElement** result = new DuplicateElement * [k];
	for (int i = 0; i < k; i++)
	{
		result[i] = temp[i];
	}
	delete[] temp;
	return result;
}
PairOfElements** MyArray::FindAllPairsOfElementsWithSumUsingLoops(int* arr, int size, int sum)
{
	PairOfElements** temp = new PairOfElements * [size] {nullptr};
	int k = 0;

	for (int i = 0; i < size; i++)
	{
		for (int j = i + 1; j < size; j++)
		{
			if (arr[j] + arr[i] == sum)
			{
				temp[k++] = new PairOfElements(arr[i], arr[j]);
			}
		}
	}

	PairOfElements** result = new PairOfElements * [k];
	for (int i = 0; i < k; i++)
	{
		result[i] = temp[i];
	}
	delete[] temp;
	return result;
}

PairOfElements** MyArray::FindAllPairsOfElementsWithSumUsingHash(int* arr, int size, int sum)
{
	// use Hash Array

	int max = arr[0];
	int min = arr[0];
	for (int i = 1; i < size; i++)
	{
		if (arr[i] > max)
		{
			max = arr[i];
		}
		else if (arr[i] < min)
		{
			min = arr[i];
		}
	}
	PairOfElements** temp = new PairOfElements * [size] {nullptr};
	int* hash = new int[max - min + 1] {0};

	for (int i = 0; i < size; i++)
	{
		hash[arr[i] - min]++;
	}

	int countPair = 0;

	for (int i = 0; i < max - min + 1; i++)
	{
		int first = min + i;
		int sec = sum - first;
		int secIndexInHash = sec - min;
		if (secIndexInHash < 0 || secIndexInHash >= max - min + 1)
			continue;
		if (i == secIndexInHash && hash[i] > 1)
		{
			temp[countPair++] = new PairOfElements(first, first);

		}
		else if (hash[secIndexInHash] > 0 && hash[i] > 0 && i < secIndexInHash)
		{
			temp[countPair++] = new PairOfElements(min + i, min + secIndexInHash);
		}
	}

	PairOfElements** result = new PairOfElements * [countPair];
	for (int i = 0; i < countPair; i++)
	{
		result[i] = temp[i];
	}
	delete[] temp;
	delete[] hash;
	return result;
}


MyArray::~MyArray()
{
	delete[] arr;
}

void MyArray::TestBehavior()
{
	try
	{
		auto PrintIntArray = [](const char* title, int* a, int count)
			{
				std::cout << title << " { ";
				for (int i = 0; i < count; i++)
				{
					std::cout << a[i];
					if (i < count - 1) std::cout << ", ";
				}
				std::cout << " }\n";
			};

		std::cout << "\n================ BASIC OPERATIONS ================\n";
		MyArray arr(10);

		arr.Append(10);
		arr.Append(20);
		arr.Append(30);
		arr.Append(40);
		arr.Append(50);
		arr.Display();

		std::cout << "\nInsert 25 at index 2:\n";
		arr.Insert(2, 25);
		arr.Display();

		std::cout << "\nInsert 60 at index = length:\n";
		arr.Insert(6, 60);
		arr.Display();

		std::cout << "\nDelete element at index 3:\n";
		int deleted = arr.Delete(3);
		std::cout << "Deleted value: " << deleted << "\n";
		arr.Display();

		std::cout << "\nGet index 2 = " << arr.Get(2) << "\n";

		std::cout << "\nSet index 1 = 99\n";
		arr.Set(1, 99);
		arr.Display();

		std::cout << "\nMax = " << arr.Max() << "\n";
		std::cout << "Min = " << arr.Min() << "\n";
		std::cout << "Sum = " << arr.Sum() << "\n";
		std::cout << "Avg = " << arr.Avg() << "\n";

		std::cout << "\nReverse:\n";
		arr.Reverse();
		arr.Display();

		std::cout << "\nShiftLeft:\n";
		arr.ShiftLeft();
		arr.Display();

		std::cout << "\nRotateLeft:\n";
		arr.RotateLeft();
		arr.Display();

		std::cout << "\nRotateRight:\n";
		arr.RotateRight();
		arr.Display();

		std::cout << "\nShiftRight:\n";
		arr.ShiftRight();
		arr.Display();


		std::cout << "\n================ SEARCH ==================\n";
		MyArray searchArr(10);
		searchArr.Append(5);
		searchArr.Append(10);
		searchArr.Append(15);
		searchArr.Append(20);
		searchArr.Append(25);

		searchArr.Display();
		std::cout << "LinearSearch(15) = " << searchArr.LinearSearch(15) << "\n";
		std::cout << "LinearSearch(100) = " << searchArr.LinearSearch(100) << "\n";

		std::cout << "BinarySearchInSortedAsc(25) = " << searchArr.BinarySearchInSortedAsc(25) << "\n";
		std::cout << "BinarySearchInSortedAsc(100) = " << searchArr.BinarySearchInSortedAsc(100) << "\n";
		std::cout << "RBinarySearch(0, 4, 10) = " << searchArr.RBinarySearch(0, 4, 10) << "\n";
		std::cout << "RBinarySearch(0, 4, 99) = " << searchArr.RBinarySearch(0, 4, 99) << "\n";

		std::cout << "ImprovedLinearSearch(20) = " << searchArr.ImprovedLinearSearch(20) << "\n";
		searchArr.Display();


		std::cout << "\n================ SORTED OPERATIONS ==================\n";
		MyArray sortedArr(10);
		sortedArr.Append(10);
		sortedArr.Append(20);
		sortedArr.Append(30);
		sortedArr.Append(40);

		sortedArr.Display();
		std::cout << "IsSortedAsc = " << sortedArr.IsSortedAsc() << "\n";

		std::cout << "\nInsertInSortedAsc(25):\n";
		sortedArr.InsertInSortedAsc(25);
		sortedArr.Display();

		std::cout << "\nInsertInSortedAsc(5):\n";
		sortedArr.InsertInSortedAsc(5);
		sortedArr.Display();

		std::cout << "\nInsertInSortedAsc(50):\n";
		sortedArr.InsertInSortedAsc(50);
		sortedArr.Display();

		MyArray notSorted(10);
		notSorted.Append(30);
		notSorted.Append(10);
		notSorted.Append(20);
		notSorted.Display();
		std::cout << "IsSortedAsc (not sorted) = " << notSorted.IsSortedAsc() << "\n";
		std::cout << "BinarySearchInSortedAsc(20) on not sorted array = "
			<< notSorted.BinarySearchInSortedAsc(20) << "\n";


		std::cout << "\n================ NEGATIVE ARRANGEMENT ==================\n";
		MyArray negArr(10);
		negArr.Append(2);
		negArr.Append(-5);
		negArr.Append(7);
		negArr.Append(-10);
		negArr.Append(4);
		negArr.Append(-1);
		negArr.Display();

		negArr.ArrangingNegativesToLeftSide();
		std::cout << "After arranging negatives to left:\n";
		negArr.Display();


		std::cout << "\n================ MERGE / UNION / INTERSECTION / DIFFERENCE ==================\n";

		int a1[] = { 1, 3, 5, 7, 9 };
		int a2[] = { 2, 3, 6, 7, 10 };

		int* unionSorted = MyArray::UnionTwoSortedAscArraysIntoSortedOne(a1, 5, a2, 5);
		PrintIntArray("UnionTwoSortedAscArraysIntoSortedOne =", unionSorted, 8);

		int* interSorted = MyArray::IntersectionTwoSortedAscArraysIntoSortedOne(a1, 5, a2, 5);
		PrintIntArray("IntersectionTwoSortedAscArraysIntoSortedOne =", interSorted, 2);

		int* diffSorted = MyArray::DifferenceTwoSortedAscArraysIntoSortedOne(a1, 5, a2, 5);
		PrintIntArray("DifferenceTwoSortedAscArraysIntoSortedOne =", diffSorted, 3);

		int u1[] = { 5, 1, 7, 3 };
		int u2[] = { 3, 8, 1, 9 };

		int* unionUnsorted = MyArray::UnionTwoUnsortedArraysIntoUnSortedOne(u1, 4, u2, 4);
		PrintIntArray("UnionTwoUnsortedArraysIntoUnSortedOne =", unionUnsorted, 6);

		int* interUnsorted = MyArray::IntersectionTwoUnsortedArraysIntoUnSortedOne(u1, 4, u2, 4);
		PrintIntArray("IntersectionTwoUnsortedArraysIntoUnSortedOne =", interUnsorted, 2);

		int* diffUnsorted = MyArray::DifferenceTwoUnsortedArraysIntoUnSortedOne(u1, 4, u2, 4);
		PrintIntArray("DifferenceTwoUnsortedArraysIntoUnSortedOne =", diffUnsorted, 2);

		delete[] unionSorted;
		delete[] interSorted;
		delete[] diffSorted;
		delete[] unionUnsorted;
		delete[] interUnsorted;
		delete[] diffUnsorted;


		std::cout << "\n================ MERGE INTO CURRENT OBJECT ==================\n";
		MyArray mergeArr(10);
		mergeArr.Append(1);
		mergeArr.Append(3);
		mergeArr.Append(5);
		mergeArr.Append(7);
		mergeArr.Append(9);

		int mergeWith[] = { 2, 4, 6, 8, 10 };
		std::cout << "Before merge:\n";
		mergeArr.Display();

		mergeArr.MergeWithSortedAscArray(mergeWith, 5);
		std::cout << "After merge:\n";
		mergeArr.Display();


		std::cout << "\n================ MISSING ELEMENTS ==================\n";

		int missSorted[] = { 6, 7, 8, 10, 11, 12 };
		std::cout << "FindSingleMissingElementInSortedAscArray = "
			<< MyArray::FindSingleMissingElementInSortedAscArray(missSorted, 6) << "\n";

		int missUnsorted[] = { 10, 12, 11, 14 };
		std::cout << "FindSingleMissingElementInUnsortedArray = "
			<< MyArray::FindSingleMissingElementInUnsortedArray(missUnsorted, 4) << "\n";

		int manyMissSorted[] = { 3, 4, 6, 8, 9 };
		int* allMissSorted = MyArray::FindAllMissingElementsInSortedAscArray(manyMissSorted, 5);
		PrintIntArray("FindAllMissingElementsInSortedAscArray =", allMissSorted, 2);

		int manyMissUnsorted[] = { 9, 6, 4, 3 };
		int* allMissUnsorted = MyArray::FindAllMissingElementsInUnsortedArray(manyMissUnsorted, 4);
		PrintIntArray("FindAllMissingElementsInUnsortedArray =", allMissUnsorted, 3);

		delete[] allMissSorted;
		delete[] allMissUnsorted;


		std::cout << "\n================ DUPLICATES ==================\n";
		int dupArr[] = { 3, 6, 8, 8, 10, 12, 15, 15, 15, 20 };

		DuplicateElement** d1 = MyArray::FindAllDuplicateElementsInUnsortedArrayUsingHash(dupArr, 10);
		std::cout << "FindAllDuplicateElementsInUnsortedArrayUsingHash done\n";
		std::cout << "Expected: 8 appears 2 times, 15 appears 3 times\n";

		DuplicateElement** d2 = MyArray::FindAllDuplicateElementsInUnsortedArrayUsingLoops(dupArr, 10);
		std::cout << "FindAllDuplicateElementsInUnsortedArrayUsingLoops done\n";
		std::cout << "Expected: 8 appears 2 times, 15 appears 3 times\n";


		std::cout << "\n================ PAIRS WITH SUM ==================\n";
		int pairArr[] = { 1, 3, 4, 5, 6, 8, 9 };

		PairOfElements** p1 = MyArray::FindAllPairsOfElementsWithSumUsingLoops(pairArr, 7, 10);
		std::cout << "FindAllPairsOfElementsWithSumUsingLoops done\n";

		PairOfElements** p2 = MyArray::FindAllPairsOfElementsWithSumUsingHash(pairArr, 7, 10);
		std::cout << "FindAllPairsOfElementsWithSumUsingHash done\n";

		std::cout << "Expected pairs for sum = 10: (1,9), (4,6)\n";


		std::cout << "\n================ EXCEPTION TESTS ==================\n";

		try
		{
			MyArray emptyArr(5);
			std::cout << "Trying Max() on empty array...\n";
			emptyArr.Max();
		}
		catch (const std::exception& e)
		{
			std::cout << "Caught expected exception: " << e.what() << "\n";
		}

		try
		{
			MyArray emptyArr(5);
			std::cout << "Trying Avg() on empty array...\n";
			emptyArr.Avg();
		}
		catch (const std::exception& e)
		{
			std::cout << "Caught expected exception: " << e.what() << "\n";
		}

		try
		{
			MyArray emptyArr(5);
			std::cout << "Trying ShiftLeft() on empty array...\n";
			emptyArr.ShiftLeft();
		}
		catch (const std::exception& e)
		{
			std::cout << "Caught expected exception: " << e.what() << "\n";
		}

		try
		{
			MyArray small(2);
			small.Append(1);
			small.Append(2);
			std::cout << "Trying Append() on full array...\n";
			small.Append(3);
		}
		catch (const std::exception& e)
		{
			std::cout << "Caught expected exception: " << e.what() << "\n";
		}

		try
		{
			MyArray test(3);
			test.Append(10);
			std::cout << "Trying Get(5)...\n";
			test.Get(5);
		}
		catch (const std::exception& e)
		{
			std::cout << "Caught expected exception: " << e.what() << "\n";
		}

		try
		{
			MyArray test(3);
			test.Append(10);
			std::cout << "Trying Delete(5)...\n";
			test.Delete(5);
		}
		catch (const std::exception& e)
		{
			std::cout << "Caught expected exception: " << e.what() << "\n";
		}

		try
		{
			MyArray test(2);
			test.Append(1);
			test.Append(2);
			std::cout << "Trying Insert() on full array...\n";
			test.Insert(1, 99);
		}
		catch (const std::exception& e)
		{
			std::cout << "Caught expected exception: " << e.what() << "\n";
		}

		// ملاحظة:
		// d1, d2, p1, p2 فيها memory leaks لأن الدوال لا ترجع عدد العناصر الفعلي
		// لذلك لا نستطيع حذف العناصر الداخلية هنا بشكل صحيح.
	}
	catch (const std::exception& e)
	{
		std::cout << "\nException: " << e.what() << std::endl;
	}
}