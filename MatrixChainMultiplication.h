#pragma once
#include <iostream>

class MatrixChainMultiplication
{
private:
	// 1-Recursion Helper
	static int MCMRecursion(int* p, int i, int j);

	// 2-Memoization Helper
	static int MCMMemoization(int* p, int i, int j, int** m);

	// Helper to print the optimal parenthesization
	static void PrintOptimalParens(int i, int j, int** bracket, char& name);

public:
	// 1-Recursion
	static void ExecuteRecursion(int* p, int n);

	// 2-Memoization
	static void ExecuteMemoization(int* p, int n);

	// 3-Tabulation
	static void ExecuteTabulation(int* p, int n);
};