#include "Polynomial.h"
#include<stdexcept>
PolynomialTerm::PolynomialTerm(int coff, int exp)
{
	if (exp < 0)
	{
		throw std::logic_error("cant create a poly term with negative exp");
	}
	this->exp = exp;
	this->coff = coff;
}
PolynomialTerm::~PolynomialTerm()
{}

void PolynomialTerm::SetCoff(int coff)
{
	this->coff = coff;
}
int PolynomialTerm::GetCoff()
{
	return this->coff;
}
int PolynomialTerm::GetExp()
{
	return this->exp;
}


Polynomial::Polynomial(int CapacityOfTerms)
{
	if (CapacityOfTerms < 0)
	{
		throw std::logic_error("cant create a poly with negative no of terms");
	}

	this->CapacityOfTerms = CapacityOfTerms;
	this->NoOfTerms = 0;

	this->polynomialTerms = new PolynomialTerm[CapacityOfTerms];

}

Polynomial::~Polynomial()
{
	delete[] this->polynomialTerms;
}
void Polynomial::ThrowIfFull()
{
	if (CapacityOfTerms == NoOfTerms)
		throw std::out_of_range("the polynomial is full");
}
int Polynomial::Power(int base, int exp)
{
	int result = 1;
	for (int i = 0; i < exp; i++)
		result *= base;
	return result;
}

void Polynomial::AddTerm(int coff, int exp)
{
	if (exp < 0)
		throw logic_error("negative exponent is not allowed");

	if (coff == 0)
		return;

	int pos = 0;

	while (pos < NoOfTerms && polynomialTerms[pos].GetExp() > exp)
		pos++;

	if (pos < NoOfTerms && polynomialTerms[pos].GetExp() == exp)
	{
		int newCoff = polynomialTerms[pos].GetCoff() + coff;
		if (newCoff == 0)
		{
			for (int i = pos; i < NoOfTerms - 1; i++)
			{
				polynomialTerms[i] = polynomialTerms[i + 1];
			}
			NoOfTerms--;
		}
		else {
			polynomialTerms[pos].SetCoff(newCoff);
		}
		return;
	}
	else {

		ThrowIfFull();

		for (int j = NoOfTerms; j > pos; j--)
		{
			polynomialTerms[j] = polynomialTerms[j - 1];
		}
		polynomialTerms[pos] = PolynomialTerm(coff, exp);
		NoOfTerms++;
		return;
	}
}

int Polynomial::GetTermCoff(int exp)
{
	for (int i = 0; i < NoOfTerms; i++)
	{
		if (polynomialTerms[i].GetExp() == exp)
		{
			return polynomialTerms[i].GetCoff();
		}
	}
	return 0;
}

int Polynomial::Calc(int val)
{
	int sum = 0;
	for (int i = 0; i < NoOfTerms; i++)
	{
		sum += polynomialTerms[i].GetCoff() * Power(val, polynomialTerms[i].GetExp());
	}
	return sum;
}

void Polynomial::Display()
{
	if (NoOfTerms == 0)
	{
		cout << "0";
		return;
	}

	for (int i = 0; i < NoOfTerms; i++)
	{
		int coff = polynomialTerms[i].GetCoff();
		int exp = polynomialTerms[i].GetExp();
		int absCoff = (coff < 0 ? -coff : coff);

		if (i == 0)
		{
			if (coff < 0)
			{
				cout << "-";
			}
		}
		else {
			if (coff < 0)
			{
				cout << " - ";
			}
			else {
				cout << " + ";
			}
		}


		if (exp == 0)
		{
			cout << absCoff;
		}
		else {
			if (absCoff != 1)
			{
				cout << absCoff;
			}
			cout << "x";
			if (exp != 1)
			{
				cout << "^" << exp;
			}
		}




	}



}


Polynomial Polynomial::operator+(const Polynomial& other) const
{
	int j = 0, i = 0;
	Polynomial result = Polynomial(this->NoOfTerms + other.NoOfTerms);
	while (j < other.NoOfTerms && i < this->NoOfTerms)
	{
		int exp1 = this->polynomialTerms[i].GetExp();
		int exp2 = other.polynomialTerms[j].GetExp();

		if (exp1 == exp2)
		{
			int c = this->polynomialTerms[i].GetCoff() + other.polynomialTerms[j].GetCoff();
			if (c != 0)
				result.AddTerm(c, exp1);

			i++;
			j++;
		}
		else if (exp1 > exp2)
		{
			result.AddTerm(this->polynomialTerms[i].GetCoff(), exp1);
			i++;
		}
		else
		{
			result.AddTerm(other.polynomialTerms[j].GetCoff(), exp2);
			j++;
		}

	}

	while (i < this->NoOfTerms)
	{
		result.AddTerm(this->polynomialTerms[i].GetCoff(),
			this->polynomialTerms[i].GetExp());
		i++;
	}

	while (j < other.NoOfTerms)
	{
		result.AddTerm(other.polynomialTerms[j].GetCoff(),
			other.polynomialTerms[j].GetExp());
		j++;
	}
	return result;
}



