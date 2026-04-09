#pragma once
class PolynomialNode
{
	int coeff;
	int power;
	PolynomialNode* next;
public:
	PolynomialNode(double coeff, int power, PolynomialNode* next = nullptr);
	~PolynomialNode();

	void SetCoeff(double coeff);
	void SetPower(int power);
	void SetNext(PolynomialNode* next);
	double GetCoeff();
	int GetPower();
	PolynomialNode* GetNext();
	double Calc(double value);
};

