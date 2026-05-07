#pragma once
#include<iostream>
#include <queue>      // عشان الـ priority_queue نفسها
#include <vector>     // لأنها بتستخدم الـ vector من جواها عشان تخزن العناصر
#include <functional> // عشان نستخدم std::greater اللي بتعكس الترتيب لـ Min-Heap
using namespace std;
class OptimalMergePatternAlgorithm
{
	// Optimal Merge Pattern: Uses a Min-Heap (priority_queue) to repeatedly merge the two smallest arrays.
	// This greedy approach ensures the minimum total merging cost.
	// Note: std::pair is structured as {Size, Pointer} so the Heap automatically sorts by Size.

	static std::pair<int, int*> Merge(pair<int, int*> A, pair<int, int*> B);
public:
	static std::pair<int, int*> Execute(int* A, int* B, int* C, int* D, int* E, int ASize, int BSize, int CSize, int DSize, int ESize);
};

