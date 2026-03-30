#pragma once
#include "Stack.h"
#include<string>
#include<iostream>
using namespace std;
class StackExamples
{
	static bool IsEqualOrHigherPriority(const char c1, const char c2);
	static bool IsOperator(char c);
public:
	static bool ParenthesisMatching(const char* exp);

	static string InfixToPostfix(const char* exp);

	static void TestBehavior();
};

