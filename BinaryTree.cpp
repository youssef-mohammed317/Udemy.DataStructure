#include "BinaryTree.h"
BinaryTree::BinaryTree()
{
	root = nullptr;
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
	Node* ptr;
	q.push(root);

	while (!q.empty())
	{
		ptr = q.front();

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
	if (root == nullptr) return 0;

	int maxDegree = 0;
	queue<Node*>q;
	q.push(root);
	Node* ptr;
	while (!q.empty())
	{
		ptr = q.front();

		q.pop();

		if (ptr->GetLeft() != nullptr)
		{
			q.push(ptr->GetLeft());
			maxDegree = 1;
		}
		if (ptr->GetRight() != nullptr)
		{
			q.push(ptr->GetRight());
			maxDegree = 1;
		}
		if (ptr->GetLeft() != nullptr && ptr->GetRight() != nullptr)
			return 2;

	}
	return maxDegree;
}

int BinaryTree::GetHeight(Node* node)
{
	if (node == nullptr) return 0;

	int x = GetHeight(node->GetLeft());
	int y = GetHeight(node->GetRight());

	return (x > y ? x : y) + 1;
}
int BinaryTree::GetHeight()
{
	return GetHeight(root) - 1; // height start form 0
}

int BinaryTree::CountNodes()
{
	if (root == nullptr) return 0;

	int count = 0;
	queue<Node*>q;
	q.push(root);
	Node* ptr;
	while (!q.empty())
	{
		ptr = q.front();

		q.pop();
		count++;

		if (ptr->GetLeft() != nullptr)
		{
			q.push(ptr->GetLeft());
		}
		if (ptr->GetRight() != nullptr)
		{
			q.push(ptr->GetRight());
		}

	}
	return count;
}

int BinaryTree::CountInternal()
{
	if (root == nullptr) return -1;

	int count = 0;
	queue<Node*>q;
	q.push(root);
	Node* ptr;
	while (!q.empty())
	{
		ptr = q.front();
		q.pop();

		if (ptr->GetLeft() != nullptr)
		{
			q.push(ptr->GetLeft());
		}
		if (ptr->GetRight() != nullptr)
		{
			q.push(ptr->GetRight());
		}

		if (ptr->GetLeft() != nullptr || ptr->GetRight() != nullptr)
			count++;

	}
	return count;
}

int BinaryTree::CountExternal()
{
	if (root == nullptr) return -1;

	int count = 0;
	queue<Node*>q;
	q.push(root);
	Node* ptr;
	while (!q.empty())
	{
		ptr = q.front();
		q.pop();

		if (ptr->GetLeft() != nullptr)
		{
			q.push(ptr->GetLeft());
		}
		if (ptr->GetRight() != nullptr)
		{
			q.push(ptr->GetRight());
		}

		if (ptr->GetLeft() == nullptr && ptr->GetRight() == nullptr)
			count++;

	}
	return count;
}

int BinaryTree::ICountByDegree(int degree)
{
	if (root == nullptr) return 0;

	if (degree > 2 || degree < 0)return 0;

	int count = 0;
	queue<Node*>q;
	q.push(root);
	Node* ptr;
	while (!q.empty())
	{
		ptr = q.front();
		q.pop();

		if (ptr->GetLeft() != nullptr)
		{
			q.push(ptr->GetLeft());
		}
		if (ptr->GetRight() != nullptr)
		{
			q.push(ptr->GetRight());
		}


		if (degree == 0)
		{
			if (ptr->GetLeft() == nullptr && ptr->GetRight() == nullptr)
				count++;
		}
		else if (degree == 1)
		{
			if ((ptr->GetLeft() != nullptr) ^ (ptr->GetRight() != nullptr))
				count++;
		}
		else if (degree == 2)
		{
			if (ptr->GetLeft() != nullptr && ptr->GetRight() != nullptr)
				count++;
		}
		else
			return 0;



	}
	return count;
}

void BinaryTree::RCountByDegree(Node* ptr, int degree, int& count)
{
	if (ptr == nullptr) return;

	if (degree == 0)
	{
		if (ptr->GetLeft() == nullptr && ptr->GetRight() == nullptr)
			count++;
	}
	else if (degree == 1)
	{
		if ((ptr->GetLeft() != nullptr) ^ (ptr->GetRight() != nullptr))
			count++;
	}
	else if (degree == 2)
	{
		if (ptr->GetLeft() != nullptr && ptr->GetRight() != nullptr)
			count++;
	}

	RCountByDegree(ptr->GetLeft(), degree, count);
	RCountByDegree(ptr->GetRight(), degree, count);
}
int BinaryTree::RCountByDegree(int degree)
{
	if (root == nullptr) return 0;

	if (degree > 2 || degree < 0) return 0;

	int count = 0;

	RCountByDegree(root, degree, count);

	return count;

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

void BinaryTree::ILeveLDisplay()
{

}

void BinaryTree::TestBehavior()
{

}