#include "Node.h"

Node::Node(int data, Node* right, Node* left)
{
	this->data = data;
	this->right = right;
	this->left = left;
}

Node::~Node()
{}

int Node::GetData()
{
	return data;
}

Node* Node::GetRight()
{
	return right;
}

Node* Node::GetLeft()
{
	return left;
}

void Node::SetData(int data)
{
	this->data = data;
}

void Node::SetLeft(Node* left)
{
	this->left = left;
}

void Node::SetRight(Node* right)
{
	this->right = right;
}