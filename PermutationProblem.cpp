#include "PermutationProblem.h"

void PermutationProblem::Execute(char* str)
{
	int n = 0;
	while (str[n] != '\0')
		n++;

	bool* sel = new bool[n] {false};
	char* res = new char[n + 1];
	res[n] = '\0';

	Perm(str, sel, res, n, 0);

	delete[]res;
	delete[]sel;
}

void PermutationProblem::Perm(char* str, bool* sel, char* res, int n, int k)
{
	if (k == n)
	{
		Print(res);
		return;
	}
	for (int i = 0; i < n; i++)
	{


		if (!sel[i])
		{
			// bounded condition
			if (k > 0 && str[i] - res[k - 1] == 1)
				continue;
			sel[i] = true;
			res[k] = str[i];
			Perm(str, sel, res, n, k + 1);
			sel[i] = false;
		}
	}
}
void PermutationProblem::Print(char* res)
{
	std::cout << res << "\n";
}