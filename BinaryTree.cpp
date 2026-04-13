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



void BinaryTree::IDelete(int val)
{
	if (root == nullptr) return;
	Node* ptr, * target, * targetParent, * leaf, * leafParent;
	ptr = target = targetParent = leaf = leafParent = nullptr;

	stack<Node*>s;
	queue<Node*>q;
	q.push(root);
	s.push(root);

	while (!q.empty())
	{
		ptr = q.front();
		q.pop();

		if (ptr->GetData() == val)
		{
			target = ptr;
		}

		if (ptr->GetLeft() != nullptr || ptr->GetRight() != nullptr)
		{
			s.push(ptr);

			if (ptr->GetLeft() != nullptr)
			{
				q.push(ptr->GetLeft());
			}

			if (ptr->GetRight() != nullptr)
			{
				q.push(ptr->GetRight());
			}
		}
	}

	if (target == nullptr) return;

	leaf = ptr;
	while (!s.empty() && (leafParent == nullptr || targetParent == nullptr))
	{
		ptr = s.top();
		s.pop();

		if (ptr->GetLeft() == leaf || ptr->GetRight() == leaf)
		{
			leafParent = ptr;
		}
		if (ptr->GetLeft() == target || ptr->GetRight() == target)
		{
			targetParent = ptr;
		}
	}
	if (leafParent != nullptr)
	{
		if (leafParent->GetLeft() == leaf)
		{
			leafParent->SetLeft(nullptr);
		}
		else
		{
			leafParent->SetRight(nullptr);
		}
	}

	if (target == leaf)
	{
		if (target == root)
		{
			root = nullptr;
		}

		delete target;
		return;
	}


	if (target == root)
	{
		// taraget parent is nullptr
		root = leaf;
	}
	else
	{
		if (targetParent->GetLeft() == target)
		{
			targetParent->SetLeft(leaf);
		}
		else
		{
			targetParent->SetRight(leaf);
		}
	}

	leaf->SetRight(target->GetRight());
	leaf->SetLeft(target->GetLeft());

	delete target;

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

bool BinaryTree::IsStrict()
{
	if (root == nullptr)return true;
	queue<Node*>q;
	q.push(root);
	Node* ptr;
	while (!q.empty())
	{
		ptr = q.front(); q.pop();

		if ((ptr->GetLeft() != nullptr) ^ (ptr->GetRight() != nullptr))
			return false;


		if (ptr->GetLeft() != nullptr)
			q.push(ptr->GetLeft());
		if (ptr->GetRight() != nullptr)
			q.push(ptr->GetRight());
	}
	return true;
}

bool BinaryTree::IsComplete()
{
	if (root == nullptr)return true;

	queue<Node*>q;
	q.push(root);
	Node* ptr;
	bool endOfTree = false;
	while (!q.empty())
	{
		ptr = q.front(); q.pop();
		if (ptr == nullptr)
		{
			endOfTree = true;
		}
		else
		{

			if (endOfTree) return false;

			q.push(ptr->GetLeft());
			q.push(ptr->GetRight());
		}
	}
	return true;

}

bool BinaryTree::IsFull()
{
	if (root == nullptr)return true;

	queue<Node*>q;
	q.push(root);
	Node* ptr;
	int expectedNodes = 1, levelSize;
	while (!q.empty())
	{
		levelSize = q.size();

		if (expectedNodes != levelSize) return false;



		for (int i = 0; i < levelSize; i++)
		{
			ptr = q.front();
			q.pop();

			if (ptr->GetLeft() != nullptr)
				q.push(ptr->GetLeft());
			if (ptr->GetRight() != nullptr)
				q.push(ptr->GetRight());
		}

		if (!q.empty())
		{
			expectedNodes *= 2;
		}
	}

	return true;
}


void BinaryTree::RPostDisplay(Node* node)
{
	if (node != nullptr)
	{
		RPostDisplay(node->GetLeft());
		RPostDisplay(node->GetRight());
		cout << node->GetData() << " ";
	}
}
void BinaryTree::RPostDisplay()
{
	RPostDisplay(root);
}

void BinaryTree::RPreDisplay(Node* node)
{
	if (node != nullptr)
	{
		cout << node->GetData() << " ";
		RPreDisplay(node->GetLeft());
		RPreDisplay(node->GetRight());
	}
}

void BinaryTree::RPreDisplay()
{
	RPreDisplay(root);
}
void BinaryTree::RInDisplay(Node* node)
{
	if (node != nullptr)
	{
		RInDisplay(node->GetLeft());
		cout << node->GetData() << " ";
		RInDisplay(node->GetRight());
	}
}

void BinaryTree::RInDisplay()
{
	RInDisplay(root);

}

void BinaryTree::RLevelDisplay(Node* ptr, int level)
{
	if (ptr == nullptr)return;

	if (level == 1)
	{
		cout << ptr->GetData() << " ";
	}
	else if (level > 1)
	{
		RLevelDisplay(ptr->GetLeft(), level - 1);
		RLevelDisplay(ptr->GetRight(), level - 1);
	}


}
void BinaryTree::RLevelDisplay()
{
	if (root == nullptr) return;

	int totalLevels = GetHeight(root);

	for (int i = 1; i <= totalLevels; i++)
	{
		RLevelDisplay(root, i);
	}
}

void BinaryTree::IPreDisplay()
{
	if (root == nullptr) return;
	stack<Node*>s;
	s.push(root);
	Node* ptr;

	while (!s.empty())
	{
		ptr = s.top();
		s.pop();

		cout << ptr->GetData() << " ";

		if (ptr->GetRight() != nullptr)
		{
			s.push(ptr->GetRight());
		}
		if (ptr->GetLeft() != nullptr)
		{
			s.push(ptr->GetLeft());
		}
	}
}

void BinaryTree::IPostDisplay()
{
	if (root == nullptr)return;
	stack<Node*>s;
	Node* ptr, * lastPrinted;
	ptr = lastPrinted = nullptr;
	s.push(root);
	while (!s.empty())
	{
		ptr = s.top(); s.pop();
		if (lastPrinted != nullptr)
		{
			if (ptr->GetLeft() == lastPrinted || ptr->GetRight() == lastPrinted)
			{
				lastPrinted = ptr;
				cout << ptr->GetData() << " ";
				continue;
			}
		}

		if (ptr->GetLeft() != nullptr)
		{
			s.push(ptr);
			if (ptr->GetRight() != nullptr)
			{
				s.push(ptr->GetRight());
			}
			s.push(ptr->GetLeft());
		}
		else if (ptr->GetRight() != nullptr)
		{
			s.push(ptr);
			s.push(ptr->GetRight());
		}
		else
		{
			lastPrinted = ptr;
			cout << ptr->GetData() << " ";
		}
	}

}

void BinaryTree::IInDisplay()
{
	if (root == nullptr)return;
	stack<Node*> s;
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
		}
		else if (ptr->GetRight() != nullptr)
		{
			cout << ptr->GetData() << " ";
			s.push(ptr->GetRight());
		}
		else
		{
			cout << ptr->GetData() << " ";

			while (!s.empty() && ptr->GetRight() != s.top())
			{
				ptr = s.top(); s.pop();
				cout << ptr->GetData() << " ";
			}
		}
	}
}


