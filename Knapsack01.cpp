#include "Knapsack01.h"


void Knapsack01::ExecuteRecursion(int* wt, int* val, int W, int n)
{
	std::cout << "maximum profit is => " << KnapsackRecursion(wt, val, W, n - 1);
}

int Knapsack01::KnapsackRecursion(int* wt, int* val, int W, int n)
{
	if (W <= 0 || n < 0)
		return 0;

	int x = -1;
	// select
	if (wt[n] <= W)
	{
		x = KnapsackRecursion(wt, val, W - wt[n], n - 1) + val[n];
	}
	// not select
	int y = KnapsackRecursion(wt, val, W, n - 1);

	return y > x ? y : x;
}

void Knapsack01::ExecuteMemoization(int* wt, int* val, int W, int n)
{

	int** M = new int* [W + 1];
	for (int i = 0; i <= W; i++)
	{
		M[i] = new int[n];
		for (int j = 0; j < n; j++)
			M[i][j] = -1;
	}


	KnapsackMemoization(wt, val, W, n - 1, M);

	std::cout << "maximum profit is => " << M[W][n - 1];


	for (int i = 0; i <= W; i++)
		delete[] M[i];
	delete[] M;
}

int Knapsack01::KnapsackMemoization(int* wt, int* val, int W, int n, int** M)
{
	if (W <= 0 || n < 0)
		return 0;

	if (M[W][n] != -1)
		return M[W][n];

	int x = -1;
	// select
	if (wt[n] <= W)
	{
		x = KnapsackMemoization(wt, val, W - wt[n], n - 1, M) + val[n];
	}
	// not select
	int y = KnapsackMemoization(wt, val, W, n - 1, M);

	M[W][n] = y > x ? y : x;

	return M[W][n];
}

void Knapsack01::ExecuteTabulation(int* wt, int* val, int W, int n)
{
	int** M = new int* [W + 1];
	for (int i = 0; i <= W; i++)
	{
		M[i] = new int[n + 1] {0};
	}

	int sel;
	for (int w = 1; w <= W; w++)
	{
		for (int i = 1; i <= n; i++)
		{
			if (wt[i - 1] <= w)
			{
				sel = M[w - wt[i - 1]][i - 1] + val[i - 1];
				M[w][i] = M[w][i - 1] > sel ? M[w][i - 1] : sel;
			}
			else {
				M[w][i] = M[w][i - 1];
			}
		}
	}

	std::cout << "maximum profit is => " << M[W][n];
	PrintSelectedItems(M, wt, W, n);

	// --- طباعة المصفوفة M ---
// --- طباعة المصفوفة M ---
	std::cout << "\n\n--- DP Matrix (M) ---\n";
	for (int i = 0; i <= W; i++)
	{
		for (int j = 0; j <= n; j++)
		{
			// استخدام \t لتنسيق المسافات بين الأعمدة بشكل مرتب
			std::cout << M[i][j] << "\t";
		}
		std::cout << "\n";
	}
	std::cout << "---------------------\n\n";



	for (int i = 0; i <= W; i++)
		delete[] M[i];
	delete[] M;
}

void Knapsack01::PrintSelectedItems(int** M, int* wt, int W, int n)
{
	bool* sel = new bool[n + 1] {false};

	int w = W, i = n;
	while (w > 0 && i > 0)
	{
		if (M[w][i - 1] != M[w][i])
		{
			sel[i] = true;
			w -= wt[i - 1];
		}
		i--;
	}
	std::cout << "\n{";
	for (int i = 1; i <= n; i++)
	{
		std::cout << sel[i];
		if (i != n)
			std::cout << ", ";
	}
	std::cout << "}\n";
	delete[] sel;
}

void Knapsack01::TestBehavior()
{
	std::cout << "========== Test Case 1 (Standard) ==========\n";
	int val1[] = { 6, 5, 3, 8 };
	int wt1[] = { 1,2,1,2 };
	int W1 = 5;
	int n1 = 4;

	std::cout << "[ Recursion ] ";
	Knapsack01::ExecuteRecursion(wt1, val1, W1, n1);
	std::cout << "\n";

	std::cout << "[ Memoization ] ";
	Knapsack01::ExecuteMemoization(wt1, val1, W1, n1);
	std::cout << "\n";

	std::cout << "[ Tabulation ] ";
	Knapsack01::ExecuteTabulation(wt1, val1, W1, n1);
	std::cout << "\n";



	std::cout << "============================================\n";
}