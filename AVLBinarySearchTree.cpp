#include "AVLBinarySearchTree.h"

int AVLBinarySearchTree::GetHeight(Node* ptr)
{
	if (ptr == nullptr)return 0;

	int lh = GetHeight(ptr->GetLeft());
	int rh = GetHeight(ptr->GetRight());

	return (lh > rh ? lh : rh) + 1;
}
int AVLBinarySearchTree::GetBalanceFactor(Node* ptr)
{
	if (ptr == nullptr)return 0;
	int lh = GetHeight(ptr->GetLeft());
	int rh = GetHeight(ptr->GetRight());
	return lh - rh;
}
void AVLBinarySearchTree::Clear(Node* ptr)
{
	if (ptr == nullptr)return;

	Clear(ptr->GetLeft());
	Clear(ptr->GetRight());
	delete ptr;
}

Node* AVLBinarySearchTree::LLRotation(Node* ptr)
{

	Node* pl = ptr->GetLeft();

	Node* plr = ptr->GetLeft()->GetRight();

	pl->SetRight(ptr);
	ptr->SetLeft(plr);

	return pl;
}
Node* AVLBinarySearchTree::LRRotation(Node* ptr)
{

	Node* pl = ptr->GetLeft();

	Node* plr = ptr->GetLeft()->GetRight();

	pl->SetRight(plr->GetLeft());
	ptr->SetLeft(plr->GetRight());
	plr->SetLeft(pl);
	plr->SetRight(ptr);

	return plr;
}
Node* AVLBinarySearchTree::RLRotation(Node* ptr)
{

	Node* pr = ptr->GetRight();

	Node* prl = ptr->GetRight()->GetLeft();

	pr->SetLeft(prl->GetRight());
	ptr->SetRight(prl->GetLeft());
	prl->SetLeft(ptr);
	prl->SetRight(pr);

	return prl;
}

Node* AVLBinarySearchTree::RRRotation(Node* ptr)
{

	Node* pr = ptr->GetRight();

	Node* prl = ptr->GetRight()->GetLeft();

	pr->SetLeft(ptr);
	ptr->SetRight(prl);

	return pr;
}


Node* AVLBinarySearchTree::Insert(Node* ptr, int val)
{
	if (ptr == nullptr)
	{
		ptr = new Node(val);
	}
	else
	{
		if (val > ptr->GetData())
			ptr->SetRight(Insert(ptr->GetRight(), val));
		else if (val < ptr->GetData())
			ptr->SetLeft(Insert(ptr->GetLeft(), val));
	}

	int rootBalanceFactor = GetBalanceFactor(ptr);
	int leftBalanceFactor = GetBalanceFactor(ptr->GetLeft());
	int rightBalanceFactor = GetBalanceFactor(ptr->GetRight());

	if (rootBalanceFactor == 2 && leftBalanceFactor == 1)
	{
		// left left rotation
		return LLRotation(ptr);
	}
	else if (rootBalanceFactor == 2 && leftBalanceFactor == -1)
	{
		// left right rotation
		return LRRotation(ptr);
	}
	else if (rootBalanceFactor == -2 && rightBalanceFactor == 1)
	{
		// right left rotation
		return RLRotation(ptr);
	}
	else if (rootBalanceFactor == -2 && rightBalanceFactor == -1)
	{
		// right right rotation
		return RRRotation(ptr);
	}

	return ptr;
}

Node* AVLBinarySearchTree::Delete(Node* ptr, int val)
{
	if (ptr == nullptr) return nullptr;

	if (val > ptr->GetData())
	{

		ptr->SetRight(Delete(ptr->GetRight(), val));
	}
	else if (val < ptr->GetData())
	{
		ptr->SetLeft(Delete(ptr->GetLeft(), val));
	}
	else if (val == ptr->GetData())
	{
		if (ptr->GetLeft() == nullptr || ptr->GetRight() == nullptr)
		{

			// one child or leaf
			Node* child = ptr->GetRight() != nullptr ? ptr->GetRight() : ptr->GetLeft();
			delete ptr;
			return child;
		}
		else
		{
			// two childs 
			Node* successor = ptr->GetRight();
			while (successor->GetLeft() != nullptr)
			{
				successor = successor->GetLeft();
			}
			ptr->SetData(successor->GetData());

			ptr->SetRight(Delete(ptr->GetRight(), successor->GetData()));
		}
	}

	int rootBalanceFactor = GetBalanceFactor(ptr);
	int leftBalanceFactor = GetBalanceFactor(ptr->GetLeft());
	int rightBalanceFactor = GetBalanceFactor(ptr->GetRight());

	if (rootBalanceFactor == 2 && leftBalanceFactor >= 0)
		return LLRotation(ptr);
	else if (rootBalanceFactor == 2 && leftBalanceFactor == -1)
		return LRRotation(ptr);
	else if (rootBalanceFactor == -2 && rightBalanceFactor == 1)
		return RLRotation(ptr);
	else if (rootBalanceFactor == -2 && rightBalanceFactor <= 0)
		return RRRotation(ptr);

	return ptr;
}
void AVLBinarySearchTree::Display(Node* ptr)
{
	if (ptr == nullptr) return;


	Display(ptr->GetLeft());
	std::cout << ptr->GetData() << " ";
	Display(ptr->GetRight());

}

AVLBinarySearchTree::AVLBinarySearchTree()
{
	root = nullptr;
}
AVLBinarySearchTree::~AVLBinarySearchTree()
{
	Clear();
}
void AVLBinarySearchTree::Clear()
{
	Clear(root);
	root = nullptr;
}
void AVLBinarySearchTree::Insert(int val)
{
	root = Insert(root, val);
}
void AVLBinarySearchTree::Delete(int val)
{
	root = Delete(root, val);
}
void AVLBinarySearchTree::Display()
{
	std::cout << "{";
	Display(root);
	std::cout << "}\n";
}

void AVLBinarySearchTree::TestBehavior() {
	std::cout << "==========================================\n";
	std::cout << "          AVL Tree Test Suite             \n";
	std::cout << "==========================================\n\n";

	AVLBinarySearchTree tree;

	std::cout << "[1] Testing RR Rotation (Right Heavy)...\n";
	std::cout << "Inserting 10, 20, 30...\n";
	tree.Insert(10);
	tree.Insert(20);
	tree.Insert(30); // هنا سيحدث دوران RR لتصبح 20 هي الجذر
	std::cout << "Tree (In-Order): "; tree.Display();

	std::cout << "\n[2] Testing LL Rotation (Left Heavy)...\n";
	std::cout << "Inserting 5, 2...\n";
	tree.Insert(5);
	tree.Insert(2); // هنا سيحدث دوران LL
	std::cout << "Tree (In-Order): "; tree.Display();

	std::cout << "\n[3] Testing Complex Deletions...\n";
	std::cout << "Deleting 20 (Root Node)...\n";
	tree.Delete(20); // سيتم استبدالها بـ 30، وقد يحدث دوران للحفاظ على التوازن
	std::cout << "Tree (In-Order): "; tree.Display();

	std::cout << "\n==========================================\n";
	std::cout << "              Tests Completed             \n";
	std::cout << "==========================================\n";
}