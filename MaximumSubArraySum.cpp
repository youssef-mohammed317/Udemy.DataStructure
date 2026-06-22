#include "MaximumSubArraySum.h"



void MaximumSubArraySum::ExecuteNaiveN3(int* arr, int n)
{
	// naive algorithm O(n3)
	int maxSum = INT_MIN;
	int start = -1, end = -1;
	for (int i = 0; i < n; i++)
	{
		for (int j = i; j < n; j++)
		{
			int sum = 0;
			for (int k = i; k <= j; k++)
			{
				sum += arr[k];
			}
			if (sum > maxSum)
			{
				maxSum = sum;
				start = i;
				end = j;
			}
		}
	}
	std::cout << "\nstart => " << start << ", end => " << end << ", max sum => " << maxSum << "\n";
}

void MaximumSubArraySum::ExecuteNaiveN2(int* arr, int n)
{
	// naive algorithm O(n2)
	int maxSum = INT_MIN;
	int start = -1, end = -1;
	for (int i = 0; i < n; i++)
	{
		int sum = 0;
		for (int j = i; j < n; j++)
		{
			sum += arr[j];
			if (sum > maxSum)
			{
				maxSum = sum;
				start = i;
				end = j;
			}
		}
	}
	std::cout << "\nstart => " << start << ", end => " << end << ", max sum => " << maxSum << "\n";
}

void MaximumSubArraySum::ExecuteDP(int* arr, int n)
{
	// DP algorithm time O(n) and space O(n) 
	if (n <= 0) return;

	int* res = new int[n] {0};
	res[0] = arr[0];


	for (int i = 1; i < n; i++)
	{
		if (res[i - 1] < 0)
		{
			res[i] = arr[i];
		}
		else {
			res[i] = res[i - 1] + arr[i];
		}
	}
	int maxSum = INT_MIN;
	int start = -1, end = -1;

	for (int i = 0; i < n; i++)
	{
		if (res[i] > maxSum)
		{
			maxSum = res[i];
			end = i;
		}
	}
	start = end;

	while (start > 0 && res[start] != arr[start])
	{
		start--;
	}


	std::cout << "\nstart => " << start << ", end => " << end << ", max sum => " << maxSum << "\n";

	delete[] res;
}

void MaximumSubArraySum::ExecuteKadaneN(int* arr, int n)
{
	// Kadane algorithm time O(n) and space O(1)
	if (n <= 0) return;

	int maxSum = arr[0];
	int start = 0, end = 0;
	int currentSum = arr[0];
	int tempStart = 0;


	for (int i = 1; i < n; i++)
	{
		if (currentSum > 0)
		{
			currentSum += arr[i];
		}
		else {
			currentSum = arr[i];
			tempStart = i;
		}

		if (currentSum > maxSum)
		{
			start = tempStart;
			end = i;
			maxSum = currentSum;
		}
	}

	std::cout << "\nstart => " << start << ", end => " << end << ", max sum => " << maxSum << "\n";
}


void MaximumSubArraySum::TestBehavior()
{
	// ---------------------------------------------------
	// Test Case 1: مصفوفة مختلطة (أرقام موجبة وسالبة)
	// النتيجة المتوقعة: start => 3, end => 6, max sum => 6 (للمسار 4, -1, 2, 1)
	// ---------------------------------------------------
	std::cout << "========== Test Case 1 (Mixed Numbers) ==========\n";
	int arr1[] = { -2, 1, -3, 4, -1, 2, 1, -5, 4 };
	int n1 = sizeof(arr1) / sizeof(arr1[0]);

	std::cout << "[ Naive O(N^3) ]";
	MaximumSubArraySum::ExecuteNaiveN3(arr1, n1);

	std::cout << "[ Naive O(N^2) ]";
	MaximumSubArraySum::ExecuteNaiveN2(arr1, n1);

	std::cout << "[ DP O(N) ]";
	MaximumSubArraySum::ExecuteDP(arr1, n1);

	std::cout << "[ Kadane O(N) ]";
	MaximumSubArraySum::ExecuteKadaneN(arr1, n1);


	// ---------------------------------------------------
	// Test Case 2: مصفوفة أرقام سالبة بالكامل
	// النتيجة المتوقعة: start => 3, end => 3, max sum => -1
	// ---------------------------------------------------
	std::cout << "\n========== Test Case 2 (All Negative Numbers) ==========\n";
	int arr2[] = { -5, -2, -9, -1, -3 };
	int n2 = sizeof(arr2) / sizeof(arr2[0]);

	std::cout << "[ Naive O(N^3) ]";
	MaximumSubArraySum::ExecuteNaiveN3(arr2, n2);

	std::cout << "[ Naive O(N^2) ]";
	MaximumSubArraySum::ExecuteNaiveN2(arr2, n2);

	std::cout << "[ DP O(N) ]";
	MaximumSubArraySum::ExecuteDP(arr2, n2);

	std::cout << "[ Kadane O(N) ]";
	MaximumSubArraySum::ExecuteKadaneN(arr2, n2);


	// ---------------------------------------------------
	// Test Case 3: مصفوفة أرقام موجبة بالكامل
	// النتيجة المتوقعة: start => 0, end => 4, max sum => 15
	// ---------------------------------------------------
	std::cout << "\n========== Test Case 3 (All Positive Numbers) ==========\n";
	int arr3[] = { 1, 2, 3, 4, 5 };
	int n3 = sizeof(arr3) / sizeof(arr3[0]);

	std::cout << "[ Naive O(N^3) ]";
	MaximumSubArraySum::ExecuteNaiveN3(arr3, n3);

	std::cout << "[ Naive O(N^2) ]";
	MaximumSubArraySum::ExecuteNaiveN2(arr3, n3);

	std::cout << "[ DP O(N) ]";
	MaximumSubArraySum::ExecuteDP(arr3, n3);

	std::cout << "[ Kadane O(N) ]";
	MaximumSubArraySum::ExecuteKadaneN(arr3, n3);


	std::cout << "\n================================================\n";
}