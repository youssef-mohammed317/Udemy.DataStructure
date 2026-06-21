#pragma once
#include<iostream>

class RatInMazeProblem
{
	static void RIM(int** maze, int** sol, int k, int i, int j, int n);
	static void Print(int** sol, int n);

public:
	static void Execute(int** maze, int n);


	static void TestBehavior();
};

