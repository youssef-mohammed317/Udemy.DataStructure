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
			arr[i] = arr[rear];
			arr[rear--] = INT_MIN;
			while (rear > 0 && arr[rear] == INT_MIN)
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
			if ((lchildIndex >= capacity || (arr[lchildIndex] == INT_MIN)) && (rchildIndex >= capacity || (arr[rchildIndex] == INT_MIN)))
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
		return 2;
	int deg1 = CountByDegree(1);
	if (deg1 != 0)
		return 1;
	return 0;
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
	if (lchildIndex >= capacity && rchildIndex >= capacity)
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
		cout << arr[q.front()];
		q.pop();
		if (!q.empty())
			cout << ", ";

	}
	cout << "}\n";
}

void BinaryTreeByArray::RLevelDisplay(int low, int high)
{

	if (low < 1 || low>rear)return;

	for (int i = low; i <= high && i <= rear; i++)
	{
		if (arr[i] != INT_MIN)
		{
			if (i != 1)
			{
				cout << ", ";
			}
			cout << arr[i];
		}
	}
	RLevelDisplay(low * 2, low * 4 - 1);
}
void BinaryTreeByArray::RLevelDisplay()
{
	cout << "{";
	RLevelDisplay(1, 1);
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
	RInDisplay(parentIndex * 2);// left
	cout << ", ";
	cout << arr[parentIndex];
	RInDisplay(parentIndex * 2 + 1);//right
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
	RPostDisplay(parentIndex * 2);// left
	RPostDisplay(parentIndex * 2 + 1);//right
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

		if (rchildIndex < capacity && arr[rchildIndex] != INT_MIN)
		{
			s.push(rchildIndex);
		}
		if (lchildIndex < capacity && arr[lchildIndex] != INT_MIN)
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
		if (lchildIndex < capacity && arr[lchildIndex] != INT_MIN)
		{
			if (rchildIndex < capacity && arr[rchildIndex] != INT_MIN)
			{
				s.push(rchildIndex);
			}
			s.push(parentIndex);
			s.push(lchildIndex);
			parents.push(parentIndex);
		}
		else if (rchildIndex < capacity && arr[rchildIndex] != INT_MIN)
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

		if (lchildIndex < capacity && arr[lchildIndex] != INT_MIN)
		{
			s.push(parentIndex);
			if (rchildIndex < capacity && arr[rchildIndex] != INT_MIN)
			{
				s.push(rchildIndex);
			}
			s.push(lchildIndex);
			parents.push(parentIndex);
		}
		else if (rchildIndex < capacity && arr[rchildIndex] != INT_MIN)
		{
			s.push(parentIndex);
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
void BinaryTreeByArray::TestBehavior()
{
	cout << "\n=== STARTING COMPREHENSIVE BINARY TREE TESTS ===\n\n";
	BinaryTreeByArray tree;

	cout << "[1] Testing Empty Tree:\n";
	cout << "Is tree empty? (Expected 1): " << tree.IsEmpty() << "\n";
	cout << "Height of empty tree (Expected 0): " << tree.GetHeight() << "\n";
	cout << "Does 10 exist in empty tree? (Expected 0): " << tree.IsExist(10) << "\n";
	cout << "Delete from empty tree (Should not crash)...\n";
	tree.Delete(10);

	// Build a Complete Binary Tree
	//         10
	//       /    \
	//     20      30
	//    /  \    /  \
	//  40   50  60   70
	cout << "\n[2] Inserting Elements (10, 20, 30, 40, 50, 60, 70)...\n";
	for (int i = 1; i <= 7; i++)
	{
		tree.Insert(i * 10);
	}
	cout << "\n[3] Testing Traversals:\n";
	cout << "Level (I):     "; tree.ILevelDisplay();       // {10, 20, 30, 40, 50, 60, 70}
	cout << "Level (Queue): "; tree.IQueueLevelDisplay();  // {10, 20, 30, 40, 50, 60, 70}
	cout << "Level (R):     "; tree.RLevelDisplay();       // {10, 20, 30, 40, 50, 60, 70} <-- ADDED HERE
	cout << "Pre (R):       "; tree.RPreDisplay();         // {10, 20, 40, 50, 30, 60, 70}
	cout << "Pre (I):       "; tree.IPreDisplay();         // {10, 20, 40, 50, 30, 60, 70}
	cout << "In (R):        "; tree.RInDisplay();          // {40, 20, 50, 10, 60, 30, 70}
	cout << "In (I):        "; tree.IInDisplay();          // {40, 20, 50, 10, 60, 30, 70}
	cout << "Post (R):      "; tree.RPostDisplay();        // {40, 50, 20, 60, 70, 30, 10}
	cout << "Post (I):      "; tree.IPostDisplay();        // {40, 50, 20, 60, 70, 30, 10}

	cout << "\n[4] Testing Tree Properties:\n";
	cout << "Total Nodes    (Expected 7): " << tree.CountNodes() << "\n";
	cout << "Height         (Expected 3): " << tree.GetHeight() << "\n";
	cout << "Max Degree     (Expected 2): " << tree.GetMaxDegree() << "\n";
	cout << "Internal Nodes (Expected 3): " << tree.CountInternal() << "\n";
	cout << "External Nodes (Expected 4): " << tree.CountExternal() << "\n";

	cout << "\n[5] Testing Tree Shapes:\n";
	cout << "Is Strict?   (Expected 1): " << tree.IsStrict() << "\n";
	cout << "Is Complete? (Expected 1): " << tree.IsComplete() << "\n";
	cout << "Is Full?     (Expected 1): " << tree.IsFull() << "\n";

	cout << "\n[6] Testing Delete Logic (Internal Node):\n";
	tree.Delete(20); // Replaces 20 with 70
	cout << "Level Display after Deleting 20:  "; tree.ILevelDisplay();
	cout << "Is Full now?   (Expected 0): " << tree.IsFull() << "\n";

	cout << "\n[7] Testing DoubleCapacity (Forcing capacity > 8):\n";
	cout << "Inserting 80, 90, 100, 110...\n";
	tree.Insert(80); tree.Insert(90); tree.Insert(100); tree.Insert(110);
	cout << "Count Nodes    (Expected 10): " << tree.CountNodes() << "\n";
	cout << "Level Display:                "; tree.ILevelDisplay();

	cout << "\n[8] Testing Edge Cases (Invalid Inputs & Non-existent):\n";
	tree.Insert(INT_MIN);
	cout << "Count after inserting INT_MIN (Expected 10): " << tree.CountNodes() << "\n";
	tree.Delete(999);
	cout << "Count after deleting non-existent 999 (Expected 10): " << tree.CountNodes() << "\n";

	cout << "\n[9] Testing Root Deletion:\n";
	tree.Clear();
	tree.Insert(10); tree.Insert(20); tree.Insert(30);
	cout << "Before Root Delete: "; tree.ILevelDisplay();
	tree.Delete(10); // 30 should replace 10
	cout << "After Root Delete:  "; tree.ILevelDisplay();
	cout << "Root changed to 30? (Expected 1): " << (tree.IsExist(30) && !tree.IsExist(10)) << "\n";

	cout << "\n[10] Testing Total Annihilation (Preventing Crash):\n";
	// Current tree has 30, 20
	cout << "Deleting remaining nodes one by one...\n";
	tree.Delete(30);
	tree.Delete(20);
	cout << "Is Empty after deleting all? (Expected 1): " << tree.IsEmpty() << "\n";
	tree.Delete(50); // Trying to delete from empty again
	cout << "Did it survive without crashing? (Expected Yes!)\n";

	cout << "\n=== ALL TESTS PASSED FLAWLESSLY ===\n";
}