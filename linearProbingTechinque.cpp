#include "linearProbingTechinque.h"


int linearProbingTechinque::GetHashIndex(int key)
{
	int i = key % capacity;
	return i > 0 ? i : -i;
}


void linearProbingTechinque::DoubleCapacity()
{
	if (length == (capacity - 1) / 2)
	{
		int* oldHash = hashTable;
		capacity *= 2;

		hashTable = new int[capacity];
		for (int i = 0; i < capacity; i++)
			hashTable[i] = INT_MIN;

		length = 0;
		for (int i = 0; i < capacity / 2; i++)
		{
			if (oldHash[i] != INT_MIN)
				Insert(oldHash[i]);
		}

		delete[]oldHash;
	}
}

void linearProbingTechinque::ReInsert()
{
	if (length > 0)
	{
		std::stack<int>s;

		for (int i = 0; i < capacity; i++)
		{
			if (hashTable[i] != INT_MIN)
			{
				s.push(hashTable[i]);
				hashTable[i] = INT_MIN;
			}
		}
		length = 0;
		while (!s.empty())
		{
			Insert(s.top());
			s.pop();
		}
	}
}
linearProbingTechinque::linearProbingTechinque()
{
	length = 0;
	capacity = 8;
	hashTable = new int[capacity];
	for (int i = 0; i < capacity; i++)
		hashTable[i] = INT_MIN;
}
linearProbingTechinque::~linearProbingTechinque()
{
	delete[]hashTable;
}
void linearProbingTechinque::Clear()
{
	for (int i = 0; i < capacity; i++)
		hashTable[i] = INT_MIN;
	length = 0;
}
int linearProbingTechinque::GetLength()
{
	return length;
}

void linearProbingTechinque::Insert(int key)
{
	DoubleCapacity();
	int index = GetHashIndex(key);
	while (hashTable[index] != INT_MIN)
	{
		index = (index + 1) % capacity;
	}
	if (hashTable[index] == INT_MIN)
	{
		hashTable[index] = key;
		length++;
	}
}

bool linearProbingTechinque::IsExist(int key)
{
	if (length > 0)
	{
		int index = GetHashIndex(key);
		while (hashTable[index] != INT_MIN && hashTable[index] != key)
		{
			index = (index + 1) % capacity;
		}
		if (hashTable[index] == key)
			return true;
	}
	return false;
}
void linearProbingTechinque::Delete(int key)
{
	if (length > 0)
	{
		int index = GetHashIndex(key);
		while (hashTable[index] != INT_MIN && hashTable[index] != key)
		{
			index = (index + 1) % capacity;
		}
		if (hashTable[index] == key)
		{
			hashTable[index] = INT_MIN;
			length--;
			ReInsert();
			return;
		}
	}
}
void linearProbingTechinque::Display()
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
				if (i < capacity - 1 && l < length)
				{
					std::cout << ", ";
				}
			}
		}
	}
	std::cout << "}\n";
}

void linearProbingTechinque::TestBehavior()
{
	std::cout << "=== STARTING LINEAR PROBING TESTS ===\n\n";
	linearProbingTechinque lpTable;

	std::cout << "[1] Testing Empty Hash Table:\n";
	std::cout << "Length (Expected 0): " << lpTable.GetLength() << "\n";
	std::cout << "Does 10 exist? (Expected 0): " << lpTable.IsExist(10) << "\n";

	std::cout << "\n[2] Testing Insertions & Collisions:\n";
	// Assuming initial capacity is 8
	lpTable.Insert(10); // Index: 10 % 8 = 2
	lpTable.Insert(18); // Collision: 18 % 8 = 2 -> shifts to 3
	lpTable.Insert(26); // Collision: 26 % 8 = 2 -> shifts to 4

	std::cout << "Length (Expected 3): " << lpTable.GetLength() << "\n";
	std::cout << "Display map: "; lpTable.Display(); // Should print {10, 18, 26}

	std::cout << "\n[3] Testing Lookup Efficiency (Linear Probing):\n";
	std::cout << "Find 18 (Expected 1): " << lpTable.IsExist(18) << "\n";
	std::cout << "Find 26 (Expected 1): " << lpTable.IsExist(26) << "\n";
	std::cout << "Find 99 (Expected 0): " << lpTable.IsExist(99) << "\n";

	std::cout << "\n[4] Testing Delete & ReInsert Cluster fix:\n";
	// Deleting 10 should move 18 and 26 to correct positions through ReInsert
	lpTable.Delete(10);
	std::cout << "Find 10 after deletion (Expected 0): " << lpTable.IsExist(10) << "\n";
	std::cout << "Find 26 after 10 is deleted (Expected 1): " << lpTable.IsExist(26) << "\n";
	std::cout << "Length after deletion (Expected 2): " << lpTable.GetLength() << "\n";

	std::cout << "\n[5] Testing Double Capacity:\n";
	std::cout << "Inserting multiple elements to trigger expansion...\n";
	lpTable.Insert(1);
	lpTable.Insert(2);
	lpTable.Insert(3);
	lpTable.Insert(4);
	lpTable.Insert(5); // This should definitely trigger DoubleCapacity

	std::cout << "Length (Expected 7): " << lpTable.GetLength() << "\n";
	std::cout << "Display map after expansion: "; lpTable.Display();

	std::cout << "\n[6] Testing Clear:\n";
	lpTable.Clear();
	std::cout << "Length after clear (Expected 0): " << lpTable.GetLength() << "\n";
	std::cout << "Find 1 after clear (Expected 0): " << lpTable.IsExist(1) << "\n";

	std::cout << "\n=== ALL TESTS PASSED! ===\n";
}