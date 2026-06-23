#include "MatrixChainMultiplication.h"

// 1-Recursion
void MatrixChainMultiplication::ExecuteRecursion(int* p, int n)
{
	if (n < 1)
	{
		std::cout << "invalid input";
		return;
	}

	std::cout << "Min cost => " << MCMRecursion(p, 1, n); // n number of Matrcise not the size of p
}

int MatrixChainMultiplication::MCMRecursion(int* p, int i, int j)
{
	if (i == j)
		return 0;

	int minCost = INT_MAX;
	for (int k = i; k < j; k++)
	{
		int	cost = MCMRecursion(p, i, k) + MCMRecursion(p, k + 1, j) + p[i - 1] * p[k] * p[j];
		if (cost < minCost)
		{
			minCost = cost;
		}
	}

	return minCost;
}

// 2-Memoization
void MatrixChainMultiplication::ExecuteMemoization(int* p, int n)
{
	if (n < 1)
	{
		std::cout << "invalid input";
		return;
	}

	int** M = new int* [n + 1];
	for (int i = 0; i <= n; i++)
	{
		M[i] = new int[n + 1];
		for (int j = 0; j <= n; j++)
			M[i][j] = -1;
	}

	MCMMemoization(p, 1, n, M);// n number of Matrcise not the size of p

	std::cout << "Min cost => " << M[1][n];

	for (int i = 0; i <= n; i++)
		delete[] M[i];
	delete[] M;
}

int MatrixChainMultiplication::MCMMemoization(int* p, int i, int j, int** M)
{
	if (M[i][j] != -1)
		return M[i][j];

	if (i == j)
	{
		M[i][j] = 0;
	}
	else {
		int minCost = INT_MAX;
		for (int k = i; k < j; k++)
		{
			int	cost = MCMMemoization(p, i, k, M) + MCMMemoization(p, k + 1, j, M) + p[i - 1] * p[k] * p[j];
			if (cost < minCost)
			{
				minCost = cost;
			}
		}
		M[i][j] = minCost;
	}
	return M[i][j];
}

void MatrixChainMultiplication::ExecuteTabulation(int* p, int n)
{
	if (n < 1)
	{
		std::cout << "invalid input";
		return;
	}

	int** M = new int* [n + 1];
	int** bracket = new int* [n + 1];
	for (int i = 0; i <= n; i++)
	{
		M[i] = new int[n + 1] {0};
		bracket[i] = new int[n + 1] {0};
	}

	int minCost, cost;
	for (int c = 2; c <= n; c++) // move Diagonally
	{
		for (int i = 1, j = c; i < n && j <= n; i++, j++)
		{
			minCost = INT_MAX;
			for (int k = i; k < j; k++)
			{
				cost = M[i][k] + M[k + 1][j] + p[i - 1] * p[k] * p[j];
				if (cost < minCost)
				{
					minCost = cost;
					bracket[i][j] = k;
				}
			}
			M[i][j] = minCost;
		}
	}

	std::cout << "Min cost => " << M[1][n];

	std::cout << "Optimal Parenthesization => ";
	char name = 'A';
	PrintOptimalParens(1, n, bracket, name);


	for (int i = 0; i <= n; i++)
	{
		delete[] M[i];
		delete[] bracket[i];
	}
	delete[] M;
	delete[] bracket;
}

void MatrixChainMultiplication::PrintOptimalParens(int i, int j, int** bracket, char& name)
{
	if (i == j)
	{
		std::cout << name++;
		return;
	}

	std::cout << "(";

	PrintOptimalParens(i, bracket[i][j], bracket, name);

	PrintOptimalParens(bracket[i][j] + 1, j, bracket, name);

	std::cout << ")";
}