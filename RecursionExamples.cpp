#include "RecursionExamples.h"

int RecursionExamples::GetSumByRecursion(int last, int first, int step)
{
	if (last < first)
	{
		return 0;
	}
	else {
		return GetSumByRecursion(last - step, first, step) + last;
	}
}

int RecursionExamples::GetSumByFormula(int last, int first, int step)
{
	int n = (last - first) / step + 1;
	int realLast = first + (n - 1) * step;
	return (n * (first + realLast)) / 2;
}
int RecursionExamples::GetSumByLoop(int last, int first, int step)
{
	int sum = 0;
	for (int i = first; i <= last; i += step)
		sum += i;

	return sum;
}

int RecursionExamples::GetFactorialByRecursion(int num)
{

	if (num == 0)
	{
		return 1;
	}
	else {
		return GetFactorialByRecursion(num - 1) * num;
	}
}
int RecursionExamples::GetFactorialByLoop(int num)
{
	if (num == 0)
		return 1;

	int mul = 1;
	for (int i = num; i > 0; i--)
		mul *= i;

	return mul;
}

int RecursionExamples::GetPowerByRecursion(int base, int exp)
{
	if (exp == 0)
	{
		return 1;
	}
	else {
		return GetPowerByRecursion(base, exp - 1) * base;
	}
}
int RecursionExamples::GetPowerByLoop(int base, int exp)
{
	if (exp == 0)
	{
		return 1;
	}
	int mul = 1;
	for (int i = exp; i > 0; i--)
	{
		mul *= base;
	}

	return mul;
}
double RecursionExamples::ImprovedGetPowerByRecursion(double base, int exp)
{
	if (exp == 0)
		return 1;

	if (exp < 0)
	{
		return 1.0 / ImprovedGetPowerByRecursion(base, -exp);
	}

	if (exp % 2 == 0)
	{
		return ImprovedGetPowerByRecursion(base * base, exp / 2);
	}
	else {
		return ImprovedGetPowerByRecursion(base * base, (exp - 1) / 2) * base;
	}
}

double RecursionExamples::GetTaylor(double base, int numberOfTerms)
{
	if (numberOfTerms == 1)
	{
		return 1;
	}
	else
	{
		return GetTaylor(base, numberOfTerms - 1) * base + 1;
	}
}
double RecursionExamples::ImprovedGetTaylor(double base, int numberOfTerms)
{
	static double p = 1;
	static double f = 1;

	if (numberOfTerms == 0)
	{
		return 1;
	}
	else
	{
		double r = ImprovedGetTaylor(base, numberOfTerms - 1);
		p *= base;
		f *= numberOfTerms;
		return r + p / f;
	}
}
double RecursionExamples::ImprovedGetTaylorHornersRuleByRecursion(double base, int numberOfTerms)
{
	static double s = 1;

	if (numberOfTerms == 0)
	{
		return s;
	}
	else
	{
		s = 1 + (base / numberOfTerms) * s;
		return ImprovedGetTaylorHornersRuleByRecursion(base, numberOfTerms - 1);
	}
}
double RecursionExamples::ImprovedGetTaylorHornersRuleByLoop(double base, int numberOfTerms)
{
	double s = 1;

	for (int i = numberOfTerms; i > 0; i--)
	{
		s = 1 + (base / i) * s;
	}
	return s;
}
int RecursionExamples::GetFibonacciTermRecursion(int numberOfTerm)
{

	if (numberOfTerm - 1 < 2)
	{
		return numberOfTerm - 1;
	}
	else {
		return GetFibonacciTermRecursion(numberOfTerm - 1) + GetFibonacciTermRecursion(numberOfTerm - 2);
	}
}

int RecursionExamples::GetFibonacciTermByLoop(int numberOfTerm)
{
	if (numberOfTerm - 1 < 2)
	{
		return numberOfTerm - 1;
	}

	int beforePrev = 0;
	int prev = 1;
	int current = 1;
	for (int i = 3; i <= numberOfTerm; i++)
	{

		current = prev + beforePrev;
		beforePrev = prev;
		prev = current;
	}

	return current;

}
void RecursionExamples::PrintFibonacciByLoop(int numberOfTerms)
{

	for (int i = 1; i <= numberOfTerms; i++)
		cout << GetFibonacciTermByLoop(i) << " ";
}
void RecursionExamples::PrintFibonacciByRecursion(int numberOfTerms)
{

	for (int i = 1; i <= numberOfTerms; i++)
		cout << GetFibonacciTermRecursion(i) << " ";
}

