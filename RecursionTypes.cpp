#include "RecursionTypes.h"
void RecursionTypes::TestTailRecursion(int n)// output: n, n-1, n-2...3, 2, 1, 0
{
	if (n >= 0)
	{
		cout << n << " ";
		TestTailRecursion(n - 1);
	}
}
void RecursionTypes::TestHeadRecursion(int n) 	// output: 0, 1, 2, 3...n-1, n
{
	if (n >= 0)
	{
		TestHeadRecursion(n - 1);
		cout << n << " ";

	}
}
void RecursionTypes::TestTreeRecursion(int n)	// output: 3, 2, 1, 0, 0, 1, 0, 0, 2, 1, 0, 0, 1, 0, 0
{
	if (n >= 0)
	{
		cout << n << " ";

		TestTreeRecursion(n - 1);
		TestTreeRecursion(n - 1);
	}
}

void RecursionTypes::TestInDirectRecursionA(int n) // output: A B A
{
	if (n != 0)
	{
		cout << "A ";
		return TestInDirectRecursionB(n - 1);
	}
}
void RecursionTypes::TestInDirectRecursionB(int n) // output: B A B
{
	if (n != 0)
	{
		cout << "B ";
		return TestInDirectRecursionA(n - 1);
	}
}


int RecursionTypes::TestNestedRecursion(int n)	// for n = 80 return: 91
{
	if (n > 100)
		return n - 10;
	return TestNestedRecursion(TestNestedRecursion(n + 11));
}

void RecursionTypes::TestBehavior()
{
	cout << "========== Recursion Types TestBehavior ==========\n\n";

	cout << "1) Tail Recursion\n";
	cout << "Expected: 5 4 3 2 1 0\n";
	cout << "Actual:   ";
	TestTailRecursion(5);
	cout << "\n\n";

	cout << "2) Head Recursion\n";
	cout << "Expected: 0 1 2 3 4 5\n";
	cout << "Actual:   ";
	TestHeadRecursion(5);
	cout << "\n\n";

	cout << "3) Tree Recursion\n";
	cout << "Expected order for n = 3:\n";
	cout << "3 2 1 0 0 1 0 0 2 1 0 0 1 0 0\n";
	cout << "Actual:   ";
	TestTreeRecursion(3);
	cout << "\n\n";

	cout << "4) Indirect Recursion starting with A\n";
	cout << "Expected: A B A\n";
	cout << "Actual:   ";
	TestInDirectRecursionA(3);
	cout << "\n\n";

	cout << "5) Indirect Recursion starting with B\n";
	cout << "Expected: B A B\n";
	cout << "Actual:   ";
	TestInDirectRecursionB(3);
	cout << "\n\n";

	cout << "6) Nested Recursion\n";
	cout << "TestNestedRecursion(80)  = " << TestNestedRecursion(80) << "   expected: 91\n";
	cout << "TestNestedRecursion(95)  = " << TestNestedRecursion(95) << "   expected: 91\n";
	cout << "TestNestedRecursion(101) = " << TestNestedRecursion(101) << "   expected: 91\n";
	cout << "TestNestedRecursion(120) = " << TestNestedRecursion(120) << "   expected: 110\n";

	cout << "\n==================================================\n";
}