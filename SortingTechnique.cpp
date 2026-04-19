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


void SortingTechnique::IMergeAscending(int* arr, int low, int mid, int high)
{
	if (high - low + 1 <= 1 || arr == nullptr)return;

	int* sortedArr = new int[high - low + 1];
	int k = 0;
	int i = low;
	int j = mid + 1;
	while (i <= mid && j <= high && k < high - low + 1)
	{
		if (arr[i] < arr[j])
		{
			sortedArr[k++] = arr[i++];
		}
		else
		{
			sortedArr[k++] = arr[j++];
		}
	}
	while (i <= mid && k < high - low + 1)
	{
		sortedArr[k++] = arr[i++];
	}
	while (j <= high && k < high - low + 1)
	{
		sortedArr[k++] = arr[j++];
	}
	k = 0;
	i = low;
	while (k < high - low + 1 && i <= high)
	{
		arr[i++] = sortedArr[k++];
	}
	delete[]sortedArr;
}

void SortingTechnique::IMergeDescending(int* arr, int low, int mid, int high)
{
	if (high - low + 1 <= 1 || arr == nullptr)return;

	int* sortedArr = new int[high - low + 1];
	int k = 0;
	int i = low;
	int j = mid + 1;
	while (i <= mid && j <= high && k < high - low + 1)
	{
		if (arr[i] > arr[j])
		{
			sortedArr[k++] = arr[i++];
		}
		else
		{
			sortedArr[k++] = arr[j++];
		}
	}
	while (i <= mid && k < high - low + 1)
	{
		sortedArr[k++] = arr[i++];
	}
	while (j <= high && k < high - low + 1)
	{
		sortedArr[k++] = arr[j++];
	}
	k = 0;
	i = low;
	while (k < high - low + 1 && i <= high)
	{
		arr[i++] = sortedArr[k++];
	}
	delete[]sortedArr;
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


void SortingTechnique::ShellAscending(int* arr, int size)
{
	if (size <= 1 || arr == nullptr)return;

	int gap = size / 2;
	int low = 0;
	int high = low + gap;
	int h, l;
	while (gap > 0)
	{
		while (low >= 0 && high < size)
		{
			h = high++;
			l = low++;
			while (l >= 0 && h < size && arr[l] > arr[h])
			{
				Swap(arr[l], arr[h]);
				l = l - gap;
				h = h - gap;
			}
		}
		gap = gap / 2;
		low = 0;
		high = low + gap;
	}
}


void SortingTechnique::ShellDescending(int* arr, int size)
{
	if (size <= 1 || arr == nullptr)return;

	int gap = size / 2;
	int low = 0;
	int high = low + gap;
	int h, l;
	while (gap > 0)
	{
		while (low >= 0 && high < size)
		{
			h = high++;
			l = low++;
			while (l >= 0 && h < size && arr[l] < arr[h])
			{
				Swap(arr[l], arr[h]);
				l = l - gap;
				h = h - gap;
			}
		}
		gap = gap / 2;
		low = 0;
		high = low + gap;
	}
}

void SortingTechnique::IMergingAscending(int* arr, int size)
{
	int low, high, mid, p, i;
	for (p = 2; p < size * 2; p *= 2)
	{
		for (i = 0; i + p / 2 < size; i += p)
		{
			low = i;
			mid = low + (p / 2) - 1;
			high = i + p - 1;
			if (high > size - 1)
				high = size - 1;

			IMergeAscending(arr, low, mid, high);
		}
	}
}
void SortingTechnique::IMergingDescending(int* arr, int size)
{
	int low, high, mid, p, i;
	for (p = 2; p <= size * 2; p *= 2)
	{
		for (i = 0; i + p / 2 < size; i += p)
		{
			low = i;
			mid = low + (p / 2) - 1;
			high = i + p - 1;
			if (high > size - 1)
				high = size - 1;

			IMergeDescending(arr, low, mid, high);
		}
	}
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

	// =========================================================
	// 7. Shell Sort
	// =========================================================
	{
		// اختبار الترتيب التصاعدي (مصفوفة عشوائية)
		int arrA[] = { 45, 12, 89, 2, 67, 356, 24, 95, 18, 237, 5, 73 };
		int sizeA = 12;
		std::cout << "\n[7.1] Shell Ascending\n  Before: "; PrintArray(arrA, sizeA);
		ShellAscending(arrA, sizeA);
		std::cout << "  After:  "; PrintArray(arrA, sizeA);

		// اختبار الترتيب التنازلي (مصفوفة تحتوي على أرقام سالبة ومكررة)
		int arrD[] = { -10, 55, 0, 55, -20, 100, 7 };
		int sizeD = 7;
		std::cout << "[7.2] Shell Descending\n  Before: "; PrintArray(arrD, sizeD);
		ShellDescending(arrD, sizeD);
		std::cout << "  After:  "; PrintArray(arrD, sizeD);
	}

	// =========================================================
	// 8. Iterative Merge Sort
	// =========================================================
	{
		// اختبار الترتيب التصاعدي (مصفوفة بحجم فردي لاختبار حالات الـ Tail)
		int arrA[] = { 38, 27, 43, 3, 9,1, 82, 10 ,83,10,-3,-99 };
		int sizeA = 12;
		std::cout << "\n[8.1] Iterative Merge Ascending\n  Before: "; PrintArray(arrA, sizeA);
		IMergingAscending(arrA, sizeA);
		std::cout << "  After:  "; PrintArray(arrA, sizeA);

		// اختبار الترتيب التنازلي
		int arrD[] = { 100, 5, 20, 15, 30, 0 };
		int sizeD = 6;
		std::cout << "[8.2] Iterative Merge Descending\n  Before: "; PrintArray(arrD, sizeD);
		IMergingDescending(arrD, sizeD);
		std::cout << "  After:  "; PrintArray(arrD, sizeD);
	}
	std::cout << "\n======================================================" << std::endl;
}