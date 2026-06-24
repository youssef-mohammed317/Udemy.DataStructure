#pragma once
#include <iostream>

class Knapsack01
{
private:
	// 1-Recursion Helper
	static int KnapsackRecursion(int* wt, int* val, int W, int n);

	// 2-Memoization Helper
	static int KnapsackMemoization(int* wt, int* val, int W, int n, int** M);

	// Helper to print the selected items (Traceback)
	static void PrintSelectedItems(int** M, int* wt, int W, int n);

public:
	// 1-Recursion
	static void ExecuteRecursion(int* wt, int* val, int W, int n);

	// 2-Memoization
	static void ExecuteMemoization(int* wt, int* val, int W, int n);

	// 3-Tabulation
	static void ExecuteTabulation(int* wt, int* val, int W, int n);

	static void TestBehavior();
};