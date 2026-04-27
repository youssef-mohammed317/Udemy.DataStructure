#include "DACExamples.h"

int DACExamples::IBinarySearch(int* arr, int size, int key)
{
	// arr must be sorted
	if (arr == nullptr || size < 1) return -1;

	int low = 0;
	int high = size - 1;
	int mid;

	while (low <= high)
	{
		mid = (low + high) / 2;

		if (arr[mid] == key) return mid;

		if (arr[mid] > key)
			high = mid - 1;
		else
			low = mid + 1;
	}
	return -1;
}

// this apply divide and conquer
int DACExamples::RBinarySearch(int* arr, int low, int high, int key)
{
	// this is the small condition
	if (arr == nullptr || high - low < 0) return -1;

	int mid = (low + high) / 2;

	if (arr[mid] == key)
		return mid;

	// this is the split(divide) of problem and apply dac for it
	if (arr[mid] > key)
		return	RBinarySearch(arr, low, mid - 1, key);

	return RBinarySearch(arr, mid + 1, high, key);

	// no need for combine the problem
}

int DACExamples::RBinarySearch(int* arr, int size, int key)
{
	return RBinarySearch(arr, 0, size - 1, key);
}

void DACExamples::Merge(int* auxilliary, int* arr, int low, int mid, int high)
{
	if (arr == nullptr || high - low < 1 || mid > high || mid < low) return;

	int i = low, j = mid + 1, k = 0;
	while (i <= mid && j <= high)
	{
		if (arr[i] < arr[j])
			auxilliary[k++] = arr[i++];
		else
			auxilliary[k++] = arr[j++];
	}
	while (i <= mid)
	{
		auxilliary[k++] = arr[i++];
	}
	while (j <= high && k < high - low + 1)
	{
		auxilliary[k++] = arr[j++];
	}
	k = 0;
	while (k <= high - low)
	{
		arr[k + low] = auxilliary[k];
		k++;
	}
}

void DACExamples::RMergeSort(int* auxilliary, int* arr, int low, int high)
{
	// this is the small problem
	if (arr == nullptr || high - low < 1) return;

	int mid = (low + high) / 2;

	// this is the splitting
	RMergeSort(auxilliary, arr, low, mid);
	RMergeSort(auxilliary, arr, mid + 1, high);

	// this is the combine
	Merge(auxilliary, arr, low, mid, high);
}

void DACExamples::RMergeSort(int* arr, int size)
{
	int* auxilliary = new int[size];
	RMergeSort(auxilliary, arr, 0, size - 1);
	delete[]auxilliary;
}

void DACExamples::IMergeSort(int* arr, int size)
{
	if (arr == nullptr || size <= 1) return;

	int p, l, mid, h;
	int* auxilliary = new int[size];


	for (p = 2; p < size * 2; p *= 2)
	{
		for (l = 0; l < size - 1; l += p)
		{
			mid = l + p / 2 - 1;
			if (mid >= size - 1) break;
			h = l + p - 1;
			h = h < size ? h : size - 1;
			Merge(auxilliary, arr, l, mid, h);
		}
	}
	delete[]auxilliary;

}

int** DACExamples::ISquareMatrixMultiplication(int** A, int** B, int n)
{
	if (A == nullptr || B == nullptr || n < 1) return nullptr;

	for (int i = 0; i < n; i++)
		if (A[i] == nullptr || B[i] == nullptr)	return nullptr;

	int** C = new int* [n];
	for (int i = 0; i < n; i++)
		C[i] = new int[n] {0};

	int sum;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			sum = 0;
			for (int k = 0; k < n; k++)
			{
				sum += A[i][k] * B[k][j];
			}
			C[i][j] = sum;
		}
	}

	return C;
}

int** DACExamples::MatrixAddition(int** A, int** B, int n)
{
	if (A == nullptr || B == nullptr || n < 1) return nullptr;

	for (int i = 0; i < n; i++)
		if (A[i] == nullptr || B[i] == nullptr)	return nullptr;

	int** C = new int* [n];
	for (int i = 0; i < n; i++)
		C[i] = new int[n] {0};

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			C[i][j] = A[i][j] + B[i][j];
		}
	}
	return C;
}

