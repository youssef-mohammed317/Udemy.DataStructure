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
	double Avg();
	void Reverse();
	void ShiftLeft();
	void ShiftRight();
	void RotateLeft();
	void RotateRight();

	int LinearSearch(int key);
	int ImprovedLinearSearch(int key);
	int BinarySearch(int key);
	int RBinarySearch(int low, int high, int key);

	bool IsSortedAsc();
	void InsertInSortedAsc(int value);
	void ArrangingNegativesToLeftSide();
	void MergeWithSortedAscArray(int* arr2, int size2);

	static int* UnionTwoSortedAscArraysIntoSortedOne(int* arr1, int size1, int* arr2, int size2); // same as Merge
	static int* UnionTwoUnsortedArraysIntoUnSortedOne(int* arr1, int size1, int* arr2, int size2);

	static int* IntersectionTwoSortedAscArraysIntoSortedOne(int* arr1, int size1, int* arr2, int size2);
	static int* IntersectionTwoUnsortedArraysIntoSortedOne(int* arr1, int size1, int* arr2, int size2);
	
	static int* DifferenceTwoUnsortedArraysIntoSortedOne(int* arr1, int size1, int* arr2, int size2);
	static int* DifferenceTwoSortedAscArraysIntoSortedOne(int* arr1, int size1, int* arr2, int size2);

	static int FindSingleMissingElementInSortedAscArray(int* arr, int size);
	static int FindSingleMissingElementInUnsortedArray(int* arr, int size);

	static int* FindAllMissingElementsInSortedAscArray(int* arr, int size);
	static int* FindAllMissingElementsInUnsortedArray(int* arr, int size);

	static DuplicateElement** FindAllDuplicateElementsInUnsortedArrayUsingHash(int* arr, int size);
	static DuplicateElement** FindAllDuplicateElementsInUnsortedArrayUsingLoops(int* arr, int size);

	void static TestBehavior();
	~MyArray();
};
class DuplicateElement
{
private:
	int value;
	int count;
public:
	DuplicateElement(int value, int count) {

		this->value = value;
		this->count = count;

	}
	int GetValue() {
		return value;
	}
	int GetCount() {
		return count;
	}

	void Display() {
		std::cout << "Value: " << value << " Count: " << count << std::endl;
	}

	~DuplicateElement() {}

};

