#pragma once
#include "PolynomialNode.h"
#include <iostream>
#include <stdexcept>

using namespace std;
class PolynomialByLinkedList
{

	PolynomialNode* head;
	PolynomialNode* tail;
	int length;
	void ThrowIfFull();
public:
	PolynomialByLinkedList();
	PolynomialByLinkedList(const PolynomialByLinkedList& other);
	~PolynomialByLinkedList();
	void Clear();

	void AddTerm(double coeff, int power);
	int GetTermCoeff(int power);

	double Calc(double val);
	void Display();

	static void TestBehavior();

	PolynomialByLinkedList operator+(const PolynomialByLinkedList& s) const;

};

