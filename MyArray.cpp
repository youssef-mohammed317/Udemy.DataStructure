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
			return i;
		}
	return -1;
}
int MyArray::BinarySearch(int key)
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
	return -1;
}
int MyArray::RBinarySearch(int low, int high, int key)
{
	int low = 0;
	int high = length - 1;
	while (low <= high) {
		int mid = (low + high) / 2;
		if (arr[mid] == key)
			return mid;
		else if (arr[mid] > key)
			return RBinarySearch(low, mid - 1, key);
		else if (arr[mid] < key)
			return RBinarySearch(mid + 1, high, key);
	}
	return -1;
}

void MyArray::InsertInSortedAsc(int value)
{
	ThrowIfFull();
	int j = 0;
	for(j = length-1;arr[j]>value;j--)
	{
		Swap(arr[j], arr[j + 1]);
	}
	arr[j] = value;

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
	int j = length-1,i=0;
	while(i<j)
	{
		
		while(arr[i]<0) {
			i++;
		}
		while (arr[j]>=0)
		{
			j--;
		}
		if(i<j)
		{
			Swap(arr[i], arr[j]);
		}
	}
}
void MyArray::MergeWithSortedAscArray( int* arr2, int size2)
{
	int *arr = new int[this->length + size2];
	int i = 0, j = 0, k = 0;
	
	while(i < this->length && j < size2)
	{
		if(arr[i] == arr2[j])
		{
			arr[k++] = arr[i];
			i++;j++;
		}
		else if(arr[i]<arr2[j])
		{
			arr[k++] = arr[i++];
		}else if(arr[i]>arr2[j])
		{
			arr[k++] = arr2[j++];
		}
	}
	while (i < this->length)
	{
		arr[k++] = arr[i++];
	}
	while (j < size2)
	{
		arr[k++] = arr2[j++];
	}
}