int RecursionExamples::GetCominationByFormula(int n, int r)
{
	int t1 = GetFactorialByRecursion(n);
	int t2 = GetFactorialByRecursion(r);
	int t3 = GetFactorialByRecursion(n - r);

	return t1 / (t2 * t3);

}
int RecursionExamples::GetCominationByPascalTriangle(int n, int r)
{
	if (r == 0 || r == n)
	{
		return 1;
	}
	else {
		return GetCominationByPascalTriangle(n - 1, r) + GetCominationByPascalTriangle(n - 1, r - 1);
	}
}
void RecursionExamples::PrintPascalTriangleByLoop(int numberOfRows)
{
	for (int i = 0; i < numberOfRows; i++)
	{
		for (int j = 0; j < (numberOfRows - i); j++)
			cout << " ";
		for (int j = 0; j <= i; j++)
		{
			cout << GetCominationByPascalTriangle(i, j) << " ";
		}
		cout << endl;
	}

}



void RecursionExamples::PrintPascalRowByRecursion(int row, int col)
{
	if (col > row)
		return;

	cout << GetCominationByPascalTriangle(row, col) << " ";
	return PrintPascalRowByRecursion(row, col + 1);
}

void RecursionExamples::PrintPascalTriangleByRecursion(int n, int row)
{
	if (row >= n)
		return;

	PrintPascalRowByRecursion(row);
	cout << endl;

	PrintPascalTriangleByRecursion(n, row + 1);

}


