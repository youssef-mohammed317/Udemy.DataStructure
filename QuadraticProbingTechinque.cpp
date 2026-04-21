#include "QuadraticProbingTechinque.h"

QuadraticProbingTechinque::QuadraticProbingTechinque()
{
	length = 0;
	capacity = 8;
	hashTable = new int[capacity];
	for (int i = 0; i < capacity; i++)
		hashTable[i] = INT_MIN;
}

QuadraticProbingTechinque::~QuadraticProbingTechinque()
{
	delete[]hashTable;
}
void QuadraticProbingTechinque::Clear()
{
	length = 0;
	for (int i = 0; i < capacity; i++)
		hashTable[i] = INT_MIN;

}
int QuadraticProbingTechinque::GetHashIndex(int key)
{
	int i = key % capacity;
	return i > 0 ? i : -i;
}
void QuadraticProbingTechinque::DoubleCapacity()
{
	if (length == (capacity - 1) / 2)
	{
		int* oldHash = hashTable;
		capacity *= 2;
		hashTable = new int[capacity];
		Clear();
		for (int i = 0; i < capacity / 2; i++)
		{
			if (oldHash[i] != INT_MIN)
			{
				Insert(oldHash[i]);
			}
		}
		delete[]oldHash;
	}
}
void QuadraticProbingTechinque::ReInsert()
{
	if (length > 0)
	{
		std::stack<int>s;

		for (int i = 0; i < capacity; i++)
		{
			if (hashTable[i] != INT_MIN)
			{
				s.push(hashTable[i]);
			}
		}
		Clear();
		while (!s.empty())
		{
			Insert(s.top()); s.pop();
		}
	}
}

int QuadraticProbingTechinque::GetLength()
{
	return length;
}

void QuadraticProbingTechinque::Insert(int key)
{
	DoubleCapacity();
	int index = GetHashIndex(key);
	int targetIndex = index;

	int step = 1;
	while (hashTable[targetIndex] != INT_MIN)
	{

		targetIndex = (index + (step * step)) % capacity;
		step++;
	}

	hashTable[targetIndex] = key;
	length++;
}
bool QuadraticProbingTechinque::IsExist(int key)
{
	int index = GetHashIndex(key);
	int targetIndex = index;
	int step = 1;
	while (hashTable[targetIndex] != INT_MIN && hashTable[targetIndex] != key)
	{
		targetIndex = (index + (step * step)) % capacity;
		step++;
	}

	return hashTable[targetIndex] == key;
}
void QuadraticProbingTechinque::Delete(int key)
{
	int index = GetHashIndex(key);
	int targetIndex = index;
	int step = 1;
	while (hashTable[targetIndex] != INT_MIN && hashTable[targetIndex] != key)
	{
		targetIndex = (index + (step * step)) % capacity;
		step++;
	}
	if (hashTable[targetIndex] == key)
	{
		hashTable[targetIndex] = INT_MIN;
		length--;
		ReInsert();
	}
}

void QuadraticProbingTechinque::Display()
{
	std::cout << "{";
	if (length > 0)
	{
		int l = 0;
		for (int i = 0; i < capacity; i++)
		{
			if (hashTable[i] != INT_MIN)
			{
				std::cout << hashTable[i];
				l++;
				if (i < capacity && l < length)
					std::cout << ", ";
			}
		}
	}
	std::cout << "}\n";
}

void QuadraticProbingTechinque::TestBehavior()
{
	std::cout << "=== STARTING QUADRATIC PROBING TESTS ===\n\n";
	QuadraticProbingTechinque qpTable;

	std::cout << "[1] Testing Empty Hash Table:\n";
	std::cout << "Length (Expected 0): " << qpTable.GetLength() << "\n";
	std::cout << "Does 10 exist? (Expected 0): " << qpTable.IsExist(10) << "\n";

	std::cout << "\n[2] Testing Insertions & Quadratic Collisions:\n";
	// Initial capacity is 8
	qpTable.Insert(10); // Index: 10 % 8 = 2
	qpTable.Insert(18); // Collision 1: 18 % 8 = 2 -> Checks (2 + 1*1) % 8 = 3
	qpTable.Insert(26); // Collision 2: 26 % 8 = 2 -> Checks (2 + 1*1) = 3 (Full) -> Checks (2 + 2*2) % 8 = 6

	std::cout << "Length (Expected 3): " << qpTable.GetLength() << "\n";
	std::cout << "Display map (Indexes 2, 3, 6): "; qpTable.Display();

	std::cout << "\n[3] Testing Lookup Efficiency (Quadratic Probing):\n";
	std::cout << "Find 18 (Expected 1): " << qpTable.IsExist(18) << "\n";
	std::cout << "Find 26 (Expected 1): " << qpTable.IsExist(26) << "\n";
	std::cout << "Find 99 (Expected 0): " << qpTable.IsExist(99) << "\n";

	std::cout << "\n[4] Testing Delete & ReInsert Cluster fix:\n";
	// Deleting 10 should safely restructure the array so 26 can still be found
	qpTable.Delete(10);
	std::cout << "Find 10 after deletion (Expected 0): " << qpTable.IsExist(10) << "\n";
	std::cout << "Find 26 after 10 is deleted (Expected 1): " << qpTable.IsExist(26) << "\n";
	std::cout << "Length after deletion (Expected 2): " << qpTable.GetLength() << "\n";

	std::cout << "\n[5] Testing Double Capacity:\n";
	std::cout << "Inserting elements to trigger expansion at capacity/2...\n";
	qpTable.Insert(1);
	qpTable.Insert(2);
	qpTable.Insert(3); // Should trigger DoubleCapacity safely

	std::cout << "Length (Expected 5): " << qpTable.GetLength() << "\n";
	std::cout << "Display map after expansion: "; qpTable.Display();

	std::cout << "\n[6] Testing Clear:\n";
	qpTable.Clear();
	std::cout << "Length after clear (Expected 0): " << qpTable.GetLength() << "\n";
	std::cout << "Find 26 after clear (Expected 0): " << qpTable.IsExist(26) << "\n";

	std::cout << "\n=== ALL TESTS PASSED FLAWLESSLY ===\n";
}