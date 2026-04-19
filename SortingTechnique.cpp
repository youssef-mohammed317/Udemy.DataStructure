#include "SortingTechnique.h"
void SortingTechnique::Swap(int& x, int& y)
{
	int temp = x;
	x = y;
	y = temp;
}
MinMax SortingTechnique::GetMinMax(int* arr, int size)
{
	MinMax minmax;
	minmax.max = arr[0];
	minmax.min = arr[0];

	for (int i = 1; i < size; i++)
	{
		if (arr[i] > minmax.max)
		{
			minmax.max = arr[i];
		}
		else if (arr[i] < minmax.min)
		{
			minmax.min = arr[i];

		}
	}
	return minmax;
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

void SortingTechnique::CountAscending(int* arr, int size)
{
	if (size <= 1 || arr == nullptr)return;

	MinMax minmax = GetMinMax(arr, size);

	int max = minmax.max;
	int min = minmax.min;

	int* count = new int[max - min + 1] {0};

	for (int i = 0; i < size; i++)
	{
		count[arr[i] - min]++;
	}
	int j = 0;
	for (int i = 0; i < max - min + 1 && j < size; i++)
	{
		while (count[i] > 0)
		{
			arr[j++] = i + min;
			count[i]--;
		}
	}
	delete[]count;

}

void SortingTechnique::CountDescending(int* arr, int size)
{
	if (size <= 1 || arr == nullptr)return;

	MinMax minmax = GetMinMax(arr, size);

	int max = minmax.max;
	int min = minmax.min;


	int* count = new int[max - min + 1] {0};

	for (int i = 0; i < size; i++)
	{
		count[arr[i] - min]++;
	}
	int j = 0;
	for (int i = max - min; i >= 0 && j < size; i--)
	{
		while (count[i] > 0)
		{
			arr[j++] = i + min;
			count[i]--;
		}
	}
	delete[]count;

}

void SortingTechnique::BinBucketAscending(int* arr, int size)
{
	if (size <= 1 || arr == nullptr)return;

	MinMax minmax = GetMinMax(arr, size);

	int max = minmax.max;
	int min = minmax.min;


	Node** bin = new Node * [max - min + 1];
	for (int i = 0; i < max - min + 1; i++)
		bin[i] = nullptr;

	for (int i = 0; i < size; i++)
	{
		bin[arr[i] - min] = new Node(arr[i], bin[arr[i] - min]);
	}
	int j = 0;
	for (int i = 0; i < max - min + 1 && j < size; i++)
	{
		if (bin[i] != nullptr)
		{
			Node* curr = bin[i];
			Node* temp;
			while (curr != nullptr)
			{
				arr[j++] = curr->GetData();
				temp = curr;
				curr = curr->GetNext();
				delete temp;
			}
		}
	}
	delete[]bin;
}

void SortingTechnique::BinBucketDescending(int* arr, int size)
{
	if (size <= 1 || arr == nullptr)return;

	MinMax minmax = GetMinMax(arr, size);

	int max = minmax.max;
	int min = minmax.min;


	Node** bin = new Node * [max - min + 1];
	for (int i = 0; i < max - min + 1; i++)
		bin[i] = nullptr;

	for (int i = 0; i < size; i++)
	{
		bin[arr[i] - min] = new Node(arr[i], bin[arr[i] - min]);
	}
	int j = 0;
	for (int i = max - min; i >= 0 && j < size; i--)
	{
		if (bin[i] != nullptr)
		{
			Node* curr = bin[i];
			Node* temp;
			while (curr != nullptr)
			{
				arr[j++] = curr->GetData();
				temp = curr;
				curr = curr->GetNext();
				delete temp;
			}
		}
	}
	delete[]bin;
}

void SortingTechnique::RadixAscending(int* arr, int size)
{
	if (size <= 1 || arr == nullptr) return;
	// decimal system size 10, octal system size 8 ....
	List* radix = new List[10];

	int max = GetMinMax(arr, size).max;

	int times = 0;

	while (max > 0)
	{
		times++;
		max = max / 10;
	}
	int data, radixIndex, exp = 1;


	for (int i = 1; i <= times; i++)
	{
		for (int j = 0; j < size; j++)
		{
			data = arr[j];

			radixIndex = (data / exp) % 10;
			radix[radixIndex].Append(data);
		}
		int k = 0, r = 0;
		while (k < size && r < 10)
		{

			while (!radix[r].IsEmpty())
			{
				arr[k++] = radix[r].Front();
			}
			r++;
		}
		exp = exp * 10;
	}
	delete[]radix;
}

void SortingTechnique::RadixDescending(int* arr, int size)
{
	if (size <= 1 || arr == nullptr) return;
	// decimal system size 10, octal system size 8 ....
	List* radix = new List[10];

	int max = GetMinMax(arr, size).max; // assume 237 -> 3 times

	int times = 0;

	while (max > 0)
	{
		times++;
		max = max / 10;
	}
	int data, radixIndex, exp = 1;

	for (int i = 1; i <= times; i++)
	{
		for (int j = 0; j < size; j++)
		{
			data = arr[j];
			radixIndex = (data / exp) % 10;
			radix[radixIndex].Append(data);
		}
		int k = 0, r = 9;
		while (k < size && r >= 0)
		{
			while (!radix[r].IsEmpty())
			{
				arr[k++] = radix[r].Front();
			}
			r--;
		}
		exp = exp * 10;
	}
	delete[]radix;
}

void SortingTechnique::TestBehavior()
{
	std::cout << "=========== Testing All Sorting Techniques ===========" << std::endl;

	// =========================================================
	// 1. Bubble Sort
	// =========================================================
	{
		int arrA[] = { 64, 34, 25, 12, 22 };
		int sizeA = 5;
		std::cout << "[1.1] Bubble Ascending\n  Before: "; PrintArray(arrA, sizeA);
		BubbleAscending(arrA, sizeA);
		std::cout << "  After:  "; PrintArray(arrA, sizeA);

		int arrD[] = { 5, 90, 11, 45, 100 };
		int sizeD = 5;
		std::cout << "[1.2] Bubble Descending\n  Before: "; PrintArray(arrD, sizeD);
		BubbleDescending(arrD, sizeD);
		std::cout << "  After:  "; PrintArray(arrD, sizeD);
	}

	// =========================================================
	// 2. Selection Sort
	// =========================================================
	{
		int arrA[] = { 29, 10, 14, 37, 13 };
		int sizeA = 5;
		std::cout << "\n[2.1] Selection Ascending\n  Before: "; PrintArray(arrA, sizeA);
		SelectionAscending(arrA, sizeA);
		std::cout << "  After:  "; PrintArray(arrA, sizeA);

		int arrD[] = { 8, 3, 11, 2, 19 };
		int sizeD = 5;
		std::cout << "[2.2] Selection Descending\n  Before: "; PrintArray(arrD, sizeD);
		SelectionDescending(arrD, sizeD);
		std::cout << "  After:  "; PrintArray(arrD, sizeD);
	}

	// =========================================================
	// 3. Insertion Sort
	// =========================================================
	{
		int arrA[] = { 3, 1, 4, 1, 5 };
		int sizeA = 5;
		std::cout << "\n[3.1] Insertion Ascending\n  Before: "; PrintArray(arrA, sizeA);
		InsertionAscending(arrA, sizeA);
		std::cout << "  After:  "; PrintArray(arrA, sizeA);

		int arrD[] = { 10, 2, 55, 30, 1 };
		int sizeD = 5;
		std::cout << "[3.2] Insertion Descending\n  Before: "; PrintArray(arrD, sizeD);
		InsertionDescending(arrD, sizeD);
		std::cout << "  After:  "; PrintArray(arrD, sizeD);
	}

	// =========================================================
	// 4. Count Sort (Negative Support)
	// =========================================================
	{
		int arrA[] = { -5, 2, 0, -2, 5 };
		int sizeA = 5;
		std::cout << "\n[4.1] Count Ascending\n  Before: "; PrintArray(arrA, sizeA);
		CountAscending(arrA, sizeA);
		std::cout << "  After:  "; PrintArray(arrA, sizeA);

		int arrD[] = { 10, -10, 5, -5, 0 };
		int sizeD = 5;
		std::cout << "[4.2] Count Descending\n  Before: "; PrintArray(arrD, sizeD);
		CountDescending(arrD, sizeD);
		std::cout << "  After:  "; PrintArray(arrD, sizeD);
	}

	// =========================================================
	// 5. Bin / Bucket Sort (Negative Support)
	// =========================================================
	{
		int arrA[] = { 100, -50, 25, 0, 75 };
		int sizeA = 5;
		std::cout << "\n[5.1] BinBucket Ascending\n  Before: "; PrintArray(arrA, sizeA);
		BinBucketAscending(arrA, sizeA);
		std::cout << "  After:  "; PrintArray(arrA, sizeA);

		int arrD[] = { 1, 9, 3, 7, 5 };
		int sizeD = 5;
		std::cout << "[5.2] BinBucket Descending\n  Before: "; PrintArray(arrD, sizeD);
		BinBucketDescending(arrD, sizeD);
		std::cout << "  After:  "; PrintArray(arrD, sizeD);
	}

	// =========================================================
	// 6. Radix Sort
	// =========================================================
	{
		int arrA[] = { 170, 45, 75, 90, 24 };
		int sizeA = 5;
		std::cout << "\n[6.1] Radix Ascending\n  Before: "; PrintArray(arrA, sizeA);
		RadixAscending(arrA, sizeA);
		std::cout << "  After:  "; PrintArray(arrA, sizeA);

		int arrD[] = { 10, 500, 2, 88, 30 };
		int sizeD = 5;
		std::cout << "[6.2] Radix Descending\n  Before: "; PrintArray(arrD, sizeD);
		RadixDescending(arrD, sizeD);
		std::cout << "  After:  "; PrintArray(arrD, sizeD);
	}

	std::cout << "\n======================================================" << std::endl;
}