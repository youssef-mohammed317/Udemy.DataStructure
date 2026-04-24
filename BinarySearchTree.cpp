#include "BinarySearchTree.h"
#include <iostream>

BinarySearchTree::BinarySearchTree() {
	root = nullptr;
}

BinarySearchTree::~BinarySearchTree() {
	ILevelClear();
}

void BinarySearchTree::ILevelClear() {

	if (root == nullptr) return;

	queue<Node*>q;
	q.push(root);
	Node* ptr;
	while (!q.empty())
	{
		ptr = q.front(); q.pop();

		if (ptr->GetLeft() != nullptr)
			q.push(ptr->GetLeft());
		if (ptr->GetRight() != nullptr)
			q.push(ptr->GetRight());

		delete ptr;
	}

	root = nullptr;
}

void BinarySearchTree::IPreClear() {

	if (root == nullptr) return;

	stack<Node*>s;
	s.push(root);
	Node* ptr;

	while (!s.empty())
	{
		ptr = s.top(); s.pop();

		if (ptr->GetRight() != nullptr)
		{
			s.push(ptr->GetRight());
		}

		if (ptr->GetLeft() != nullptr)
		{
			s.push(ptr->GetLeft());

		}

		delete ptr;
	}

	root = nullptr;
}

void BinarySearchTree::IInClear() {

	if (root == nullptr) return;

	stack<Node*>s, lastParents;
	s.push(root);
	Node* ptr;

	while (!s.empty())
	{
		ptr = s.top(); s.pop();

		if (ptr->GetLeft() != nullptr)
		{
			if (ptr->GetRight() != nullptr)
			{
				s.push(ptr->GetRight());
			}
			s.push(ptr);
			s.push(ptr->GetLeft());
			lastParents.push(ptr);
		}
		else if (ptr->GetRight() != nullptr)
		{
			s.push(ptr->GetRight());
			delete ptr;
		}
		else
		{
			delete ptr;

			while (!s.empty() && !lastParents.empty() && s.top() == lastParents.top())
			{
				ptr = s.top(); s.pop(); lastParents.pop();
				delete ptr;
			}
		}

	}

	root = nullptr;
}

void BinarySearchTree::IPostClear() {

	if (root == nullptr) return;

	stack<Node*>s, lastParants;
	s.push(root);
	Node* ptr;

	while (!s.empty())
	{
		ptr = s.top(); s.pop();


		if (ptr->GetLeft() != nullptr)
		{
			s.push(ptr);
			if (ptr->GetRight() != nullptr)
			{
				s.push(ptr->GetRight());
			}
			s.push(ptr->GetLeft());
			lastParants.push(ptr);
		}
		else if (ptr->GetRight() != nullptr)
		{
			s.push(ptr);
			s.push(ptr->GetRight());
			lastParants.push(ptr);
		}
		else
		{
			delete ptr;

			while (!s.empty() && !lastParants.empty() && lastParants.top() == s.top())
			{
				ptr = s.top(); s.pop();
				lastParants.pop();
				delete ptr;
			}
		}

	}

	root = nullptr;
}


void BinarySearchTree::RPreClear(Node* ptr) {
	if (ptr != nullptr)
	{
		Node* right = ptr->GetRight();
		Node* left = ptr->GetLeft();
		delete ptr;
		RPreClear(left);
		RPreClear(right);
	}
}
void BinarySearchTree::RPreClear() {
	if (root == nullptr) return;
	RPreClear(root);
	root = nullptr;
}

void BinarySearchTree::RInClear(Node* ptr) {
	if (ptr != nullptr)
	{
		Node* right = ptr->GetRight();
		RInClear(ptr->GetLeft());
		delete ptr;
		RInClear(right);
	}
}
void BinarySearchTree::RInClear() {
	if (root == nullptr) return;
	RInClear(root);
	root = nullptr;
}

void BinarySearchTree::RPostClear(Node* ptr) {
	if (ptr != nullptr)
	{
		RPostClear(ptr->GetLeft());
		RPostClear(ptr->GetRight());
		delete ptr;
	}
}
void BinarySearchTree::RPostClear() {
	if (root == nullptr) return;
	RPostClear(root);
	root = nullptr;
}

void BinarySearchTree::RLevelClear(Node* ptr, int level) {

	if (ptr != nullptr)
	{
		if (level == 1)
		{
			delete ptr;
		}
		else
		{
			RLevelClear(ptr->GetLeft(), level - 1);
			RLevelClear(ptr->GetRight(), level - 1);
		}
	}
}
void BinarySearchTree::RLevelClear() {
	if (root == nullptr) return;

	int levels = RGetHeight(); // root is at level 1

	for (int level = levels; level >= 1; level--)
	{
		RLevelClear(root, level);
	}
	root = nullptr;
}

