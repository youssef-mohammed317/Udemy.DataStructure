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


void BinarySearchTree::IInsert(int val) {

}

void BinarySearchTree::IDelete(int val) {

}

Node* BinarySearchTree::ISearch(int val) {

}


int BinarySearchTree::GetHeight() {

}

int BinarySearchTree::CountNodes(int degree) {

}

void BinarySearchTree::IInDisplay() {

}

void BinarySearchTree::RInDisplay() {

}

void BinarySearchTree::TestBehavior() {

}