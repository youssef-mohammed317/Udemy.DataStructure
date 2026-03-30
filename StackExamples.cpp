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
bool StackExamples::IsEqualOrHigherPriority(const char c1, const char c2)
{
	return ((c1 == '+' || c1 == '-') && (c2 == '+' || c2 == '-'))
		|| ((c1 == '*' || c1 == '/') && (c2 == '*' || c2 == '/'))
		|| ((c1 == '*' || c1 == '/') && (c2 == '+' || c2 == '-'));

}
bool StackExamples::IsOperator(const char c)
{
	return (c == '+' || c == '-' || c == '*' || c == '/');
}

string StackExamples::InfixToPostfix(const char* exp)
{

	string result = "";
	Stack s = Stack();
	char out, in;
	for (int i = 0; exp[i] != '\0'; i++)
	{
		out = exp[i];

		if (IsOperator(out))
		{
			if (!s.IsEmpty())
			{
				in = s.Top();
				if (IsEqualOrHigherPriority(in, out))
				{
					result += in;
					s.Pop();
					i--;
				}
				else
				{
					s.Push(out);
				}
			}
			else
			{
				s.Push(out);
			}
		}
		else
		{
			result += out;
		}
	}
	while (!s.IsEmpty())
	{
		result += s.Top();
		s.Pop();
	}
	return result;
}



void StackExamples::TestBehavior()
{
	char test1[] = "a+b*c-d/e";
	cout << "Test 1" << endl;
	cout << "Infix    : " << test1 << endl;
	cout << "Expected : abc*+de/-" << endl;
	cout << "Actual   : " << InfixToPostfix(test1) << endl;
	cout << endl;

	char test2[] = "a*b+c/d-e";
	cout << "Test 2" << endl;
	cout << "Infix    : " << test2 << endl;
	cout << "Expected : ab*cd/+e-" << endl;
	cout << "Actual   : " << InfixToPostfix(test2) << endl;
	cout << endl;

	char test3[] = "a+b*c/d-e*f";
	cout << "Test 3" << endl;
	cout << "Infix    : " << test3 << endl;
	cout << "Expected : abc*d/+ef*-" << endl;
	cout << "Actual   : " << InfixToPostfix(test3) << endl;
	cout << endl;

	char test4[] = "a*b-c+d/e";
	cout << "Test 4" << endl;
	cout << "Infix    : " << test4 << endl;
	cout << "Expected : ab*c-de/+" << endl;
	cout << "Actual   : " << InfixToPostfix(test4) << endl;
	cout << endl;

	char test5[] = "a+b-c*d/e+f";
	cout << "Test 5" << endl;
	cout << "Infix    : " << test5 << endl;
	cout << "Expected : ab+cd*e/-f+" << endl;
	cout << "Actual   : " << InfixToPostfix(test5) << endl;
	cout << endl;

	char test6[] = "a*b/c+d-e*f";
	cout << "Test 6" << endl;
	cout << "Infix    : " << test6 << endl;
	cout << "Expected : ab*c/d+ef*-" << endl;
	cout << "Actual   : " << InfixToPostfix(test6) << endl;
	cout << endl;

	char test7[] = "a+b*c-d/e+f*g";
	cout << "Test 7" << endl;
	cout << "Infix    : " << test7 << endl;
	cout << "Expected : abc*+de/-fg*+" << endl;
	cout << "Actual   : " << InfixToPostfix(test7) << endl;
	cout << endl;
}