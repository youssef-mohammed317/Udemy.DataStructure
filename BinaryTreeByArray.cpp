#include "BinaryTreeByArray.h"

void BinaryTreeByArray::DoubleCapacity()
{
	if (rear == capacity - 1)
	{
		capacity *= 2;
		int* newArr = new int[capacity];
		int i = 0;
		for (; i < capacity / 2; i++)
			newArr[i] = arr[i];
		for (; i < capacity; i++)
			newArr[i] = INT_MIN;

		delete[]arr;
		arr = newArr;
	}
}


BinaryTreeByArray::BinaryTreeByArray()
{
	capacity = 8;
	rear = 0;
	arr = new int[capacity];
	for (int i = 0; i < capacity; i++)
		arr[i] = INT_MIN;
}
BinaryTreeByArray::~BinaryTreeByArray()
{
	delete[]arr;
}
void BinaryTreeByArray::Clear()
{
	delete[]arr;
	rear = 0;
	arr = new int[capacity];
	for (int i = 0; i < capacity; i++)
		arr[i] = INT_MIN;
}
bool BinaryTreeByArray::IsEmpty()
{
	return rear == 0 || CountNodes() == 0;
}
bool BinaryTreeByArray::IsExist(int val)
{
	if (IsEmpty())return false;
	if (val == INT_MIN) return true;

	for (int i = 1; i < capacity; i++)
	{
		if (val == arr[i])
			return true;
	}

	return false;
}

void BinaryTreeByArray::Insert(int val)
{
	DoubleCapacity();
	if (val == INT_MIN)return;
	for (int i = 1; i < capacity; i++)
	{
		if (arr[i] == INT_MIN)
		{
			arr[i] = val;
			if (i > rear)
				rear = i;
			return;
		}
	}
}

void BinaryTreeByArray::Delete(int val)
{
	if (IsEmpty())return;
	DoubleCapacity();
	if (val == INT_MIN) return;
	for (int i = 1; i < capacity; i++)
	{
		if (arr[i] == val)
		{
			arr[i] = INT_MIN;
			if (i == rear)
				rear--;
			return;
		}
	}
}

int BinaryTreeByArray::CountByDegree(int degree)
{
	if (IsEmpty())return 0;
	if (degree > 2 || degree < 0)return 0;
	int counter = 0;
	int parentIndex, lchildIndex, rchildIndex;
	for (int i = 1; i < capacity; i++)
	{
		parentIndex = i;
		lchildIndex = 2 * parentIndex;
		rchildIndex = 2 * parentIndex + 1;
		if (degree == 2)
		{
			if (rchildIndex < capacity && lchildIndex < capacity)
			{
				if (arr[parentIndex] != INT_MIN && arr[rchildIndex] != INT_MIN && arr[lchildIndex] != INT_MIN)
				{
					counter++;
				}
			}
		}
		else if (degree == 1)
		{
			if ((rchildIndex < capacity || lchildIndex < capacity))
			{
				if (arr[parentIndex] != INT_MIN && (((rchildIndex < capacity) && (arr[rchildIndex] != INT_MIN)) ^ ((lchildIndex < capacity) && (arr[lchildIndex] != INT_MIN))))
				{
					counter++;
				}
			}
		}
		else
		{
			if ((lchildIndex > capacity || (arr[lchildIndex] == INT_MIN)) && (rchildIndex > capacity || (arr[rchildIndex] == INT_MIN)))
			{
				counter++;
			}
		}
	}
	return counter;
}
int BinaryTreeByArray::CountExternal()
{
	return CountByDegree(0);
}
int BinaryTreeByArray::CountInternal()
{
	return CountByDegree(1) + CountByDegree(2);
}
int BinaryTreeByArray::CountNodes()
{
	int counter = 0;
	for (int i = 1; i < capacity; i++)
	{
		if (arr[i] != INT_MIN)
			counter++;

	}
	return counter;
}

int BinaryTreeByArray::GetMaxDegree()
{
	int deg2 = CountByDegree(2);
	if (deg2 != 0)
		return deg2;
	int deg1 = CountByDegree(1);
	if (deg1 != 0)
		return deg1;
	return CountByDegree(0);
}

bool BinaryTreeByArray::IsStrict()
{
	return CountByDegree(1) == 0;
}
bool BinaryTreeByArray::IsComplete()
{
	if (IsEmpty()) return true;
	for (int i = 1; i < capacity; i++)
	{
		if (arr[i] == INT_MIN)
		{
			for (; i < capacity; i++)
			{
				if (arr[i] != INT_MIN)
					return false;
			}
		}
	}
	return true;
}
bool BinaryTreeByArray::IsFull()
{
	if (IsEmpty()) return true;
	for (int i = 1; i < capacity; i++)
	{
		if (arr[i] == INT_MIN)
		{
			return false;
		}
	}
	return true;
}
int BinaryTreeByArray::GetHeight(int parentIndex)
{
	if (parentIndex >= capacity) return 0;
	if (arr[parentIndex] == INT_MIN)return 0;
	int lchildIndex = 2 * parentIndex;
	int	rchildIndex = 2 * parentIndex + 1;
	if (lchildIndex > capacity && rchildIndex > capacity)
		return 1;

	int x = GetHeight(lchildIndex);
	int y = GetHeight(rchildIndex);

	return (x > y ? x : y) + 1;
}
int BinaryTreeByArray::GetHeight()
{
	if (IsEmpty()) return 0;
	return GetHeight(1);
}
void BinaryTreeByArray::ILevelDisplay()
{
	std::cout << "{";
	int i = 1;
	while (i < capacity)
	{
		if (arr[i] != INT_MIN)
		{
			std::cout << arr[i];
		}
		i++;
		while (arr[i] == INT_MIN)
			i++;

		if (i < capacity)
			std::cout << ", ";
	}
	std::cout << "}\n";

}
void BinaryTreeByArray::IQueueLevelDisplay()
{
	cout << "{";
	queue<int> q;
	for (int i = 1; i < capacity; i++)
	{
		if (arr[i] != INT_MIN)
			q.push(i);
	}
	while (!q.empty())
	{
		cout << q.front();
		q.pop();
		if (!q.empty())
			cout << ", ";

	}
	cout << "}\n";
}

