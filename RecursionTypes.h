#pragma once
#include<iostream>
using namespace std;
class RecursionTypes
{
public:
	static void TestTailRecursion(int n);	// one time at the end and nothing after it

	static void TestHeadRecursion(int n);	// one time at the first and nothing before it

	static void TestTreeRecursion(int n);	// non-linear(more than one time)

	static void TestInDirectRecursionA(int n);	// Two functions calling each other
	static void TestInDirectRecursionB(int n);	// Two functions calling each other

	static int TestNestedRecursion(int n);	// the parameter is the recusion

	static void TestBehavior();
};

