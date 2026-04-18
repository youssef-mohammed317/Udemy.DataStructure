#include "HeapBinaryTree.h"
HeapBinaryTree::HeapBinaryTree(bool maxHeap)
{
	root = nullptr;
	this->maxHeap = maxHeap;
}
HeapBinaryTree::~HeapBinaryTree()
{
	Clear();
}
void HeapBinaryTree::Clear(Node* ptr)
{
	if (ptr == nullptr)return;

	Clear(ptr->GetLeft());
	Clear(ptr->GetRight());
	delete ptr;
}
void HeapBinaryTree::Clear()
{
	Clear(root);
	root = nullptr;
}
bool HeapBinaryTree::IsPerfect(Node* ptr)
{
	if (ptr == nullptr) return true;

	if (ptr->GetLeft() == nullptr && ptr->GetRight() == nullptr)
	{
		return true; // degree 0
	}
	else if ((ptr->GetLeft() != nullptr) ^ (ptr->GetRight() != nullptr))
	{
		return false; // degree 1
	}
	else
	{
		return IsPerfect(ptr->GetLeft()) && IsPerfect(ptr->GetRight()) && GetHeight(ptr->GetLeft()) == GetHeight(ptr->GetRight());
	}
}

bool HeapBinaryTree::IsPerfect()
{
	return IsPerfect(root);
}
int HeapBinaryTree::GetHeight(Node* ptr)
{
	if (ptr == nullptr)return 0;

	int x = GetHeight(ptr->GetLeft());
	int y = GetHeight(ptr->GetRight());

	return 1 + (x > y ? x : y);
}
int HeapBinaryTree::GetHeight()
{
	return GetHeight(root);
}
void HeapBinaryTree::Insert(Node* ptr, int val)
{
	if (ptr == nullptr)return;
	int currData = ptr->GetData();

	if (maxHeap && val > currData)
	{
		ptr->SetData(val);
		Insert(ptr, currData);
	}
	else if (!maxHeap && val < currData)
	{
		ptr->SetData(val);
		Insert(ptr, currData);
	}
	else {

		if (ptr->GetLeft() == nullptr)
		{
			ptr->SetLeft(new Node(val));
		}
		else if (ptr->GetRight() == nullptr)
		{
			ptr->SetRight(new Node(val));
		}
		else
		{
			if (IsPerfect(ptr->GetLeft()) && IsPerfect(ptr->GetRight()))
			{
				if (GetHeight(ptr->GetLeft()) == GetHeight(ptr->GetRight()))
				{
					Insert(ptr->GetLeft(), val);
				}
				else {
					Insert(ptr->GetRight(), val);
				}
			}
			else if (IsPerfect(ptr->GetLeft()) && !IsPerfect(ptr->GetRight()))
			{
				Insert(ptr->GetRight(), val);
			}
			else {
				Insert(ptr->GetLeft(), val);
			}
		}

	}
}

void HeapBinaryTree::Insert(int val)
{
	if (root == nullptr)
	{
		root = new Node(val);
	}
	else {
		Insert(root, val);
	}
}

Node* HeapBinaryTree::Search(Node* ptr, int val)
{
	if (ptr == nullptr)return nullptr;

	if (val == ptr->GetData())return ptr;

	if (maxHeap && val > ptr->GetData())return nullptr;
	if (!maxHeap && val < ptr->GetData())return nullptr;

	Node* temp = Search(ptr->GetLeft(), val);
	if (temp != nullptr) return temp;
	return Search(ptr->GetRight(), val);
}
Node* HeapBinaryTree::Search(int val)
{
	return Search(root, val);
}


Node* HeapBinaryTree::Delete()
{
	if (root == nullptr) return nullptr;
	int deletedData = root->GetData();
	queue<Node*>q;
	Node* curr, * lastParent;
	curr = lastParent = nullptr;
	q.push(root);

	while (!q.empty())
	{
		lastParent = curr;
		curr = q.front(); q.pop();

		if (curr->GetLeft() == nullptr && curr->GetRight() == nullptr)
		{
			while (!q.empty())
			{
				curr = q.front(); q.pop();
			}
		}
		else
		{
			if (curr->GetLeft() != nullptr)
				q.push(curr->GetLeft());
			if (curr->GetRight() != nullptr)
				q.push(curr->GetRight());
		}
	}

	if (lastParent == nullptr)
	{
		// only root
		delete root;
		root = nullptr;
	}
	else
	{
		if (lastParent->GetRight() == curr)
		{
			lastParent->SetRight(nullptr);
		}
		else if (lastParent->GetLeft() == curr)
		{
			lastParent->SetLeft(lastParent->GetRight());// not matter because right already nullptr(complete tree)
			lastParent->SetRight(nullptr); // not matter because right already nullptr(complete tree)
		}
		root->SetData(curr->GetData());
		delete curr;

		// rearrange the tree
		Rearrange(root);
	}
	return new Node(deletedData);
}
void HeapBinaryTree::Rearrange(Node* ptr)
{
	if (ptr == nullptr)return;

	if (ptr->GetLeft() == nullptr && ptr->GetRight() == nullptr)return;

	if ((ptr->GetLeft() != nullptr) ^ (ptr->GetRight() != nullptr))
	{
		// degree 1
		int currData = ptr->GetData();
		if (ptr->GetLeft() != nullptr)
		{
			int leftData = ptr->GetLeft()->GetData();
			if (maxHeap && (currData < leftData) || !maxHeap && (currData > leftData))
			{
				ptr->SetData(leftData);
				ptr->GetLeft()->SetData(currData);
				Rearrange(ptr->GetLeft());

			}
		}
		else if (ptr->GetRight() != nullptr) {
			// never get here
			int rightData = ptr->GetRight()->GetData();
			if (maxHeap && (currData < rightData) || !maxHeap && (currData > rightData))
			{
				ptr->SetData(rightData);
				ptr->GetRight()->SetData(currData);
				Rearrange(ptr->GetRight());
			}
		}
	}
	else {

		int currData = ptr->GetData();
		int leftData = ptr->GetLeft()->GetData();
		int rightData = ptr->GetRight()->GetData();

		if (maxHeap) {
			if (currData < rightData || currData < leftData) {
				if (rightData > leftData) {
					ptr->SetData(rightData);
					ptr->GetRight()->SetData(currData);
					Rearrange(ptr->GetRight());
				}
				else {
					ptr->SetData(leftData);
					ptr->GetLeft()->SetData(currData);
					Rearrange(ptr->GetLeft());
				}
			}
		}
		else {
			if (currData > rightData || currData > leftData) {
				if (rightData < leftData) {
					ptr->SetData(rightData);
					ptr->GetRight()->SetData(currData);
					Rearrange(ptr->GetRight());
				}
				else {
					ptr->SetData(leftData);
					ptr->GetLeft()->SetData(currData);
					Rearrange(ptr->GetLeft());
				}
			}
		}
	}
}


