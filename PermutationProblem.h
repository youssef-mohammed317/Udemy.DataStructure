#pragma once
#include <iostream>
class PermutationProblem
{
	static void Perm(char* str, bool* sel, char* res, int n, int k);

	static void Print(char* res);

public:
	static void Execute(char* str);
};