int* MyArray::UnionTwoSortedAscArraysIntoSortedOne(int* arr1, int size1, int* arr2, int size2)
{
	int *arr = new int[size1 + size2];
	int i = 0, j = 0, k = 0;
	
	while(i < size1 && j < size2)
	{
		if(arr1[i] == arr2[j])
		{
			arr[k++] = arr1[i];
			i++;j++;
		}
		else if(arr1[i]<arr2[j])
		{
			arr[k++] = arr1[i++];
		}else if(arr1[i]>arr2[j])
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
	int *arr = new int[size1 + size2];
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
			arr[k++] = arr2[j++];
		}
	}
	return arr;
}
int* MyArray::IntersectionTwoSortedAscArraysIntoSortedOne(int* arr1, int size1, int* arr2, int size2)
{

	int *arr = new int[size1> size2 ? size1:size2];
	int i = 0, j = 0, k = 0;
	while (j < size2 && i<size1)
	{
		if(arr1[i] == arr2[j])
		{
			arr[k++] = arr1[i++];
			j++;
		}
		else if(arr1[i]<arr2[j])
		{
			i++;
		}else if(arr1[i]>arr2[j]){
			j++;
		}
	}
	return arr;
}
int* MyArray::IntersectionTwoUnsortedArraysIntoSortedOne(int* arr1, int size1, int* arr2, int size2)
{

	int *arr = new int[size1> size2 ? size1:size2];
	int i = 0, j = 0, k = 0;
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
		if (found)
		{
			arr[k++] = arr2[j];
		}
		j++;
	}
	return arr;
}
int* MyArray::DifferenceTwoUnsortedArraysIntoSortedOne(int* arr1, int size1, int* arr2, int size2)
{

	int *arr = new int[size1];
	int i = 0, j = 0, k = 0;
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

	int *arr = new int[size1];
	int i = 0, j = 0, k = 0;
	while (i < size1 && j<size2)
	{

		if(arr1[i] < arr2[j])
		{
			arr[k++] = arr1[i++];
		}else if(arr1[i] > arr2[j])
		{
			j++;
		}else if(arr1[i] == arr2[j])
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
	for(int i = 1; i < size; i++)
	{
		if(arr[i] - i != diff)
		{
			return arr[i] - 1;
		}
	}

}
int MyArray::FindSingleMissingElementInUnsortedArray(int* arr, int size)
{
	int max = arr[0];
	int min = arr[0];
	int sum = 0;
	for(int i=1; i<size; i++)
	{
		if(arr[i] > max)
		{
			max = arr[i];
		}else if(arr[i] < min)
		{
			min = arr[i];
		}
		sum += arr[i];
	}

	return (max*(max+1)/2) - (min*(min-1)/2) - sum;
}
int* MyArray::FindAllMissingElementsInSortedAscArray(int* arr, int size) 
{
	// use Bitwise if size less than 64
	int max = arr[size -1];
	int min = arr[0];
	int countMessing = 0;
	unsigned long long hash = 0;
	int* temp = new int[max - min + 1];

	for(int i=0; i<size; i++)
	{
		hash = hash | (1 << (arr[i] - min));

	}

	for(int i=0; i<size; i++)
	{
		hash = hash >> 1;
		int bit = hash & 1;
		if(bit == 0)
		{
			temp[countMessing++] = min + i;
		}
	}
	int* result = new int[countMessing];
	for(int i=0; i<countMessing; i++)
	{
		result[i] = temp[i];
	}
	delete[] temp;

	return result;

}
int* MyArray::FindAllMissingElementsInUnsortedArray(int* arr, int size)
{
	// use Hash Array
	int max = arr[0];
	int min = arr[0];
	for(int i=1; i<size; i++)
	{
		if(arr[i] > max)
		{
			max = arr[i];
		}else if(arr[i] < min)
		{
			min = arr[i];
		}
	}

	int* hash = new int[max - min + 1] {0};

	for(int i=0; i<size; i++)
	{
		hash[arr[i] - min] = 1;
	}

	int countMessing = 0;

	for(int i = 0; i < max - min + 1; i++)
	{
		if(hash[i] == 0)
		{
			countMessing++;
		}
	}

	int* result = new int[countMessing];

	for(int i = 0, j = 0; i < max - min + 1; i++)
	{
		if(hash[i] == 0)
		{
			result[j++] = min + i;
		}
	}
	delete [] hash;
	return result;
}
DuplicateElement** MyArray::FindAllDuplicateElementsInUnsortedArrayUsingHash(int* arr, int size)
{
	// use Hash Array
	int max = arr[0]; // if sorted get min and max directly
	int min = arr[0];
	for(int i=1; i<size; i++)
	{
		if(arr[i] > max)
		{
			max = arr[i];
		}else if(arr[i] < min)
		{
			min = arr[i];
		}
	}
	int* hash = new int[max - min + 1] {0};

	for(int i=0; i<size; i++)
	{
		hash[arr[i] - min]++;
	}

	int countDuplicate = 0;

	for(int i = 0; i < max - min + 1; i++)
	{
		if(hash[i] > 1)
		{
			countDuplicate++;
		}
	}

	DuplicateElement** result = new DuplicateElement*[countDuplicate];

	for(int i = 0, j = 0; i < max - min + 1; i++)
	{
		if(hash[i] > 1)
		{
			result[j++] = new DuplicateElement(min + i, hash[i]);
		}
	}

	delete [] hash;
	return result;
}

DuplicateElement** MyArray::FindAllDuplicateElementsInUnsortedArrayUsingLoops(int* arr, int size)
{
	DuplicateElement** temp = new DuplicateElement*[size]{nullptr};
	int count = 0,k =0;

	for(int i=0; i<size; i++)
	{
		if(arr[i] != NULL)
		{
			count = 0;
			for(int j = 0; j < size; j++)
			{
				if(arr[i] == arr[j] && i != j)
				{
					count++;
					arr[j] = NULL;
				}
			}
			if(count > 1)
			{
				temp[k++] = new DuplicateElement(arr[i], count);
			}
		}

	DuplicateElement** result = new DuplicateElement*[k];
	for(int i = 0; i < k; i++)
	{
		result[i] = temp[i];
	}
	delete [] temp;
	return result;
}
}


void MyArray::TestBehavior()
{
	try
	{
		MyArray arr(10);

		std::cout << "\nAppend values:\n";
		arr.Append(10);
		arr.Append(20);
		arr.Append(30);
		arr.Append(40);
		arr.Append(50);
		arr.Display();

		std::cout << "\n\nInsert 25 at index 2:\n";
		arr.Insert(2, 25);
		arr.Display();

		std::cout << "\n\nDelete element at index 3:\n";
		int deleted = arr.Delete(3);
		std::cout << "Deleted value: " << deleted << std::endl;
		arr.Display();

		std::cout << "\n\nGet element at index 2: ";
		std::cout << arr.Get(2) << std::endl;

		std::cout << "\nSet index 1 to 99\n";
		arr.Set(1, 99);
		arr.Display();

		std::cout << "\n\nMax value: " << arr.Max() << std::endl;
		std::cout << "Min value: " << arr.Min() << std::endl;
		std::cout << "Sum: " << arr.Sum() << std::endl;
		std::cout << "Average: " << arr.Avg() << std::endl;

		std::cout << "\nReverse array:\n";
		arr.Reverse();
		arr.Display();

		std::cout << "\n\nShift Left:\n";
		arr.ShiftLeft();
		arr.Display();

		std::cout << "\n\nRotate Left:\n";
		arr.RotateLeft();
		arr.Display();

		std::cout << "\n\nRotate Right:\n";
		arr.RotateRight();
		arr.Display();

		std::cout << "\n\nShift Right:\n";
		arr.ShiftRight();
		arr.Display();

	}
	catch (const std::exception& e)
	{
		std::cout << "\nException: " << e.what() << std::endl;
	}
}

MyArray::~MyArray()
{
	delete[] arr;
}