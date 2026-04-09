#include "PolynomialNode.h"
#include <cmath> // Required for std::pow

// --- Constructor & Destructor ---

PolynomialNode::PolynomialNode(double coeff, int power, PolynomialNode* next) {
	this->coeff = coeff;
	this->power = power;
	this->next = next;
}

PolynomialNode::~PolynomialNode() {
	// Nothing to delete dynamically here
}

// --- Setters ---

void PolynomialNode::SetCoeff(double coeff) {
	this->coeff = coeff;
}

void PolynomialNode::SetPower(int power) {
	this->power = power;
}
void PolynomialNode::SetNext(PolynomialNode* next) {
	this->next = next;
}

// --- Getters ---

double PolynomialNode::GetCoeff() {
	return coeff;
}

int PolynomialNode::GetPower() {
	return power;
}
PolynomialNode* PolynomialNode::GetNext() {
	return next;
}

// --- Core Functionality ---

double PolynomialNode::Calc(double value) {
	// Calculates: coeff * (value ^ power)
	return coeff * std::pow(value, power);
}