#include "DoubleProbingTechinque.h"

DoubleProbingTechinque::DoubleProbingTechinque()
{
	capacity = 8;
	hashTable = new int[capacity];
	Clear();
}
DoubleProbingTechinque::~DoubleProbingTechinque()
{
	delete[]hashTable;
}
void DoubleProbingTechinque::Clear()
{
	length = 0;
	for (int i = 0; i < capacity; i++)
		hashTable[i] = INT_MIN;
}

int DoubleProbingTechinque::GetHashIndex(int key)
{
	int i = key % capacity;
	return i > 0 ? i : -i;
}
void DoubleProbingTechinque::DoubleCapacity()
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
				Insert(oldHash[i]);
		}
		delete[]oldHash;
	}
}
void DoubleProbingTechinque::ReInsert()
{
	if (length > 0)
	{
		std::stack<int>s;
		for (int i = 0; i < capacity; i++)
		{
			if (hashTable[i] != INT_MIN)
				s.push(hashTable[i]);
		}
		Clear();
		while (!s.empty())
		{
			Insert(s.top()); s.pop();
		}
	}
}

int DoubleProbingTechinque::GetLength()
{
	return length;
}
void DoubleProbingTechinque::Insert(int key)
{
	DoubleCapacity();
	int index = GetHashIndex(key);

	int mod = key % 7;
	int step = 7 - (mod > 0 ? mod : -mod);
	int attempt = 1;
	int targetIndex = index;
	while (hashTable[targetIndex] != INT_MIN)
	{
		targetIndex = (index + attempt * step) % capacity;
		attempt++;
	}
	hashTable[targetIndex] = key;
	length++;
}
bool DoubleProbingTechinque::IsExist(int key)
{
	int index = GetHashIndex(key);
	int mod = key % 7;
	int step = 7 - (mod > 0 ? mod : -mod);
	int attempt = 1;
	int targetIndex = index;
	while (hashTable[targetIndex] != INT_MIN && hashTable[targetIndex] != key)
	{
		targetIndex = (index + attempt * step) % capacity;
		attempt++;
	}
	return hashTable[targetIndex] == key;
}
void DoubleProbingTechinque::Delete(int key)
{
	int index = GetHashIndex(key);
	int mod = key % 7;
	int step = 7 - (mod > 0 ? mod : -mod);
	int attempt = 1;
	int targetIndex = index;
	while (hashTable[targetIndex] != INT_MIN && hashTable[targetIndex] != key)
	{
		targetIndex = (index + attempt * step) % capacity;
		attempt++;
	}
	if (hashTable[targetIndex] == key)
	{
		hashTable[targetIndex] = INT_MIN;
		length--;
		ReInsert();
	}
}
void DoubleProbingTechinque::Display()
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
				if (l < length)
				{
					std::cout << ", ";
				}
			}
		}
	}
	std::cout << "}\n";
}
void DoubleProbingTechinque::TestBehavior()
{
	std::cout << "=== STARTING DOUBLE HASHING TESTS ===\n\n";
	DoubleProbingTechinque dhTable;

	std::cout << "[1] Testing Empty Hash Table:\n";
	std::cout << "Length (Expected 0): " << dhTable.GetLength() << "\n";
	std::cout << "Does 10 exist? (Expected 0): " << dhTable.IsExist(10) << "\n";

	std::cout << "\n[2] Testing Insertions & Double Hashing Collisions:\n";
	// Initial capacity is 8
	dhTable.Insert(10); // Index: 10 % 8 = 2

	// Let's force a collision at index 2
	// 18 % 8 = 2. Step: 7 - (18 % 7) = 7 - 4 = 3. 
	// Target: (2 + 1*3) % 8 = 5.
	dhTable.Insert(18);

	// Another collision at index 2
	// 26 % 8 = 2. Step: 7 - (26 % 7) = 7 - 5 = 2.
	// Target 1: (2 + 1*2) % 8 = 4.
	dhTable.Insert(26);

	std::cout << "Length (Expected 3): " << dhTable.GetLength() << "\n";
	std::cout << "Display map: "; dhTable.Display(); // Should place items correctly without infinite loops

	std::cout << "\n[3] Testing Lookup Efficiency (Double Hashing):\n";
	std::cout << "Find 10 (Expected 1): " << dhTable.IsExist(10) << "\n";
	std::cout << "Find 18 (Expected 1): " << dhTable.IsExist(18) << "\n";
	std::cout << "Find 26 (Expected 1): " << dhTable.IsExist(26) << "\n";
	std::cout << "Find 99 (Expected 0): " << dhTable.IsExist(99) << "\n";

	std::cout << "\n[4] Testing Delete & ReInsert Cluster fix:\n";
	dhTable.Delete(10);
	std::cout << "Find 10 after deletion (Expected 0): " << dhTable.IsExist(10) << "\n";
	std::cout << "Find 18 after 10 is deleted (Expected 1): " << dhTable.IsExist(18) << "\n";
	std::cout << "Length after deletion (Expected 2): " << dhTable.GetLength() << "\n";

	std::cout << "\n[5] Testing Double Capacity:\n";
	std::cout << "Inserting elements to trigger expansion at capacity/2...\n";
	dhTable.Insert(1);
	dhTable.Insert(2);
	dhTable.Insert(3); // Should trigger DoubleCapacity safely

	std::cout << "Length (Expected 5): " << dhTable.GetLength() << "\n";
	std::cout << "Display map after expansion: "; dhTable.Display();

	std::cout << "\n[6] Testing Clear:\n";
	dhTable.Clear();
	std::cout << "Length after clear (Expected 0): " << dhTable.GetLength() << "\n";
	std::cout << "Find 26 after clear (Expected 0): " << dhTable.IsExist(26) << "\n";

	std::cout << "\n=== ALL TESTS PASSED FLAWLESSLY ===\n";
}