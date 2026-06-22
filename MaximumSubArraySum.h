#pragma once

#include<iostream>

class MaximumSubArraySum
{

public:
	static void ExecuteNaiveN3(int* arr, int n);

	static void ExecuteNaiveN2(int* arr, int n);

	static void ExecuteDP(int* arr, int n);

	static void ExecuteKadaneN(int* arr, int n);


	static void TestBehavior();
};

