#include "StackExamples.h"

bool StackExamples::ParenthesisMatching(const char* exp)
{
	Stack s = Stack();
	char c, z;
	for (int i = 0; exp[i] != '\0'; i++)
	{
		c = exp[i];
		if (c == '(' || c == '[' || c == '{')
		{
			s.Push(c);
		}
		if (c == ')' || c == ']' || c == '}')
		{
			if (s.IsEmpty())
				return false;

			z = s.Top();
			s.Pop();

			if (z == '(' && c != ')' ||
				z == '[' && c != ']' ||
				z == '{' && c != '}')
				return false;

		}
	}

	return s.IsEmpty();
}
void StackExamples::TestBehavior()
{
	struct TestCase
	{
		const char* exp;
		bool expected;
	};

	TestCase tests[] =
	{
		{"()", true},
		{"[]", true},
		{"{}", true},
		{"()[]{}", true},
		{"({[]})", true},
		{"a+b*(c-d)", true},
		{"[a+(b*c)-{d/e}]", true},
		{"(", false},
		{")", false},
		{"(]", false},
		{"([)]", false},
		{"{[()]}", true},
		{"{[(])}", false},
		{"((()))", true},
		{"(()", false},
		{"())", false},
		{"", true}
	};

	int count = sizeof(tests) / sizeof(tests[0]);
	int passedCount = 0;

	std::cout << "===== ParenthesisMatching Test Start =====\n\n";

	for (int i = 0; i < count; i++)
	{
		bool actual = ParenthesisMatching(tests[i].exp);
		bool passed = (actual == tests[i].expected);

		std::cout << "Test " << i + 1 << ": \"" << tests[i].exp << "\"\n";
		std::cout << "Expected: " << (tests[i].expected ? "Valid" : "Invalid") << "\n";
		std::cout << "Actual  : " << (actual ? "Valid" : "Invalid") << "\n";
		std::cout << "Result  : " << (passed ? "PASSED" : "FAILED") << "\n";
		std::cout << "-----------------------------\n";

		if (passed)
			passedCount++;
	}

	std::cout << "\nSummary: " << passedCount << "/" << count << " tests passed.\n";
	std::cout << "===== ParenthesisMatching Test End =====\n";
}