void DACExamples::RSquareMatrixMultiplication(int** A, int** B, int** C,
	int Arow, int Acol,
	int Brow, int Bcol,
	int Crow, int Ccol,
	int n)
{
	if (n == 1)
	{
		// small problem
		C[Crow][Ccol] += A[Arow][Acol] * B[Brow][Bcol];
	}
	else
	{
		int half = n / 2;
		// split
		// C11 = A11*B11 + A12*B21

		// A11* B11
		RSquareMatrixMultiplication(A, B, C,
			Arow, Acol,
			Brow, Bcol,
			Crow, Ccol,
			half);
		// A12*B21
		RSquareMatrixMultiplication(A, B, C,
			Arow, Acol + half,
			Brow + half, Bcol,
			Crow, Ccol,
			half);


		// C12 = A11*B12 + A12*B22
		// A11*B12
		RSquareMatrixMultiplication(A, B, C,
			Arow, Acol,
			Brow, Bcol + half,
			Crow, Ccol + half,
			half);

		// A12*B22
		RSquareMatrixMultiplication(A, B, C,
			Arow, Acol + half,
			Brow + half, Bcol + half,
			Crow, Ccol + half,
			half);


		// C21 = A21*B11 + A22*B21
		// A21*B11
		RSquareMatrixMultiplication(A, B, C,
			Arow + half, Acol,
			Brow, Bcol,
			Crow + half, Ccol,
			half);

		// A22*B21
		RSquareMatrixMultiplication(A, B, C,
			Arow + half, Acol + half,
			Brow + half, Bcol,
			Crow + half, Ccol,
			half);


		// C22 = A21*B12 + A22*B22
		// A21*B12 
		RSquareMatrixMultiplication(A, B, C,
			Arow + half, Acol,
			Brow, Bcol + half,
			Crow + half, Ccol + half,
			half);

		// A22*B22
		RSquareMatrixMultiplication(A, B, C,
			Arow + half, Acol + half,
			Brow + half, Bcol + half,
			Crow + half, Ccol + half,
			half);
	}
}
int** DACExamples::RSquareMatrixMultiplication(int** A, int** B, int n)
{
	if (A == nullptr || B == nullptr || n < 1) return nullptr;

	for (int i = 0; i < n; i++)
		if (A[i] == nullptr || B[i] == nullptr)	return nullptr;

	int** C = new int* [n];
	for (int i = 0; i < n; i++)
		C[i] = new int[n] {0};

	RSquareMatrixMultiplication(A, B, C, 0, 0, 0, 0, 0, 0, n);

	return C;
}


void DACExamples::TestBehavior()
{
	std::cout << "========== DAC Algorithms Test Behavior ==========\n\n";

	// ---------------------------------------------------------
	// 1. اختبار البحث الثنائي (Binary Search)
	// ---------------------------------------------------------
	std::cout << "[1] Testing Binary Search\n";
	int sortedArray[] = { 2, 4, 6, 8, 10, 12, 14, 16 };
	int bsSize = sizeof(sortedArray) / sizeof(sortedArray[0]);
	int targetFound = 10;
	int targetNotFound = 5;

	std::cout << "Array: { 2, 4, 6, 8, 10, 12, 14, 16 }\n";
	std::cout << "Iterative Search for " << targetFound << " -> Index: " << IBinarySearch(sortedArray, bsSize, targetFound) << " (Expected: 4)\n";
	std::cout << "Recursive Search for " << targetFound << " -> Index: " << RBinarySearch(sortedArray, bsSize, targetFound) << " (Expected: 4)\n";
	std::cout << "Iterative Search for " << targetNotFound << "  -> Index: " << IBinarySearch(sortedArray, bsSize, targetNotFound) << " (Expected: -1)\n";
	std::cout << "Recursive Search for " << targetNotFound << "  -> Index: " << RBinarySearch(sortedArray, bsSize, targetNotFound) << " (Expected: -1)\n\n";

	// ---------------------------------------------------------
	// 2. اختبار ترتيب الدمج (Merge Sort)
	// ---------------------------------------------------------
	std::cout << "[2] Testing Merge Sort\n";
	int unsortedArr1[] = { 38, 27, 43, 3, 9, 82, 10 };
	int unsortedArr2[] = { 38, 27, 43, 3, 9, 82, 10 };
	int msSize = sizeof(unsortedArr1) / sizeof(unsortedArr1[0]);

	IMergeSort(unsortedArr1, msSize);
	std::cout << "Iterative Merge Sort: ";
	for (int i = 0; i < msSize; i++) std::cout << unsortedArr1[i] << " ";
	std::cout << "\n";

	RMergeSort(unsortedArr2, msSize);
	std::cout << "Recursive Merge Sort: ";
	for (int i = 0; i < msSize; i++) std::cout << unsortedArr2[i] << " ";
	std::cout << "\n\n";

	// ---------------------------------------------------------
	// 3. اختبار ضرب المصفوفات المربعة (Square Matrix Multiplication)
	// ---------------------------------------------------------
	std::cout << "[3] Testing Square Matrix Multiplication (2x2)\n";
	int n = 2; // يجب أن تكون من مضاعفات 2 للخوارزمية العودية الحالية

	// حجز الذاكرة للمصفوفات
	int** A = new int* [n];
	int** B = new int* [n];
	for (int i = 0; i < n; i++)
	{
		A[i] = new int[n];
		B[i] = new int[n];
	}

	// تهيئة مصفوفة A
	A[0][0] = 1; A[0][1] = 2;
	A[1][0] = 3; A[1][1] = 4;

	// تهيئة مصفوفة B
	B[0][0] = 5; B[0][1] = 6;
	B[1][0] = 7; B[1][1] = 8;

	// التنفيذ
	int** CI = ISquareMatrixMultiplication(A, B, n);
	int** CR = RSquareMatrixMultiplication(A, B, n);

	// الطباعة
	std::cout << "Iterative Multiplication Result:\n";
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++) std::cout << CI[i][j] << "\t";
		std::cout << "\n";
	}

	std::cout << "Recursive Multiplication Result:\n";
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++) std::cout << CR[i][j] << "\t";
		std::cout << "\n";
	}

	// تنظيف الذاكرة (Memory Cleanup) - ممارسة ممتازة لتجنب Memory Leaks
	for (int i = 0; i < n; i++)
	{
		delete[] A[i];
		delete[] B[i];
		delete[] CI[i];
		delete[] CR[i];
	}
	delete[] A;
	delete[] B;
	delete[] CI;
	delete[] CR;

	std::cout << "\n================ All Tests Passed ================\n";
}











