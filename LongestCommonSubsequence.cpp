#include "LongestCommonSubsequence.h"

// 1-Recursion
int LongestCommonSubsequence::ExecuteRecursion(char* str1, char* str2)
{
	int n1 = 0;
	while (str1[n1] != '\0') n1++;

	int n2 = 0;
	while (str2[n2] != '\0') n2++;

	return LCSRecursion(str1, str2, n1 - 1, n2 - 1);// this for '\0' termentation

}

// 1-Recursion
int LongestCommonSubsequence::LCSRecursion(char* str1, char* str2, int i, int j)
{
	if (i < 0 || j < 0)
		return 0;

	if (str1[i] == str2[j])
	{
		return 1 + LCSRecursion(str1, str2, i - 1, j - 1);
	}
	else {

		int x = LCSRecursion(str1, str2, i - 1, j);
		int y = LCSRecursion(str1, str2, i, j - 1);

		return x > y ? x : y;
	}
}

// 2-Memoization
void LongestCommonSubsequence::ExecuteMemoization(char* str1, char* str2)
{
	int n1 = 0;
	while (str1[n1] != '\0') n1++;

	int n2 = 0;
	while (str2[n2] != '\0') n2++;

	if (n1 == 0 || n2 == 0) {
		std::cout << "No Common Sequence";
		return;
	}

	int** L = new int* [n1];
	for (int i = 0; i < n1; i++)
	{
		L[i] = new int[n2];
		for (int j = 0; j < n2; j++)
			L[i][j] = -1;
	}


	LCSMemoization(L, str1, str2, n1 - 1, n2 - 1);

	Print(L, str2, n1, n2);


	// delete L
	for (int i = 0; i < n1; i++)
		delete[] L[i];
	delete[] L;
}

// 2-Memoization
int LongestCommonSubsequence::LCSMemoization(int** L, char* str1, char* str2, int i, int j)
{
	if (i < 0 || j < 0)
		return 0;

	if (L[i][j] != -1) return L[i][j];

	if (str1[i] == str2[j])
	{
		L[i][j] = 1 + LCSMemoization(L, str1, str2, i - 1, j - 1);
	}
	else {

		int x = LCSMemoization(L, str1, str2, i - 1, j);
		int y = LCSMemoization(L, str1, str2, i, j - 1);

		L[i][j] = x > y ? x : y;
	}
	return L[i][j];
}

void LongestCommonSubsequence::Print(int** L, char* str2, int n1, int n2)
{
	if (n1 == 0 || n2 == 0) {
		std::cout << "No Common Sequence";
		return;
	}

	int max = L[n1 - 1][n2 - 1];

	if (max == 0) {
		std::cout << "No Common Sequence";
		return;
	}

	char* res = new char[max + 1];
	res[max] = '\0';

	int k = max - 1;

	int i = n1 - 1, j = n2 - 1;
	while (i > -1 && j > -1 && k > -1)
	{
		int prevCol = j > 0 ? L[i][j - 1] : 0;
		int prevRow = i > 0 ? L[i - 1][j] : 0;

		// check prev cells
		if (L[i][j] == prevCol || L[i][j] == prevRow)
		{
			if (prevCol > prevRow)
			{
				j--;
			}
			else
			{
				i--;
			}
		}
		else {
			res[k--] = str2[j];
			i--;
			j--;
		}
	}
	std::cout << res;
	delete[] res;
}


// 3-Tabulation
void LongestCommonSubsequence::ExecuteTabulation(char* str1, char* str2)
{
	int n1 = 0;
	while (str1[n1] != '\0') n1++;

	int n2 = 0;
	while (str2[n2] != '\0') n2++;

	if (n1 == 0 || n2 == 0) {
		std::cout << "No Common Sequence";
		return;
	}

	int** L = new int* [n1];
	for (int i = 0; i < n1; i++)
	{
		L[i] = new int[n2] {0};
	}

	// prepare L
	for (int i = 0; i < n1; i++)
	{
		for (int j = 0; j < n2; j++)
		{
			if (str1[i] == str2[j])
			{
				L[i][j] = i > 0 && j > 0 ? L[i - 1][j - 1] + 1 : 1;
			}
			else {
				int prevCol = j > 0 ? L[i][j - 1] : 0;
				int prevRow = i > 0 ? L[i - 1][j] : 0;

				L[i][j] = prevCol > prevRow ? prevCol : prevRow;
			}
		}
	}


	Print(L, str2, n1, n2);

	// delete L
	for (int i = 0; i < n1; i++)
		delete[] L[i];
	delete[] L;
}
