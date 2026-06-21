#pragma once
#include<iostream>
#include<cmath>

class NQueensProblem
{

	static void NQueans(int** Q, int n, int k);

	static bool isValid(int** Q, int n, int k, int l);

	static void Print(int** Q, int n);

public:
	static void Execute(int n);
};