void BinarySearchTree::IInsert(int val) {

	if (root == nullptr)
	{
		root = new Node(val);
		return;
	}

	Node* ptr = root;

	while (ptr != nullptr)
	{
		if (val == ptr->GetData())
			return;


		if (val > ptr->GetData())
		{
			if (ptr->GetRight() == nullptr)
			{
				ptr->SetRight(new Node(val));
				return;
			}

			ptr = ptr->GetRight();
		}
		else
		{
			if (ptr->GetLeft() == nullptr)
			{
				ptr->SetLeft(new Node(val));
				return;
			}

			ptr = ptr->GetLeft();
		}
	}
}
void BinarySearchTree::RInsert(Node* ptr, int val) {
	if (ptr == nullptr)return;

	if (ptr->GetData() == val)return;

	if (val > ptr->GetData())
	{
		// val in right
		if (ptr->GetRight() == nullptr)
		{
			// this is the place
			ptr->SetRight(new Node(val));
			return;
		}
		else
		{
			// go right
			RInsert(ptr->GetRight(), val);
		}
	}
	else
	{
		// val in left
		if (ptr->GetLeft() == nullptr)
		{
			// this is the place
			ptr->SetLeft(new Node(val));
			return;
		}
		else
		{
			// go left
			RInsert(ptr->GetLeft(), val);
		}
	}
}
void BinarySearchTree::RInsert(int val) {
	if (root == nullptr)
	{
		root = new Node(val);
		return;
	}
	RInsert(root, val);
}

void BinarySearchTree::IDelete(int val) {

	if (root == nullptr)
		return;

	Node* curr = root;
	Node* parent = nullptr;

	while (curr != nullptr && curr->GetData() != val)
	{
		parent = curr;
		if (val > curr->GetData())
		{
			curr = curr->GetRight();
		}
		else {
			curr = curr->GetLeft();
		}
	}

	if (curr == nullptr)
		return;// not found

	// here curr point to target
	if (curr->GetLeft() == nullptr || curr->GetRight() == nullptr)
	{
		// leaf or degree 1

		Node* child = (curr->GetLeft() != nullptr) ? curr->GetLeft() : curr->GetRight();

		if (parent == nullptr)
		{
			root = child;
		}
		else if (parent->GetLeft() == curr)
		{
			parent->SetLeft(child);
		}
		else
			parent->SetRight(child);
		delete curr;
		return;
	}

	// here two childs 
	parent = curr;
	Node* successor = curr->GetRight();

	while (successor->GetLeft() != nullptr)
	{
		parent = successor;
		successor = successor->GetLeft();
	}

	curr->SetData(successor->GetData());

	if (parent->GetRight() == successor)
	{
		parent->SetRight(successor->GetRight());
	}
	else
	{
		parent->SetLeft(successor->GetRight());
	}

	delete successor;
}
Node* BinarySearchTree::RDelete(Node* ptr, int val)
{
	if (ptr == nullptr)return nullptr;

	if (val > ptr->GetData())
	{
		ptr->SetRight(RDelete(ptr->GetRight(), val));
	}
	else if (val < ptr->GetData())
	{
		ptr->SetLeft(RDelete(ptr->GetLeft(), val));
	}
	else
	{
		if (ptr->GetLeft() == nullptr || ptr->GetRight() == nullptr)
		{
			Node* child = (ptr->GetLeft() != nullptr) ? ptr->GetLeft() : ptr->GetRight();
			delete ptr;
			return child;
		}
		Node* successor = ptr->GetRight();
		while (successor->GetLeft() != nullptr) {
			successor = successor->GetLeft();
		}
		ptr->SetData(successor->GetData());

		ptr->SetRight(RDelete(ptr->GetRight(), successor->GetData()));
	}
	return ptr;

}
void BinarySearchTree::RDelete(int val) {
	root = RDelete(root, val);
}

Node* BinarySearchTree::ISearch(int val) {
	if (root == nullptr) return nullptr;

	Node* ptr = root;

	while (ptr != nullptr)
	{
		if (ptr->GetData() == val)return ptr;

		if (val > ptr->GetData())
		{
			ptr = ptr->GetRight();
		}
		else
		{
			ptr = ptr->GetLeft();
		}
	}

	return nullptr;
}

