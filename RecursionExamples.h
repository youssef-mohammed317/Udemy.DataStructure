#pragma once
#include<iostream>
#include <stdexcept>
using namespace std;
class RecursionExamples
{
public:
	static int GetSumByRecursion(int last, int first = 0, int step = 1);// time: O(n), space:(n) 
	static int GetSumByFormula(int last, int first = 0, int step = 1);// time:O(1), space:O(1)
	static int GetSumByLoop(int last, int first = 0, int step = 1);//time:O(n), space:O(1)
	static int GetFactorialByRecursion(int num); //time:O(n), space:O(n)
	static int GetFactorialByLoop(int num); //time:O(n), space:O(1)
	static int  GetPowerByRecursion(int  base = 1, int exp = 0);
	static int  GetPowerByLoop(int  base = 1, int exp = 0);
	static double  ImprovedGetPowerByRecursion(double  base = 1, int exp = 0);
	static double GetTaylor(double base, int numberOfTerms = 4);
	static double ImprovedGetTaylor(double base, int numberOfTerms = 4);
	static double ImprovedGetTaylorHornersRuleByRecursion(double base, int numberOfTerms = 4);
	static double ImprovedGetTaylorHornersRuleByLoop(double base, int numberOfTerms = 4);
	static int GetFibonacciTermRecursion(int numberOfTerm = 7);// time:O(2^n)
	static int GetFibonacciTermByLoop(int numberOfTerm = 7);
	static void PrintFibonacciByRecursion(int numberOfTerms = 7);
	static void PrintFibonacciByLoop(int numberOfTerms = 7);
	static void TestBehavior();
};