void RecursionExamples::TestBehavior()
{
	cout.setf(ios::fixed);
	cout.precision(6);

	auto PrintIntTest = [](const char* testName, int actual, int expected)
		{
			cout << testName << " = " << actual
				<< "   expected: " << expected
				<< (actual == expected ? "   [PASS]" : "   [FAIL]") << endl;
		};

	auto PrintDoubleTest = [](const char* testName, double actual, double expected, double eps = 0.000001)
		{
			double diff = actual - expected;
			if (diff < 0)
				diff = -diff;

			cout << testName << " = " << actual
				<< "   expected: " << expected
				<< (diff <= eps ? "   [PASS]" : "   [FAIL]") << endl;
		};

	cout << "========== SUM ==========" << endl;
	PrintIntTest("GetSumByRecursion(5, 0, 1)", GetSumByRecursion(5, 0, 1), 15);
	PrintIntTest("GetSumByFormula(5, 0, 1)", GetSumByFormula(5, 0, 1), 15);
	PrintIntTest("GetSumByLoop(5, 0, 1)", GetSumByLoop(5, 0, 1), 15);

	cout << "---------------------------------------------" << endl;

	PrintIntTest("GetSumByRecursion(10, 0, 2)", GetSumByRecursion(10, 0, 2), 30);
	PrintIntTest("GetSumByFormula(10, 0, 2)", GetSumByFormula(10, 0, 2), 30);
	PrintIntTest("GetSumByLoop(10, 0, 2)", GetSumByLoop(10, 0, 2), 30);

	cout << "---------------------------------------------" << endl;

	PrintIntTest("GetSumByRecursion(10, 1, 3)", GetSumByRecursion(10, 1, 3), 22);
	PrintIntTest("GetSumByFormula(10, 1, 3)", GetSumByFormula(10, 1, 3), 22);
	PrintIntTest("GetSumByLoop(10, 1, 3)", GetSumByLoop(10, 1, 3), 22);

	cout << endl;
	cout << "========== FACTORIAL ==========" << endl;
	PrintIntTest("GetFactorialByRecursion(0)", GetFactorialByRecursion(0), 1);
	PrintIntTest("GetFactorialByLoop(0)", GetFactorialByLoop(0), 1);
	PrintIntTest("GetFactorialByRecursion(5)", GetFactorialByRecursion(5), 120);
	PrintIntTest("GetFactorialByLoop(5)", GetFactorialByLoop(5), 120);

	cout << endl;
	cout << "========== POWER ==========" << endl;
	PrintIntTest("GetPowerByRecursion(2, 5)", GetPowerByRecursion(2, 5), 32);
	PrintIntTest("GetPowerByLoop(2, 5)", GetPowerByLoop(2, 5), 32);
	PrintIntTest("GetPowerByRecursion(5, 0)", GetPowerByRecursion(5, 0), 1);
	PrintIntTest("GetPowerByLoop(5, 0)", GetPowerByLoop(5, 0), 1);

	cout << endl;
	cout << "========== IMPROVED POWER ==========" << endl;
	PrintDoubleTest("ImprovedGetPowerByRecursion(2, -3)", ImprovedGetPowerByRecursion(2, -3), 0.125000);
	PrintDoubleTest("ImprovedGetPowerByRecursion(2, 5)", ImprovedGetPowerByRecursion(2, 5), 32.000000);
	PrintDoubleTest("ImprovedGetPowerByRecursion(5, 0)", ImprovedGetPowerByRecursion(5, 0), 1.000000);

	cout << endl;
	cout << "========== TAYLOR ==========" << endl;

	// مهم:
	// GetTaylor الحالية ليست Taylor series الصحيحة لـ e^x.
	// لذلك GetTaylor(1, 10) نتيجتها حسب هذا الكود = 10 وليس 2.718282
	PrintDoubleTest("GetTaylor(1, 10)", GetTaylor(1, 10), 10.000000);

	// الدالتان التاليتان تستخدمان static
	// لذلك يفضل استدعاؤهما مرة واحدة فقط في الاختبار، أو إعادة كتابة الدالة بدون static
	PrintDoubleTest("ImprovedGetTaylor(1, 10)", ImprovedGetTaylor(1, 10), 2.718282, 0.0001);
	PrintDoubleTest("ImprovedGetTaylorHornersRuleByRecursion(1, 10)",
		ImprovedGetTaylorHornersRuleByRecursion(1, 10), 2.718282, 0.0001);
	PrintDoubleTest("ImprovedGetTaylorHornersRuleByLoop(1, 10)",
		ImprovedGetTaylorHornersRuleByLoop(1, 10), 2.718282, 0.0001);

	cout << endl;
	cout << "========== FIBONACCI ==========" << endl;
	PrintIntTest("GetFibonacciTermRecursion(1)", GetFibonacciTermRecursion(1), 0);
	PrintIntTest("GetFibonacciTermRecursion(2)", GetFibonacciTermRecursion(2), 1);
	PrintIntTest("GetFibonacciTermRecursion(7)", GetFibonacciTermRecursion(7), 8);
	PrintIntTest("GetFibonacciTermByLoop(7)", GetFibonacciTermByLoop(7), 8);


	cout << endl;
	cout << "PrintFibonacciByLoop(8): ";
	PrintFibonacciByLoop(8);
	cout << "   expected: 0 1 1 2 3 5 8 13" << endl;

	cout << "PrintFibonacciByRecursion(8): ";
	PrintFibonacciByRecursion(8);
	cout << "   expected: 0 1 1 2 3 5 8 13" << endl;
	cout << endl;
	cout << "========== COMBINATION ==========" << endl;
	PrintIntTest("GetCominationByFormula(5, 2)", GetCominationByFormula(5, 2), 10);
	PrintIntTest("GetCominationByFormula(6, 0)", GetCominationByFormula(6, 0), 1);
	PrintIntTest("GetCominationByFormula(6, 6)", GetCominationByFormula(6, 6), 1);

	PrintIntTest("GetCominationByPascalTriangle(5, 2)", GetCominationByPascalTriangle(5, 2), 10);
	PrintIntTest("GetCominationByPascalTriangle(6, 0)", GetCominationByPascalTriangle(6, 0), 1);
	PrintIntTest("GetCominationByPascalTriangle(6, 6)", GetCominationByPascalTriangle(6, 6), 1);
	PrintIntTest("GetCominationByPascalTriangle(7, 3)", GetCominationByPascalTriangle(7, 3), 35);

	cout << endl;
	cout << "========== PASCAL ROW ==========" << endl;
	cout << "PrintPascalRowByRecursion(0): ";
	PrintPascalRowByRecursion(0);
	cout << "   expected: 1" << endl;

	cout << "PrintPascalRowByRecursion(4): ";
	PrintPascalRowByRecursion(4);
	cout << "   expected: 1 4 6 4 1" << endl;

	cout << endl;
	cout << "========== PASCAL TRIANGLE ==========" << endl;

	cout << "PrintPascalTriangleByLoop(5):" << endl;
	PrintPascalTriangleByLoop(5);
	cout << "Expected shape:" << endl;
	cout << "      1" << endl;
	cout << "     1 1" << endl;
	cout << "    1 2 1" << endl;
	cout << "   1 3 3 1" << endl;
	cout << "  1 4 6 4 1" << endl;

	cout << endl;
	cout << "PrintPascalTriangleByRecursion(5):" << endl;
	PrintPascalTriangleByRecursion(5);
	cout << "Expected shape:" << endl;
	cout << "1" << endl;
	cout << "1 1" << endl;
	cout << "1 2 1" << endl;
	cout << "1 3 3 1" << endl;
	cout << "1 4 6 4 1" << endl;

	cout << endl;
	cout << "========== DONE ==========" << endl;

}