Node* BinarySearchTree::RSearch(Node* ptr, int val)
{
	if (ptr == nullptr) return nullptr;
	// root left right (pre order)
	if (val == ptr->GetData()) return ptr;
	if (val < ptr->GetData()) return RSearch(ptr->GetLeft(), val);
	if (val > ptr->GetData()) return RSearch(ptr->GetRight(), val);

	return nullptr;

}
Node* BinarySearchTree::RSearch(int val)
{
	return RSearch(root, val);
}

int BinarySearchTree::IGetHeight()
{
	if (root == nullptr)return 0;
	stack<Node*>s, n;
	s.push(root);
	Node* temp;
	while (!s.empty())
	{
		temp = s.top(); s.pop();
		n.push(temp);

		if (temp->GetLeft() != nullptr)s.push(temp->GetLeft());
		if (temp->GetRight() != nullptr)s.push(temp->GetRight());
	}
	// s is empty and n contains all addresses of all nodes
	int size = n.size();
	Node** arr = new Node * [size];
	for (int i = 0; i < size; i++)
	{
		arr[i] = n.top(); n.pop();
	}
	// now array contains all addresses
	int maxCounter = 0;
	int counter = 0;
	Node* lastParent = nullptr;

	for (int i = 0; i < size; i++)
	{
		lastParent = arr[i];
		counter = 1;
		for (int j = 0; j < size; j++)
		{
			if (arr[j]->GetLeft() == lastParent || arr[j]->GetRight() == lastParent)
			{
				lastParent = arr[j];
				counter++;
			}
		}

		if (counter > maxCounter)
		{
			maxCounter = counter;
		}
	}
	delete[] arr;
	return maxCounter;


}

int BinarySearchTree::IGetHeightQueueMethod()
{
	if (root == nullptr) return 0;
	queue<Node*> q;
	q.push(root);
	Node* temp;
	int height = 0;
	while (!q.empty())
	{
		int levelSize = q.size();
		height++;

		for (int i = 0; i < levelSize; i++)
		{
			temp = q.front(); q.pop();
			if (temp->GetLeft() != nullptr)q.push(temp->GetLeft());
			if (temp->GetRight() != nullptr)q.push(temp->GetRight());
		}

	}
	return height;
}

int BinarySearchTree::RGetHeight(Node* ptr) {

	if (ptr == nullptr) return 0;

	int x = RGetHeight(ptr->GetLeft());
	int y = RGetHeight(ptr->GetRight());

	return (x > y ? x : y) + 1;
}
int BinarySearchTree::RGetHeight() {
	return RGetHeight(root);
}

int BinarySearchTree::RCountNodes(Node* ptr, int degree) {
	if (ptr == nullptr)return 0;
	// post order
	int x = RCountNodes(ptr->GetLeft(), degree);

	int y = RCountNodes(ptr->GetRight(), degree);

	switch (degree)
	{
	case 0: {
		if ((ptr->GetLeft() == nullptr) && (ptr->GetRight() == nullptr))
		{
			return x + y + 1;
		}
		else
		{
			return x + y;
		}
	}
	case 1:
	{
		if ((ptr->GetLeft() != nullptr) ^ (ptr->GetRight() != nullptr))
		{
			return x + y + 1;
		}
		else
		{
			return x + y;
		}
	}
	case 2:
	{
		if ((ptr->GetLeft() != nullptr) && (ptr->GetRight() != nullptr))
		{
			return x + y + 1;
		}
		else
		{
			return x + y;
		}
	}

	default:
		return 0;
	}

}
int BinarySearchTree::RCountNodes(int degree) {
	return RCountNodes(root, degree);
}
int BinarySearchTree::ICountNodes(int degree) {
	if (root == nullptr) return 0;
	if (degree < 0 || degree > 2) return 0;
	// level order
	queue<Node*> q;
	int count = 0;
	q.push(root);
	Node* ptr;

	while (!q.empty())
	{
		ptr = q.front(); q.pop();

		if (degree == 0)
		{
			if ((ptr->GetLeft() == nullptr) && (ptr->GetRight() == nullptr))
				count++;
		}
		else if (degree == 1)
		{
			if ((ptr->GetLeft() != nullptr) ^ (ptr->GetRight() != nullptr))
				count++;
		}
		else if (degree == 2)
		{
			if ((ptr->GetLeft() != nullptr) && (ptr->GetRight() != nullptr))
				count++;
		}

		if (ptr->GetLeft() != nullptr)
			q.push(ptr->GetLeft());
		if (ptr->GetRight() != nullptr)
			q.push(ptr->GetRight());
	}

	return count;
}
void BinarySearchTree::IInDisplay() {
	if (root == nullptr)return;
	stack<Node*>s, parents;
	Node* ptr;
	s.push(root);
	while (!s.empty())
	{
		ptr = s.top(); s.pop();


		if (ptr->GetLeft() != nullptr)
		{
			if (ptr->GetRight() != nullptr)
			{
				s.push(ptr->GetRight());
			}
			s.push(ptr);
			s.push(ptr->GetLeft());
			parents.push(ptr);
		}
		else if (ptr->GetRight() != nullptr)
		{
			s.push(ptr->GetRight());
			cout << ptr->GetData() << " ";
		}
		else {
			cout << ptr->GetData() << " ";
			while (!s.empty() && !parents.empty() && s.top() == parents.top())
			{
				ptr = s.top(); s.pop(); parents.pop();
				cout << ptr->GetData() << " ";
			}
		}
	}
}