void Polynomial::TestBehavior()
{
	cout << "========== Polynomial TestBehavior ==========\n\n";

	cout << "1) Empty polynomial\n";
	Polynomial p0(5);
	cout << "Expected: 0\nActual:   ";
	p0.Display();
	cout << "\nCalc(2) = " << p0.Calc(2) << "   expected: 0\n";
	cout << "GetTermCoff(7) = " << p0.GetTermCoff(7) << "   expected: 0\n\n";

	cout << "---------------------------------------------\n";
	cout << "2) Add terms in random order\n";
	Polynomial p1(10);
	p1.AddTerm(3, 2);
	p1.AddTerm(5, 5);
	p1.AddTerm(-2, 1);
	p1.AddTerm(7, 0);

	cout << "Expected: 5x^5 + 3x^2 - 2x + 7\nActual:   ";
	p1.Display();
	cout << "\n\n";

	cout << "---------------------------------------------\n";
	cout << "3) Add same exponent -> must merge coefficients\n";
	p1.AddTerm(4, 2); // 3x^2 + 4x^2 = 7x^2

	cout << "Expected: 5x^5 + 7x^2 - 2x + 7\nActual:   ";
	p1.Display();
	cout << "\n\n";

	cout << "---------------------------------------------\n";
	cout << "4) Add same exponent and become zero -> term deleted\n";
	p1.AddTerm(-7, 2); // 7x^2 - 7x^2 = 0

	cout << "Expected: 5x^5 - 2x + 7\nActual:   ";
	p1.Display();
	cout << "\n\n";

	cout << "---------------------------------------------\n";
	cout << "5) Add zero coefficient -> should do nothing\n";
	p1.AddTerm(0, 100);

	cout << "Expected: 5x^5 - 2x + 7\nActual:   ";
	p1.Display();
	cout << "\n\n";

	cout << "---------------------------------------------\n";
	cout << "6) GetTermCoff tests\n";
	cout << "GetTermCoff(5) = " << p1.GetTermCoff(5) << "   expected: 5\n";
	cout << "GetTermCoff(2) = " << p1.GetTermCoff(2) << "   expected: 0\n";
	cout << "GetTermCoff(1) = " << p1.GetTermCoff(1) << "   expected: -2\n";
	cout << "GetTermCoff(0) = " << p1.GetTermCoff(0) << "   expected: 7\n\n";

	cout << "---------------------------------------------\n";
	cout << "7) Calc test\n";
	cout << "Polynomial: ";
	p1.Display();
	cout << "\nCalc(2) = " << p1.Calc(2) << "   expected: 163\n\n";
	// 5*(2^5) - 2*(2^1) + 7 = 160 - 4 + 7 = 163

	cout << "---------------------------------------------\n";
	cout << "8) Full polynomial behavior\n";
	Polynomial p2(2);
	p2.AddTerm(1, 3);   // x^3
	p2.AddTerm(2, 1);   // 2x

	cout << "Initial full polynomial: ";
	p2.Display();
	cout << "\n";

	try
	{
		cout << "AddTerm(5, 1) on full polynomial with existing exp\n";
		p2.AddTerm(5, 1); // should update existing term, not throw
		cout << "No exception thrown (correct)\n";
		cout << "After update: ";
		p2.Display();
		cout << "   expected: x^3 + 7x\n";
	}
	catch (exception& ex)
	{
		cout << "Unexpected exception: " << ex.what() << "\n";
	}

	try
	{
		cout << "\nAddTerm(9, 0) on full polynomial with NEW exp\n";
		p2.AddTerm(9, 0); // should throw
		cout << "ERROR: exception was expected but not thrown\n";
	}
	catch (exception& ex)
	{
		cout << "Caught expected exception: " << ex.what() << "\n";
	}

	cout << "\n";

	cout << "---------------------------------------------\n";
	cout << "9) Negative exponent test\n";
	try
	{
		p2.AddTerm(4, -1);
		cout << "ERROR: exception was expected but not thrown\n";
	}
	catch (exception& ex)
	{
		cout << "Caught expected exception: " << ex.what() << "\n";
	}

	try
	{
		Polynomial bad(-1);
		cout << "ERROR: exception was expected but not thrown\n";
	}
	catch (exception& ex)
	{
		cout << "Caught expected exception: " << ex.what() << "\n";
	}

	cout << "\n";

	cout << "---------------------------------------------\n";
	cout << "10) operator+ test\n";

	Polynomial a(5);
	a.AddTerm(3, 4);
	a.AddTerm(2, 2);
	a.AddTerm(-1, 0);

	Polynomial b(5);
	b.AddTerm(5, 3);
	b.AddTerm(-2, 2);
	b.AddTerm(8, 0);

	cout << "A = ";
	a.Display();
	cout << "\n";

	cout << "B = ";
	b.Display();
	cout << "\n";

	Polynomial sum = a + b;

	cout << "A + B = ";
	sum.Display();
	cout << "\nExpected: 3x^4 + 5x^3 + 7\n\n";

	cout << "---------------------------------------------\n";
	cout << "11) Add with empty polynomial\n";
	Polynomial empty(3);
	Polynomial sum2 = a + empty;

	cout << "A = ";
	a.Display();
	cout << "\nEmpty = ";
	empty.Display();
	cout << "\nA + Empty = ";
	sum2.Display();
	cout << "\nExpected same as A\n\n";

	cout << "========== End of TestBehavior ==========\n";
}
