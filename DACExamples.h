#pragma once
class DACExamples
{
	static void RBinarySearch(int* arr, int low, int high);

	static void Merge(int* arr, int low, int mid, int high);
	static void RMergeSort(int* arr, int low, int high);

	static int** MatrixAddition(int** A, int** B, int n);
public:
	static void IBinarySearch(int* arr, int size);
	static void RBinarySearch(int* arr, int size);

	static void IMergeSort(int* arr, int size);
	static void RMergeSort(int* arr, int size);

	static int** IMatrixMultiplication(int** A, int** B, int n);
	static int** RMatrixMultiplication(int** A, int** B, int n);
};

