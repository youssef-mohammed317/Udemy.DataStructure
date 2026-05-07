#include "OptimalMergePatternAlgorithm.h"

pair<int, int*> OptimalMergePatternAlgorithm::Merge(pair<int, int*> A, pair<int, int*> B) {
	pair<int, int*> res;
	res.first = A.first + B.first;
	res.second = new int[res.first] {0};
	int i = 0, j = 0, k = 0;
	while (i < A.first && j < B.first)
	{
		if (A.second[i] < B.second[j])
		{
			res.second[k++] = A.second[i++];
		}
		else {
			res.second[k++] = B.second[j++];
		}
	}
	while (i < A.first)
	{
		res.second[k++] = A.second[i++];
	}
	while (j < B.first)
	{
		res.second[k++] = B.second[j++];
	}
	return res;
}

pair<int, int*>  OptimalMergePatternAlgorithm::Execute(int* A, int* B, int* C, int* D, int* E, int ASize, int BSize, int CSize, int DSize, int ESize)
{
	priority_queue < pair<int, int*>, std::vector<pair<int, int*>>, std::greater<pair<int, int*>>> minHeap;
	minHeap.push({ ASize, A });
	minHeap.push({ BSize, B });
	minHeap.push({ CSize, C });
	minHeap.push({ DSize, D });
	minHeap.push({ ESize, E });

	while (minHeap.size() > 1)
	{
		auto min1 = minHeap.top(); minHeap.pop();
		auto min2 = minHeap.top(); minHeap.pop();
		auto res = Merge(min1, min2);
		minHeap.push({ res.first,res.second });
	}
	return minHeap.top();
}