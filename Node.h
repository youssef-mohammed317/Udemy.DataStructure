#pragma once
class Node {
	int data;
	Node* next;
public:
	Node(int data = 0, Node* next = nullptr);
	~Node();

	void SetData(int data);
	int GetData();
	Node* GetNext();
	void SetNext(Node* next);

};