void BinaryTreeByArray::RPreDisplay(int parentIndex)
{
	if (parentIndex >= capacity)return;
	if (arr[parentIndex] == INT_MIN)return;
	cout << ", ";
	cout << arr[parentIndex];
	RPreDisplay(parentIndex * 2);// left
	RPreDisplay(parentIndex * 2 + 1);//right
}
void BinaryTreeByArray::RPreDisplay()
{
	cout << "{";
	RPreDisplay(1);
	cout << "}\n";
}
void BinaryTreeByArray::RInDisplay(int parentIndex)
{
	if (parentIndex >= capacity)return;
	if (arr[parentIndex] == INT_MIN)return;
	RPreDisplay(parentIndex * 2);// left
	cout << ", ";
	cout << arr[parentIndex];
	RPreDisplay(parentIndex * 2 + 1);//right
}
void BinaryTreeByArray::RInDisplay()
{
	cout << "{";
	RInDisplay(1);
	cout << "}\n";
}
void BinaryTreeByArray::RPostDisplay(int parentIndex)
{
	if (parentIndex >= capacity)return;
	if (arr[parentIndex] == INT_MIN)return;
	RPreDisplay(parentIndex * 2);// left
	RPreDisplay(parentIndex * 2 + 1);//right
	cout << ", ";
	cout << arr[parentIndex];
}
void BinaryTreeByArray::RPostDisplay()
{
	cout << "{";
	RPostDisplay(1);
	cout << "}\n";
}
void BinaryTreeByArray::IPreDisplay()
{
	if (IsEmpty())
	{
		cout << "{}\n";
		return;
	}
	cout << "{";
	stack<int>s;
	s.push(1);
	int parentIndex, lchildIndex, rchildIndex;
	while (!s.empty())
	{
		parentIndex = s.top(); s.pop();
		cout << arr[parentIndex] << ", ";

		lchildIndex = parentIndex * 2;
		rchildIndex = lchildIndex + 1;

		if (rchildIndex <= capacity && arr[rchildIndex] != INT_MIN)
		{
			s.push(rchildIndex);
		}
		if (lchildIndex <= capacity && arr[lchildIndex] != INT_MIN)
		{
			s.push(lchildIndex);
		}
	}
	cout << "}\n";
}
void BinaryTreeByArray::IInDisplay()
{
	if (IsEmpty())
	{
		cout << "{}\n";
		return;
	}
	cout << "{";
	stack<int>s, parents;
	s.push(1);
	int parentIndex, lchildIndex, rchildIndex;

	while (!s.empty())
	{
		parentIndex = s.top(); s.pop();
		lchildIndex = parentIndex * 2;
		rchildIndex = lchildIndex + 1;
		if (lchildIndex <= capacity && arr[lchildIndex] != INT_MIN)
		{
			if (rchildIndex <= capacity && arr[rchildIndex] != INT_MIN)
			{
				s.push(rchildIndex);
			}
			s.push(parentIndex);
			s.push(lchildIndex);
			parents.push(parentIndex);
		}
		else if (rchildIndex <= capacity && arr[rchildIndex] != INT_MIN)
		{
			cout << arr[parentIndex] << ", ";
			s.push(rchildIndex);
		}
		else {
			cout << arr[parentIndex] << ", ";
			while (!s.empty() && !parents.empty() && s.top() == parents.top())
			{
				parentIndex = s.top(); s.pop(); parents.pop();
				cout << arr[parentIndex] << ", ";
			}
		}

	}
	cout << "}\n";
}
void BinaryTreeByArray::IPostDisplay()
{
	if (IsEmpty())
	{
		cout << "{}\n";
		return;
	}
	cout << "{";
	stack<int>s, parents;
	s.push(1);
	int parentIndex, lchildIndex, rchildIndex;

	while (!s.empty())
	{
		parentIndex = s.top(); s.pop();
		lchildIndex = parentIndex * 2;
		rchildIndex = lchildIndex + 1;
		if (lchildIndex <= capacity && arr[lchildIndex] != INT_MIN)
		{
			if (rchildIndex <= capacity && arr[rchildIndex] != INT_MIN)
			{
				s.push(rchildIndex);
			}
			s.push(lchildIndex);
			s.push(parentIndex);
			parents.push(parentIndex);
		}
		else if (rchildIndex <= capacity && arr[rchildIndex] != INT_MIN)
		{
			s.push(rchildIndex);
			parents.push(parentIndex);
		}
		else {
			cout << arr[parentIndex] << ", ";
			while (!s.empty() && !parents.empty() && s.top() == parents.top())
			{
				parentIndex = s.top(); s.pop(); parents.pop();
				cout << arr[parentIndex] << ", ";
			}
		}
	}
	cout << "}\n";
}


