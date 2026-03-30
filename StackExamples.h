#pragma once
#include "Stack.h"
#include<string>
#include<cmath>
#include<iostream>
using namespace std;
class StackExamples
{
	static bool IsEqualPriority(const char in, const char out);
	static bool IsHigherPriority(const char in, const char out);
	static int Calc(const int c1, const int c2, const char op);
	static bool IsEqualOrHigherPriority(const char in, const char out);
	static bool IsOperator(char c);
	static bool IsDigit(char c);
public:
	static bool ParenthesisMatching(const char* exp);

	static string InfixToPostfix(const char* exp);
	static string AdvancdInfixToPostfix(const char* exp);
	static int EvaluatePostfix(const char* exp);

	static void TestBehavior();
};

