#include "SortingTechnique.h"
void SortingTechnique::Swap(int& x, int& y)
{
	int temp = x;
	x = y;
	y = temp;
}
void SortingTechnique::PrintArray(int* arr, int size)
{
	if (size <= 1 || arr == nullptr)return;
	std::cout << "{";
	for (int i = 0; i < size; i++)
	{
		std::cout << arr[i];
		if (i < size - 1)
			std::cout << ", ";
	}
	std::cout << "}\n";
}

void SortingTechnique::BubbleAscending(int* arr, int size)
{
	if (size <= 1 || arr == nullptr)return;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size - i - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				Swap(arr[j], arr[j + 1]);
			}
		}
	}
}

void SortingTechnique::BubbleDescending(int* arr, int size)
{
	if (size <= 1 || arr == nullptr)return;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size - i - 1; j++)
		{
			if (arr[j] < arr[j + 1])
			{
				Swap(arr[j], arr[j + 1]);
			}
		}
	}
}

void SortingTechnique::InsertionAscending(int* arr, int size)
{
	if (size <= 1 || arr == nullptr)return;

	for (int i = 1; i < size; i++)
	{
		for (int j = i; j > 0; j--)
		{
			if (arr[j] < arr[j - 1])
				Swap(arr[j], arr[j - 1]);
		}
	}
}

void SortingTechnique::InsertionDescending(int* arr, int size)
{
	if (size <= 1 || arr == nullptr)return;

	for (int i = 1; i < size; i++)
	{
		for (int j = i; j > 0; j--)
		{
			if (arr[j] > arr[j - 1])
				Swap(arr[j], arr[j - 1]);
		}
	}
}

void SortingTechnique::SelectionAscending(int* arr, int size)
{
	if (size <= 1 || arr == nullptr)return;
	int min;
	for (int i = 0; i < size - 1; i++)
	{
		min = i;
		for (int j = i + 1; j < size; j++)
		{
			if (arr[j] < arr[min])
			{
				min = j;
			}
		}
		if (min != i)
		{
			Swap(arr[min], arr[i]);
		}
	}
}

void SortingTechnique::SelectionDescending(int* arr, int size)
{
	if (size <= 1 || arr == nullptr)return;
	int max;
	for (int i = 0; i < size - 1; i++)
	{
		max = i;
		for (int j = i + 1; j < size; j++)
		{
			if (arr[j] > arr[max])
			{
				max = j;
			}
		}
		if (max != i)
		{
			Swap(arr[max], arr[i]);
		}
	}
}

void SortingTechnique::TestBehavior()
{
	const int size = 12;

	// المصفوفات المرجعية (النتيجة الصحيحة المتوقعة)
	int expectedAsc[] = { 2, 5, 12, 18, 24, 45, 67, 73, 89, 95, 237, 356 };
	int expectedDesc[] = { 356, 237, 95, 89, 73, 67, 45, 24, 18, 12, 5, 2 };

	std::cout << "=========== Testing Sorting Techniques ===========" << std::endl;
	std::cout << "Array Size: " << size << "\n" << std::endl;

	// =========================================================
	// 1. Bubble Sort
	// =========================================================
	std::cout << "[1] Bubble Sort" << std::endl;

	std::cout << "  -- Target: Ascending --" << std::endl;
	int arr1[] = { 45, 12, 89, 2, 67, 356, 24, 95, 18, 237, 5, 73 };
	std::cout << "  Before:   "; PrintArray(arr1, size);
	BubbleAscending(arr1, size);
	std::cout << "  Expected: "; PrintArray(expectedAsc, size);
	std::cout << "  After:    "; PrintArray(arr1, size);

	std::cout << "\n  -- Target: Descending --" << std::endl;
	int arr2[] = { 45, 12, 89, 2, 67, 356, 24, 95, 18, 237, 5, 73 };
	std::cout << "  Before:   "; PrintArray(arr2, size);
	BubbleDescending(arr2, size);
	std::cout << "  Expected: "; PrintArray(expectedDesc, size);
	std::cout << "  After:    "; PrintArray(arr2, size);


	// =========================================================
	// 2. Selection Sort
	// =========================================================
	std::cout << "\n\n[2] Selection Sort" << std::endl;

	std::cout << "  -- Target: Ascending --" << std::endl;
	int arr3[] = { 45, 12, 89, 2, 67, 356, 24, 95, 18, 237, 5, 73 };
	std::cout << "  Before:   "; PrintArray(arr3, size);
	SelectionAscending(arr3, size);
	std::cout << "  Expected: "; PrintArray(expectedAsc, size);
	std::cout << "  After:    "; PrintArray(arr3, size);

	std::cout << "\n  -- Target: Descending --" << std::endl;
	int arr4[] = { 45, 12, 89, 2, 67, 356, 24, 95, 18, 237, 5, 73 };
	std::cout << "  Before:   "; PrintArray(arr4, size);
	SelectionDescending(arr4, size);
	std::cout << "  Expected: "; PrintArray(expectedDesc, size);
	std::cout << "  After:    "; PrintArray(arr4, size);


	// =========================================================
	// 3. Insertion Sort
	// =========================================================
	std::cout << "\n\n[3] Insertion Sort" << std::endl;

	std::cout << "  -- Target: Ascending --" << std::endl;
	int arr5[] = { 45, 12, 89, 2, 67, 356, 24, 95, 18, 237, 5, 73 };
	std::cout << "  Before:   "; PrintArray(arr5, size);
	InsertionAscending(arr5, size);
	std::cout << "  Expected: "; PrintArray(expectedAsc, size);
	std::cout << "  After:    "; PrintArray(arr5, size);

	std::cout << "\n  -- Target: Descending --" << std::endl;
	int arr6[] = { 45, 12, 89, 2, 67, 356, 24, 95, 18, 237, 5, 73 };
	std::cout << "  Before:   "; PrintArray(arr6, size);
	InsertionDescending(arr6, size);
	std::cout << "  Expected: "; PrintArray(expectedDesc, size);
	std::cout << "  After:    "; PrintArray(arr6, size);

	std::cout << "\n==================================================" << std::endl;
}