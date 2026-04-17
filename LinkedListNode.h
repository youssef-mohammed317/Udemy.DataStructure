#pragma once
class LinkedListNode
{

	LinkedListNode* next;
	int data;
public:
	LinkedListNode(int data, LinkedListNode* next = nullptr);
	~LinkedListNode();

	int GetData();
	LinkedListNode* GetNext();
	void SetData(int data);
	void SetNext(LinkedListNode* right);
};