void BinarySearchTree::RInDisplay(Node* ptr) {
	if (ptr != nullptr)
	{
		RInDisplay(ptr->GetLeft());
		cout << ptr->GetData() << " ";
		RInDisplay(ptr->GetRight());
	}
}
void BinarySearchTree::RInDisplay() {
	RInDisplay(root);
}
void BinarySearchTree::TestBehavior() {
	cout << "==========================================\n";
	cout << "       Binary Search Tree Test Suite      \n";
	cout << "==========================================\n\n";

	// إنشاء كائن من الشجرة بما أن الدالة static
	BinarySearchTree tree;

	// 1. Testing Insertion (Mixed Iterative & Recursive)
	cout << "[1] Testing Insertion...\n";
	int values[] = { 50, 30, 70, 20, 40, 60, 80, 10, 25, 45, 65, 85, 42 };
	for (int i = 0; i < 13; i++) {
		if (i % 2 == 0) tree.IInsert(values[i]);
		else tree.RInsert(values[i]);
	}
	cout << "Tree built with 13 nodes.\n";

	// 2. Testing Traversals
	cout << "\n[2] Testing Display (In-Order)...\n";
	cout << "Iterative In-Order : "; tree.IInDisplay(); cout << "\n";
	cout << "Recursive In-Order : "; tree.RInDisplay(); cout << "\n";
	// Output should be sorted: 10 20 25 30 40 42 45 50 60 65 70 80 85

	// 3. Testing Height
	cout << "\n[3] Testing Height...\n";
	cout << "Iterative Height (Stack) : " << tree.IGetHeight() << "\n";
	cout << "Iterative Height (Queue) : " << tree.IGetHeightQueueMethod() << "\n";
	cout << "Recursive Height         : " << tree.RGetHeight() << "\n";
	// All should output the same number (4 in this case)

	// 4. Testing Node Counting
	cout << "\n[4] Testing Node Counting...\n";
	cout << "Leaves (Degree 0) -> ICount: " << tree.ICountNodes(0) << " | RCount: " << tree.RCountNodes(0) << "\n";
	cout << "Degree 1 Nodes    -> ICount: " << tree.ICountNodes(1) << " | RCount: " << tree.RCountNodes(1) << "\n";
	cout << "Degree 2 Nodes    -> ICount: " << tree.ICountNodes(2) << " | RCount: " << tree.RCountNodes(2) << "\n";

	// 5. Testing Search
	cout << "\n[5] Testing Search...\n";
	Node* s1 = tree.ISearch(42);
	Node* s2 = tree.RSearch(100);
	cout << "Search 42 (Iterative)  : " << (s1 ? "Found" : "Not Found") << "\n";
	cout << "Search 100 (Recursive) : " << (s2 ? "Found" : "Not Found") << "\n";

	// 6. Testing Deletion (All Cases)
	cout << "\n[6] Testing Deletion...\n";
	cout << "-> Deleting Leaf Node (42) using RDelete...\n";
	tree.RDelete(42);
	cout << "Tree: "; tree.RInDisplay(); cout << "\n\n";

	cout << "-> Deleting Degree 1 Node (40) using IDelete... (45 should take its place)\n";
	tree.IDelete(40);
	cout << "Tree: "; tree.RInDisplay(); cout << "\n\n";

	cout << "-> Deleting Degree 2 Node (50 - Root) using RDelete...\n";
	tree.RDelete(50);
	cout << "Tree: "; tree.RInDisplay(); cout << "\n\n";

	// 7. Testing Clear Functions
	cout << "[7] Testing Clear Tree...\n";
	tree.ILevelClear();
	cout << "Tree cleared using ILevelClear().\n";
	cout << "Height after clear: " << tree.RGetHeight() << " (Should be 0)\n";
	cout << "Tree elements: "; tree.RInDisplay(); cout << "(Should be empty)\n";

	cout << "\n==========================================\n";
	cout << "              Tests Completed             \n";
	cout << "==========================================\n";
}