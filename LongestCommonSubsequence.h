#pragma once

#include<iostream>

class LongestCommonSubsequence
{
	// 1-Recursion
	static int LCSRecursion(char* str1, char* str2, int i, int j);
	// 2-Memoization
	static int LCSMemoization(int** L, char* str1, char* str2, int i, int j);

	static void Print(int** L, char* str2, int n1, int n2);

public:
	// 1-Recursion
	static int ExecuteRecursion(char* str1, char* str2);
	// 2-Memoization
	static void ExecuteMemoization(char* str1, char* str2);
	// 3-Tabulation
	static void ExecuteTabulation(char* str1, char* str2);

};

