#pragma once
#include<iostream>
using namespace std;
class PolynomialTerm
{
private:
	int exp;
	int coff;
public:
	PolynomialTerm(int coff = 1, int exp = 0);
	~PolynomialTerm();

	int GetExp();
	int GetCoff();

	void SetCoff(int coff = 1);
};

class Polynomial
{
private:
	PolynomialTerm* polynomialTerms;
	int NoOfTerms;
	int CapacityOfTerms;
	void ThrowIfFull();
	int Power(int base, int exp);
public:
	Polynomial(int CapacityOfTerms = 0);
	~Polynomial();

	void AddTerm(int coff = 1, int exp = 0);
	int GetTermCoff(int exp);


	int Calc(int val);
	void Display();
	static void TestBehavior();

	Polynomial operator+(const Polynomial& other) const;
};


