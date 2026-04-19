#pragma once
#include<iostream>
class SortingTechnique
{
	static void Swap(int& x, int& y);
	static void PrintArray(int* arr, int size);
public:
	static void BubbleAscending(int* arr, int size); // O(n^2)
	static void BubbleDescending(int* arr, int size); // O(n^2)

	static void InsertionAscending(int* arr, int size); // O(n^2)
	static void InsertionDescending(int* arr, int size);// O(n^2)

	static void SelectionAscending(int* arr, int size);// O(n^2)
	static void SelectionDescending(int* arr, int size);// O(n^2)

	static void TestBehavior();
};

