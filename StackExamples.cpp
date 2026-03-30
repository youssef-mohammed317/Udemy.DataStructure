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
bool StackExamples::IsEqualOrHigherPriority(const char in, const char out)
{
	return ((in == '+' || in == '-') && (out == '+' || out == '-'))
		|| ((in == '*' || in == '/') && (out == '*' || out == '/'))
		|| ((in == '*' || in == '/') && (out == '+' || out == '-'));

}

bool StackExamples::IsEqualPriority(const char in, const char out)
{
	return ((in == '(') && (out == ')'));

}
bool StackExamples::IsHigherPriority(const char in, const char out)
{
	return
		((in == '+' || in == '-') && (out == '+' || out == '-' || out == ')'))
		||
		((in == '*' || in == '/') && (out == '+' || out == '-' || out == '*' || out == '/' || out == ')'))
		||
		((in == '^' && (out == '+' || out == '-' || out == '/' || out == '*' || out == ')')))
		;
}
bool StackExamples::IsOperator(const char c)
{
	return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == ')' || c == '(');
}
bool StackExamples::IsDigit(const char c)
{
	return (c >= '0' && c <= '9');
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

string StackExamples::AdvancdInfixToPostfix(const char* exp)
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
				if (IsEqualPriority(in, out))
				{
					s.Pop();
				}
				else if (IsHigherPriority(in, out))
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

int StackExamples::Calc(const int c1, const int c2, const char op)
{
	switch (op)
	{
	case '+':
		return c1 + c2;

	case '-':
		return c1 - c2;

	case '*':
		return c1 * c2;

	case '/':
		return c1 / c2;

	case '^':
		return (int)pow(c1, c2);

	default:
		return 0;
	}
}

int StackExamples::EvaluatePostfix(const char* exp)
{
	string postfix = AdvancdInfixToPostfix(exp);
	Stack s = Stack();
	char c;
	int num1, num2, result;
	for (int i = 0; postfix[i] != '\0'; i++)
	{
		c = postfix[i];
		if (IsOperator(c))
		{
			if (s.Size() >= 2)
			{
				num2 = s.Top(); s.Pop();
				num1 = s.Top(); s.Pop();
				result = Calc(num1, num2, c);
				s.Push(result);
			}
			else {
				throw invalid_argument("invalid postfix expression");
			}
		}
		else if (IsDigit(c)) {
			s.Push(c - '0');
		}
		else if (c == ' ')
		{
			continue;
		}
		else
		{
			throw invalid_argument("invalid character in expression");
		}
	}

	return !s.IsEmpty() ? s.Top() : 0;
}

void StackExamples::TestBehavior()
{
	cout << "===============================" << endl;
	cout << " ParenthesisMatching Tests" << endl;
	cout << "===============================" << endl;

	{
		const char* exp = "(a+b)*(c-d)";
		bool expected = true;
		bool actual = ParenthesisMatching(exp);

		cout << "Test 1" << endl;
		cout << "Expression : " << exp << endl;
		cout << "Expected   : " << (expected ? "true" : "false") << endl;
		cout << "Actual     : " << (actual ? "true" : "false") << endl;
		cout << "Result     : " << (expected == actual ? "PASS" : "FAIL") << endl;
		cout << endl;
	}

	{
		const char* exp = "((a+b)*c)";
		bool expected = true;
		bool actual = ParenthesisMatching(exp);

		cout << "Test 2" << endl;
		cout << "Expression : " << exp << endl;
		cout << "Expected   : " << (expected ? "true" : "false") << endl;
		cout << "Actual     : " << (actual ? "true" : "false") << endl;
		cout << "Result     : " << (expected == actual ? "PASS" : "FAIL") << endl;
		cout << endl;
	}

	{
		const char* exp = "{[(a+b)*c]-d}";
		bool expected = true;
		bool actual = ParenthesisMatching(exp);

		cout << "Test 3" << endl;
		cout << "Expression : " << exp << endl;
		cout << "Expected   : " << (expected ? "true" : "false") << endl;
		cout << "Actual     : " << (actual ? "true" : "false") << endl;
		cout << "Result     : " << (expected == actual ? "PASS" : "FAIL") << endl;
		cout << endl;
	}

	{
		const char* exp = "(a+b]*(c-d)";
		bool expected = false;
		bool actual = ParenthesisMatching(exp);

		cout << "Test 4" << endl;
		cout << "Expression : " << exp << endl;
		cout << "Expected   : " << (expected ? "true" : "false") << endl;
		cout << "Actual     : " << (actual ? "true" : "false") << endl;
		cout << "Result     : " << (expected == actual ? "PASS" : "FAIL") << endl;
		cout << endl;
	}

	{
		const char* exp = "((a+b)";
		bool expected = false;
		bool actual = ParenthesisMatching(exp);

		cout << "Test 5" << endl;
		cout << "Expression : " << exp << endl;
		cout << "Expected   : " << (expected ? "true" : "false") << endl;
		cout << "Actual     : " << (actual ? "true" : "false") << endl;
		cout << "Result     : " << (expected == actual ? "PASS" : "FAIL") << endl;
		cout << endl;
	}

	{
		const char* exp = "a+b)";
		bool expected = false;
		bool actual = ParenthesisMatching(exp);

		cout << "Test 6" << endl;
		cout << "Expression : " << exp << endl;
		cout << "Expected   : " << (expected ? "true" : "false") << endl;
		cout << "Actual     : " << (actual ? "true" : "false") << endl;
		cout << "Result     : " << (expected == actual ? "PASS" : "FAIL") << endl;
		cout << endl;
	}


	cout << "===============================" << endl;
	cout << " InfixToPostfix Tests" << endl;
	cout << " (Only +, -, *, /)" << endl;
	cout << "===============================" << endl;

	{
		const char* exp = "a+b*c";
		string expected = "abc*+";
		string actual = InfixToPostfix(exp);

		cout << "Test 1" << endl;
		cout << "Infix      : " << exp << endl;
		cout << "Expected   : " << expected << endl;
		cout << "Actual     : " << actual << endl;
		cout << "Result     : " << (expected == actual ? "PASS" : "FAIL") << endl;
		cout << endl;
	}

	{
		const char* exp = "a*b+c/d";
		string expected = "ab*cd/+";
		string actual = InfixToPostfix(exp);

		cout << "Test 2" << endl;
		cout << "Infix      : " << exp << endl;
		cout << "Expected   : " << expected << endl;
		cout << "Actual     : " << actual << endl;
		cout << "Result     : " << (expected == actual ? "PASS" : "FAIL") << endl;
		cout << endl;
	}

	{
		const char* exp = "a+b*c-d/e";
		string expected = "abc*+de/-";
		string actual = InfixToPostfix(exp);

		cout << "Test 3" << endl;
		cout << "Infix      : " << exp << endl;
		cout << "Expected   : " << expected << endl;
		cout << "Actual     : " << actual << endl;
		cout << "Result     : " << (expected == actual ? "PASS" : "FAIL") << endl;
		cout << endl;
	}

	{
		const char* exp = "a*b/c+d-e";
		string expected = "ab*c/d+e-";
		string actual = InfixToPostfix(exp);

		cout << "Test 4" << endl;
		cout << "Infix      : " << exp << endl;
		cout << "Expected   : " << expected << endl;
		cout << "Actual     : " << actual << endl;
		cout << "Result     : " << (expected == actual ? "PASS" : "FAIL") << endl;
		cout << endl;
	}

	{
		const char* exp = "a+b-c*d/e+f";
		string expected = "ab+cd*e/-f+";
		string actual = InfixToPostfix(exp);

		cout << "Test 5" << endl;
		cout << "Infix      : " << exp << endl;
		cout << "Expected   : " << expected << endl;
		cout << "Actual     : " << actual << endl;
		cout << "Result     : " << (expected == actual ? "PASS" : "FAIL") << endl;
		cout << endl;
	}


	cout << "===============================" << endl;
	cout << " AdvancdInfixToPostfix Tests" << endl;
	cout << " (+, -, *, /, ^, ())" << endl;
	cout << "===============================" << endl;

	{
		const char* exp = "a+b*(c-d)";
		string expected = "abcd-*+";
		string actual = AdvancdInfixToPostfix(exp);

		cout << "Test 1" << endl;
		cout << "Infix      : " << exp << endl;
		cout << "Expected   : " << expected << endl;
		cout << "Actual     : " << actual << endl;
		cout << "Result     : " << (expected == actual ? "PASS" : "FAIL") << endl;
		cout << endl;
	}

	{
		const char* exp = "(a+b)*c";
		string expected = "ab+c*";
		string actual = AdvancdInfixToPostfix(exp);

		cout << "Test 2" << endl;
		cout << "Infix      : " << exp << endl;
		cout << "Expected   : " << expected << endl;
		cout << "Actual     : " << actual << endl;
		cout << "Result     : " << (expected == actual ? "PASS" : "FAIL") << endl;
		cout << endl;
	}

	{
		const char* exp = "a^(b+c)";
		string expected = "abc+^";
		string actual = AdvancdInfixToPostfix(exp);

		cout << "Test 3" << endl;
		cout << "Infix      : " << exp << endl;
		cout << "Expected   : " << expected << endl;
		cout << "Actual     : " << actual << endl;
		cout << "Result     : " << (expected == actual ? "PASS" : "FAIL") << endl;
		cout << endl;
	}

	{
		const char* exp = "(a+b)^c";
		string expected = "ab+c^";
		string actual = AdvancdInfixToPostfix(exp);

		cout << "Test 4" << endl;
		cout << "Infix      : " << exp << endl;
		cout << "Expected   : " << expected << endl;
		cout << "Actual     : " << actual << endl;
		cout << "Result     : " << (expected == actual ? "PASS" : "FAIL") << endl;
		cout << endl;
	}

	{
		const char* exp = "a+b*(c^d-e)";
		string expected = "abcd^e-*+";
		string actual = AdvancdInfixToPostfix(exp);

		cout << "Test 5" << endl;
		cout << "Infix      : " << exp << endl;
		cout << "Expected   : " << expected << endl;
		cout << "Actual     : " << actual << endl;
		cout << "Result     : " << (expected == actual ? "PASS" : "FAIL") << endl;
		cout << endl;
	}

	{
		const char* exp = "(a+b)*(c-d)";
		string expected = "ab+cd-*";
		string actual = AdvancdInfixToPostfix(exp);

		cout << "Test 6" << endl;
		cout << "Infix      : " << exp << endl;
		cout << "Expected   : " << expected << endl;
		cout << "Actual     : " << actual << endl;
		cout << "Result     : " << (expected == actual ? "PASS" : "FAIL") << endl;
		cout << endl;
	}

	{
		const char* exp = "a^b^c";
		string expected = "abc^^";
		string actual = AdvancdInfixToPostfix(exp);

		cout << "Test 7" << endl;
		cout << "Infix      : " << exp << endl;
		cout << "Expected   : " << expected << endl;
		cout << "Actual     : " << actual << endl;
		cout << "Result     : " << (expected == actual ? "PASS" : "FAIL") << endl;
		cout << endl;
	}

	{
		const char* exp = "((a+b)*c)^d";
		string expected = "ab+c*d^";
		string actual = AdvancdInfixToPostfix(exp);

		cout << "Test 8" << endl;
		cout << "Infix      : " << exp << endl;
		cout << "Expected   : " << expected << endl;
		cout << "Actual     : " << actual << endl;
		cout << "Result     : " << (expected == actual ? "PASS" : "FAIL") << endl;
		cout << endl;
	}

	{
		const char* exp = "a+(b*c-(d/e^f)*g)*h";
		string expected = "abc*def^/g*-h*+";
		string actual = AdvancdInfixToPostfix(exp);

		cout << "Test 9" << endl;
		cout << "Infix      : " << exp << endl;
		cout << "Expected   : " << expected << endl;
		cout << "Actual     : " << actual << endl;
		cout << "Result     : " << (expected == actual ? "PASS" : "FAIL") << endl;
		cout << endl;
	}

	{
		const char* exp = "((a+b)^c-d)^(e+f)";
		string expected = "ab+c^d-ef+^";
		string actual = AdvancdInfixToPostfix(exp);

		cout << "Test 10" << endl;
		cout << "Infix      : " << exp << endl;
		cout << "Expected   : " << expected << endl;
		cout << "Actual     : " << actual << endl;
		cout << "Result     : " << (expected == actual ? "PASS" : "FAIL") << endl;
		cout << endl;
	}
	cout << "===============================" << endl;
	cout << " EvaluatePostfix Tests" << endl;
	cout << "===============================" << endl;

	{
		const char* exp = "2+3";
		int expected = 5;
		int actual = EvaluatePostfix(exp);

		cout << "Test 1" << endl;
		cout << "Infix    : " << exp << endl;
		cout << "Expected : " << expected << endl;
		cout << "Actual   : " << actual << endl;
		cout << "Result   : " << (expected == actual ? "PASS" : "FAIL") << endl;
		cout << endl;
	}

	{
		const char* exp = "2+3*4";
		int expected = 14;
		int actual = EvaluatePostfix(exp);

		cout << "Test 2" << endl;
		cout << "Infix    : " << exp << endl;
		cout << "Expected : " << expected << endl;
		cout << "Actual   : " << actual << endl;
		cout << "Result   : " << (expected == actual ? "PASS" : "FAIL") << endl;
		cout << endl;
	}

	{
		const char* exp = "(2+3)*4";
		int expected = 20;
		int actual = EvaluatePostfix(exp);

		cout << "Test 3" << endl;
		cout << "Infix    : " << exp << endl;
		cout << "Expected : " << expected << endl;
		cout << "Actual   : " << actual << endl;
		cout << "Result   : " << (expected == actual ? "PASS" : "FAIL") << endl;
		cout << endl;
	}

	{
		const char* exp = "8/2";
		int expected = 4;
		int actual = EvaluatePostfix(exp);

		cout << "Test 4" << endl;
		cout << "Infix    : " << exp << endl;
		cout << "Expected : " << expected << endl;
		cout << "Actual   : " << actual << endl;
		cout << "Result   : " << (expected == actual ? "PASS" : "FAIL") << endl;
		cout << endl;
	}

	{
		const char* exp = "8-3";
		int expected = 5;
		int actual = EvaluatePostfix(exp);

		cout << "Test 5" << endl;
		cout << "Infix    : " << exp << endl;
		cout << "Expected : " << expected << endl;
		cout << "Actual   : " << actual << endl;
		cout << "Result   : " << (expected == actual ? "PASS" : "FAIL") << endl;
		cout << endl;
	}

	{
		const char* exp = "2^3";
		int expected = 8;
		int actual = EvaluatePostfix(exp);

		cout << "Test 6" << endl;
		cout << "Infix    : " << exp << endl;
		cout << "Expected : " << expected << endl;
		cout << "Actual   : " << actual << endl;
		cout << "Result   : " << (expected == actual ? "PASS" : "FAIL") << endl;
		cout << endl;
	}

	{
		const char* exp = "2^3^2";
		int expected = 512;
		int actual = EvaluatePostfix(exp);

		cout << "Test 7" << endl;
		cout << "Infix    : " << exp << endl;
		cout << "Expected : " << expected << endl;
		cout << "Actual   : " << actual << endl;
		cout << "Result   : " << (expected == actual ? "PASS" : "FAIL") << endl;
		cout << endl;
	}

	{
		const char* exp = "2^(3+1)";
		int expected = 16;
		int actual = EvaluatePostfix(exp);

		cout << "Test 8" << endl;
		cout << "Infix    : " << exp << endl;
		cout << "Expected : " << expected << endl;
		cout << "Actual   : " << actual << endl;
		cout << "Result   : " << (expected == actual ? "PASS" : "FAIL") << endl;
		cout << endl;
	}

	{
		const char* exp = "3+4*2/(1-5)^2";
		int expected = 3;
		int actual = EvaluatePostfix(exp);

		cout << "Test 9" << endl;
		cout << "Infix    : " << exp << endl;
		cout << "Expected : " << expected << endl;
		cout << "Actual   : " << actual << endl;
		cout << "Result   : " << (expected == actual ? "PASS" : "FAIL") << endl;
		cout << endl;
	}

	{
		const char* exp = "9-(5-2)";
		int expected = 6;
		int actual = EvaluatePostfix(exp);

		cout << "Test 10" << endl;
		cout << "Infix    : " << exp << endl;
		cout << "Expected : " << expected << endl;
		cout << "Actual   : " << actual << endl;
		cout << "Result   : " << (expected == actual ? "PASS" : "FAIL") << endl;
		cout << endl;
	}
}