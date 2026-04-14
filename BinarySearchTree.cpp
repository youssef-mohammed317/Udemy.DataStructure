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

}
void BinarySearchTree::RDelete(int val) {

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

}