void BinaryTree::ILeveLDisplay()
{
	if (root == nullptr) return;

	std::queue<Node*> q;
	Node* ptr;
	q.push(root);

	while (!q.empty())
	{
		ptr = q.front();
		q.pop();
		cout << ptr->GetData() << " ";
		if (ptr->GetLeft() != nullptr)
		{
			q.push(ptr->GetLeft());
		}
		if (ptr->GetRight() != nullptr)
		{
			q.push(ptr->GetRight());
		}
	}
}

void BinaryTree::TestBehavior()
{
	cout << "========== Starting Comprehensive BinaryTree Tests ==========\n\n";

	// إنشاء كائن من الشجرة بما أن الدالة Static
	BinaryTree tree;

	// ---------------------------------------------------------
	// 1. اختبار الإدراج (Insertion)
	// ---------------------------------------------------------
	cout << "[1] Testing Insertion (IInsert)...\n";
	int elements[] = { 10, 5, 15, 2, 7, 12, 20 };
	for (int i = 0; i < 7; i++)
	{
		tree.IInsert(elements[i]);
	}
	cout << "Base Tree Created. Level-Order: ";
	tree.ILeveLDisplay(); // Expected: 10 5 15 2 7 12 20
	cout << "\n\n";

	// ---------------------------------------------------------
	// 2. اختبار طرق العرض (Traversals) - التكرارية والعودية
	// ---------------------------------------------------------
	cout << "[2] Testing Traversals...\n";
	cout << "Pre-Order  (Recursive): "; tree.RPreDisplay();   cout << "\n";
	cout << "Pre-Order  (Iterative): "; tree.IPreDisplay();   cout << "\n";
	cout << "In-Order   (Recursive): "; tree.RInDisplay();    cout << "\n";
	cout << "In-Order   (Iterative): "; tree.IInDisplay();    cout << "\n";
	cout << "Post-Order (Recursive): "; tree.RPostDisplay();  cout << "\n";
	cout << "Post-Order (Iterative): "; tree.IPostDisplay();  cout << "\n";
	cout << "Level-Order(Recursive): "; tree.RLevelDisplay(); cout << "\n";
	cout << "Level-Order(Iterative): "; tree.ILeveLDisplay(); cout << "\n\n";

	// ---------------------------------------------------------
	// 3. اختبار الخصائص والعد (Properties & Counts)
	// ---------------------------------------------------------
	cout << "[3] Testing Properties & Counts...\n";
	cout << "Tree Height: " << tree.GetHeight() << " (Expected: 2)\n";
	cout << "Max Degree: " << tree.GetMaxDegree() << " (Expected: 2)\n";
	cout << "Total Nodes: " << tree.CountNodes() << " (Expected: 7)\n";
	cout << "Internal Nodes: " << tree.CountInternal() << " (Expected: 3)\n";
	cout << "External/Leaves: " << tree.CountExternal() << " (Expected: 4)\n";
	cout << "Degree 0 Nodes (Iterative): " << tree.ICountByDegree(0) << " | (Recursive): " << tree.RCountByDegree(0) << "\n";
	cout << "Degree 1 Nodes (Iterative): " << tree.ICountByDegree(1) << " | (Recursive): " << tree.RCountByDegree(1) << "\n";
	cout << "Degree 2 Nodes (Iterative): " << tree.ICountByDegree(2) << " | (Recursive): " << tree.RCountByDegree(2) << "\n\n";

	// ---------------------------------------------------------
	// 4. اختبار أنواع الشجرة (Tree Types)
	// ---------------------------------------------------------
	cout << "[4] Testing Tree Types...\n";
	cout << "Is Strict Tree?   " << (tree.IsStrict() ? "Yes" : "No") << " (Expected: Yes)\n";
	cout << "Is Complete Tree? " << (tree.IsComplete() ? "Yes" : "No") << " (Expected: Yes)\n";
	cout << "Is Full/Max Tree? " << (tree.IsFull() ? "Yes" : "No") << " (Expected: Yes)\n\n";

	// ---------------------------------------------------------
	// 5. اختبار البحث (Search)
	// ---------------------------------------------------------
	cout << "[5] Testing Search Functions...\n";
	Node* search1 = tree.ISearch(15);
	cout << "Iterative Search for 15: " << (search1 != nullptr ? "Found" : "Not Found") << "\n";
	Node* search2 = tree.RSearch(99);
	cout << "Recursive Search for 99: " << (search2 != nullptr ? "Found" : "Not Found") << "\n\n";

	// ---------------------------------------------------------
	// 6. اختبار الحذف (Deletion)
	// ---------------------------------------------------------
	cout << "[6] Testing Deletion (IDelete)...\n";
	cout << "Deleting Leaf Node (7)...\n";
	tree.IDelete(7);
	cout << "Deleting Root Node (10)...\n";
	tree.IDelete(10);
	cout << "Tree after deletions (Level-Order): ";
	tree.ILeveLDisplay();
	cout << "\n\n";

	// ---------------------------------------------------------
	// 7. اختبار تفريغ الذاكرة (Clear Functions)
	// ---------------------------------------------------------
	cout << "[7] Testing Clear Functions...\n";
	tree.IClear();
	cout << "Total Nodes after IClear: " << tree.CountNodes() << " (Expected: 0)\n";

	// إعادة بناء شجرة صغيرة لاختبار الحذف العودي
	tree.IInsert(1); tree.IInsert(2); tree.IInsert(3);
	tree.RClear();
	cout << "Total Nodes after RClear: " << tree.CountNodes() << " (Expected: 0)\n\n";

	cout << "========== All Tests Completed Successfully ==========\n";
}