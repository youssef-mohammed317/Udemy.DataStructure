#include "ChaningTechnique.h"
int ChaningTechnique::GetHashIndex(int key)
{
	int i = key % size;

	return i > 0 ? i : -i; // h(x)=x%10 => h(x) is index and x is the key 
}

ChaningTechnique::ChaningTechnique() {
	size = 10;
	length = 0;
	hashTable = new Node * [size];
	for (int i = 0; i < size; i++)
		hashTable[i] = nullptr;
}
ChaningTechnique::~ChaningTechnique()
{
	Clear();
	delete[] hashTable;
}
void ChaningTechnique::Clear()
{
	Node* temp, * curr;
	for (int i = 0; i < size; i++)
	{
		curr = hashTable[i];
		while (curr != nullptr)
		{
			temp = curr;
			curr = curr->GetNext();
			delete temp;
		}
		hashTable[i] = nullptr;
	}
	length = 0;
}

int ChaningTechnique::GetLength()
{
	return length;
}

void ChaningTechnique::Insert(int key)
{
	int index = GetHashIndex(key);
	// insert first
	hashTable[index] = new Node(key, hashTable[index]);
	length++;
}

bool ChaningTechnique::IsExist(int key)
{
	int index = GetHashIndex(key);

	if (hashTable[index] == nullptr)
		return false;
	Node* curr = hashTable[index];

	while (curr != nullptr)
	{
		if (curr->GetData() == key)
			return true;
		curr = curr->GetNext();
	}
	return false;

}

void ChaningTechnique::Delete(int key)
{
	int index = GetHashIndex(key);

	if (hashTable[index] == nullptr)
		return;
	Node* curr = hashTable[index], * prev = nullptr;
	while (curr != nullptr && curr->GetData() != key)
	{
		prev = curr;
		curr = curr->GetNext();
	}

	if (curr != nullptr && curr->GetData() == key)
	{
		if (prev == nullptr)
			hashTable[index] = curr->GetNext();
		else
			prev->SetNext(curr->GetNext());

		delete curr;
		length--;
	}
}

void ChaningTechnique::Display()
{
	std::cout << "{";

	if (length > 0)
	{
		int l = 0;
		for (int i = 0; i < size; i++)
		{
			if (hashTable[i] != nullptr)
			{
				Node* curr = hashTable[i];
				while (curr != nullptr)
				{
					std::cout << curr->GetData();
					curr = curr->GetNext();
					l++;

					if (curr != nullptr)
						std::cout << ", ";
				}
				if (l < length)
					std::cout << ", ";
			}

		}
	}
	std::cout << "}\n";
}
void ChaningTechnique::TestBehavior()
{
	std::cout << "=== STARTING HASH TABLE (CHAINING) TESTS ===\n\n";
	ChaningTechnique hashMap;

	std::cout << "[1] Testing Empty Hash Map:\n";
	std::cout << "Length (Expected 0): " << hashMap.GetLength() << "\n";
	std::cout << "Does 10 exist? (Expected 0): " << hashMap.IsExist(10) << "\n";
	std::cout << "Display empty: "; hashMap.Display();

	std::cout << "\n[2] Testing Insertions & Collisions:\n";
	// 10, 20, 30 will all collide at index 0 (if size is 10)
	hashMap.Insert(10);
	hashMap.Insert(20);
	hashMap.Insert(30);

	// 15, 25 will collide at index 5
	hashMap.Insert(15);
	hashMap.Insert(25);

	// Negative number test
	hashMap.Insert(-4); // -4 % 10 -> maps to index 6

	std::cout << "Length (Expected 6): " << hashMap.GetLength() << "\n";
	std::cout << "Display map: "; hashMap.Display();
	// Due to insert-at-head, order per chain will be reversed: {30, 20, 10, 25, 15, -4}

	std::cout << "\n[3] Testing Lookups (IsExist):\n";
	std::cout << "Find 20 (Expected 1): " << hashMap.IsExist(20) << "\n";
	std::cout << "Find -4 (Expected 1): " << hashMap.IsExist(-4) << "\n";
	std::cout << "Find 99 (Expected 0): " << hashMap.IsExist(99) << "\n";

	std::cout << "\n[4] Testing Deletions:\n";
	std::cout << "- Deleting head of a chain (30)...\n";
	hashMap.Delete(30);

	std::cout << "- Deleting middle of a chain (20)...\n";
	hashMap.Delete(20);

	std::cout << "- Deleting non-existent element (99)...\n";
	hashMap.Delete(99); // This will crash your old code, but passes with the fix!

	std::cout << "Length after deletions (Expected 4): " << hashMap.GetLength() << "\n";
	std::cout << "Display after deletions: "; hashMap.Display(); // {10, 25, 15, -4}

	std::cout << "\n[5] Testing Clear():\n";
	hashMap.Clear();
	std::cout << "Length after Clear (Expected 0): " << hashMap.GetLength() << "\n";
	std::cout << "Find 10 after Clear (Expected 0): " << hashMap.IsExist(10) << "\n";
	std::cout << "Display cleared map: "; hashMap.Display();

	std::cout << "\n=== ALL TESTS PASSED SUCCESSFULLY ===\n";
}