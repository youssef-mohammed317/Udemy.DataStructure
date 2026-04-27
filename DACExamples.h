#pragma once
#include <iostream>

class DACExamples
{
	static int RBinarySearch(int* arr, int low, int high, int key);

	static void Merge(int* auxilliary, int* arr, int low, int mid, int high);
	static void RMergeSort(int* auxilliary, int* arr, int low, int high);

	static int** MatrixAddition(int** A, int** B, int n);
	static void RSquareMatrixMultiplication(int** A, int** B, int** C,
		int Arow, int Acol,
		int Brow, int Bcol,
		int Crow, int Ccol,
		int n);
public:
	static int IBinarySearch(int* arr, int size, int key);
	static int RBinarySearch(int* arr, int size, int key);

	static void IMergeSort(int* arr, int size);
	static void RMergeSort(int* arr, int size);

	static int** ISquareMatrixMultiplication(int** A, int** B, int n);
	static int** RSquareMatrixMultiplication(int** A, int** B, int n);

	static void TestBehavior();
};

