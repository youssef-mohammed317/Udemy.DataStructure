#include "NQueensProblem.h"

void NQueensProblem::Execute(int n)
{
	if (n < 1)
	{

		std::cout << "Invalid input";
		return;
	}

	int** Q = new int* [n + 1];
	for (int i = 1; i <= n; i++)
		Q[i] = new int[n + 1] {0};


	NQueans(Q, n, 1);

	for (int i = 1; i <= n; i++)
		delete[]Q[i];
	delete[]Q;
}

void NQueensProblem::NQueans(int** Q, int n, int k)
{
	if (k == n + 1)
	{
		Print(Q, n);
		return;
	}

	for (int i = 1; i <= n; i++)
	{
		if (isValid(Q, n, k, i))
		{
			Q[k][i] = 1;
			NQueans(Q, n, k + 1);
			Q[k][i] = 0;
		}
	}
}

bool NQueensProblem::isValid(int** Q, int n, int k, int l)
{
	// O(k)
	// same col
	for (int i = 1; i < k; i++)
	{
		if (Q[i][l] == 1)
			return false;
	}

	// main diagonal
	for (int i = k - 1, j = l + 1; i >= 1 && j <= n; j++, i--)
	{
		if (Q[i][j] == 1)
			return false;
	}
	// cross diagonal
	for (int i = k - 1, j = l - 1; i >= 1 && j >= 1; j--, i--)
	{

		if (Q[i][j] == 1)
			return false;
	}

	// O(mxn)

	//for (int i = 1; i < k; i++)
	//{
	//	for (int j = 1; j <= n; j++)
	//	{
	//		if (Q[i][j] == 1)
	//		{
	//			if (j == l) // same col
	//				return false;
	//			if (k + l == j + i) // same cross diagonal 
	//				return false;
	//			if (i - j == k - l) // same main diagonal
	//				return false;
	//			// abs(i-k) == abs(j-l) // both diagonals in one condition
	//		}
	//	}
	//}
	return true;
}
void NQueensProblem::Print(int** Q, int n)
{
	std::cout << "\n=====================================================\n";
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			std::cout << Q[i][j] << " ";
		}
		std::cout << "\n";
	}
	std::cout << "\n=====================================================\n";
}