LinkedListNode* HeapBinaryTree::GetSortedLinkedList()
{
	if (root == nullptr)return nullptr;
	LinkedListNode* ptr;
	LinkedListNode* head = new LinkedListNode(Delete()->GetData(), nullptr);
	while (root != nullptr)
	{
		ptr = new LinkedListNode(Delete()->GetData(), nullptr);
		ptr->SetNext(head);
		head = ptr;
	}
	ptr = head;
	while (ptr != nullptr)
	{
		Insert(ptr->GetData());
		ptr = ptr->GetNext();
	}
	return head;
}

void HeapBinaryTree::Display()
{
	LinkedListNode* head = GetSortedLinkedList();
	std::cout << "{";
	while (head != nullptr)
	{
		std::cout << head->GetData();

		if (head->GetNext() != nullptr)
		{
			std::cout << ", ";
		}

		head = head->GetNext();
	}
	std::cout << "}\n";
}
void HeapBinaryTree::TestBehavior()
{
	std::cout << "\n========== Advanced Edge-Case Testing ==========\n";

	std::cout << "\n--- Test 1: Empty Heap Deletion ---\n";
	HeapBinaryTree emptyHeap(true);
	Node* delNode = emptyHeap.Delete();
	if (delNode == nullptr) {
		std::cout << "Success: Handled empty heap deletion safely (Returned nullptr).\n";
	}

	std::cout << "\n--- Test 2: Single Node Heap ---\n";
	HeapBinaryTree singleHeap(true);
	singleHeap.Insert(42);
	std::cout << "Inserted 42. Display: ";
	singleHeap.Display(); // Expected: {42}

	Node* deletedSingle = singleHeap.Delete();
	std::cout << "Deleted: " << deletedSingle->GetData() << "\n";
	delete deletedSingle; // Clean up memory
	std::cout << "After Deletion (should be empty): ";
	singleHeap.Display(); // Expected: {}

	std::cout << "\n--- Test 3: Duplicate Values (Max Heap) ---\n";
	HeapBinaryTree dupHeap(true);
	dupHeap.Insert(10);
	dupHeap.Insert(20);
	dupHeap.Insert(10);
	dupHeap.Insert(20);
	dupHeap.Insert(5);
	std::cout << "Duplicates Display (Ascending for Max Heap):\n";
	dupHeap.Display(); // Expected: {5, 10, 10, 20, 20}

	std::cout << "\n--- Test 4: Search Functionality (Min Heap) ---\n";
	HeapBinaryTree searchHeap(false); // Min Heap
	searchHeap.Insert(10);
	searchHeap.Insert(20);
	searchHeap.Insert(30);
	searchHeap.Insert(5);

	// 1. البحث عن عنصر موجود
	Node* found1 = searchHeap.Search(20);
	std::cout << "Search for 20: " << (found1 != nullptr ? "Found" : "Not Found") << "\n"; // Expected: Found

	// 2. البحث عن عنصر غير موجود (أكبر من كل العناصر)
	Node* found2 = searchHeap.Search(100);
	std::cout << "Search for 100: " << (found2 != nullptr ? "Found" : "Not Found") << "\n"; // Expected: Not Found

	// 3. البحث عن عنصر غير موجود (أصغر من القمة، مما يختبر الـ Optimization الخاص بك)
	Node* found3 = searchHeap.Search(2);
	std::cout << "Search for 2: " << (found3 != nullptr ? "Found" : "Not Found") << "\n"; // Expected: Not Found


	std::cout << "\n--- Test 5: Sequential Worst-Case Insertion (Min Heap) ---\n";
	HeapBinaryTree seqHeap(false);
	// إدخال أرقام تنازلية في Min Heap يجبر الشجرة على عمل صعود (Bubble Up) في كل إضافة
	seqHeap.Insert(50);
	seqHeap.Insert(40);
	seqHeap.Insert(30);
	seqHeap.Insert(20);
	seqHeap.Insert(10);
	std::cout << "Sequential Insert Display (Descending for Min Heap):\n";
	seqHeap.Display(); // Expected: {50, 40, 30, 20, 10}

	std::cout << "\n================================================\n";
}