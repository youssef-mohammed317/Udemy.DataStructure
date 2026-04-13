#pragma once
class Node
{
	Node* right;
	Node* left;
	int data;
public:
	Node(int data, Node* left = nullptr, Node* right = nullptr);
	~Node();

	int GetData();
	Node* GetRight();
	Node* GetLeft();
	void SetData(int data);
	void SetLeft(Node* left);
	void SetRight(Node* right);
};

