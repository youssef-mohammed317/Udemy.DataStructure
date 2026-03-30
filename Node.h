#pragma once

class Node
{
	Node* next;
	int data;
public:
	Node(int data, Node* next = nullptr);

	~Node();

	int GetData() const;

	Node* GetNext() const;

	void SetData(int data);

	void SetNext(Node* next);

};

