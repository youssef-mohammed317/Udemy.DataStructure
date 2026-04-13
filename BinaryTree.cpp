#include "BinaryTree.h"
BinaryTree::BinaryTree()
{
	root = nullptr;
	count = 0;
}

BinaryTree::~BinaryTree()
{
	IClear();
}

void BinaryTree::IClear()
{
	if (root == nullptr) return;

	std::queue<Node*> q;
	q.push(root);

	while (!q.empty())
	{
		Node* ptr = q.front();
		q.pop();

		if (ptr->GetLeft() != nullptr)
		{
			q.push(ptr->GetLeft());
		}
		if (ptr->GetRight() != nullptr)
		{
			q.push(ptr->GetRight());
		}

		delete ptr;
	}

	root = nullptr;
	count = 0;
}

void BinaryTree::RClear(Node* node)
{
	if (node != nullptr)
	{
		RClear(node->GetRight());
		RClear(node->GetLeft());
		delete node;
	}
}

void BinaryTree::RClear()
{
	RClear(root);
	root = nullptr;
	count = 0;
}


void BinaryTree::IInsert(int data)
{
	Node* node = new Node(data);
	if (root == nullptr)
	{
		root = node;
	}
	else
	{
		queue<Node*>q;
		q.push(root);

		while (!q.empty())
		{
			Node* ptr = q.front();
			q.pop();

			if (ptr->GetLeft() == nullptr)
			{
				ptr->SetLeft(node);
				break;
			}
			else if (ptr->GetRight() == nullptr)
			{
				ptr->SetRight(node);
				break;
			}
			else {
				q.push(ptr->GetLeft());
				q.push(ptr->GetRight());
			}
		}
	}
	count++;
}



Node* BinaryTree::RSearch(Node* node, int val)
{
	if (node == nullptr)
		return nullptr;

	if (node->GetData() == val)
		return node;

	Node* ptr = RSearch(node->GetLeft(), val);
	if (ptr != nullptr)
		return ptr;
	return RSearch(node->GetRight(), val);

}
Node* BinaryTree::RSearch(int val)
{
	return	RSearch(root, val);
}

Node* BinaryTree::ISearch(int val)
{
	if (root == nullptr) return nullptr;

	std::queue<Node*> q;
	q.push(root);

	while (!q.empty())
	{
		Node* ptr = q.front();

		if (ptr->GetData() == val)
			return ptr;


		q.pop();

		if (ptr->GetLeft() != nullptr)
		{
			q.push(ptr->GetLeft());
		}
		if (ptr->GetRight() != nullptr)
		{
			q.push(ptr->GetRight());
		}
	}

	return nullptr;

}


void BinaryTree::RDelete(int val)
{

}

void BinaryTree::IDelete(int val)
{

}

int BinaryTree::GetMaxDegree()
{

}

int BinaryTree::GetHeight()
{

}

int BinaryTree::CountNodes()
{

}

int BinaryTree::CountInternal()
{

}

int BinaryTree::CountExternal()
{

}

int BinaryTree::ICountByDegree(int degree)
{

}

int BinaryTree::RCountByDegree(int degree)
{

}

void BinaryTree::RPostDisplay()
{

}

void BinaryTree::IPostDisplay()
{

}

void BinaryTree::RPreDisplay()
{

}

void BinaryTree::IPreDisplay()
{

}

void BinaryTree::RInDisplay()
{

}

void BinaryTree::IInDisplay()
{

}

void BinaryTree::RLevelDisplay()
{

}

void BinaryTree::ILeverDisplay()
{

}

void BinaryTree::TestBehavior()
{

}