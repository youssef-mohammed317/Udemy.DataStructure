#pragma once
class DoublyNode
{
	int data;
	DoublyNode* next, * prev;
public:
	DoublyNode(int data, DoublyNode* next = nullptr, DoublyNode* prev = nullptr);
	~DoublyNode();

	int GetData() const;
	void SetData(int data);

	void SetNext(DoublyNode* next);
	DoublyNode* GetNext() const;

	void SetPrev(DoublyNode* prev);
	DoublyNode* GetPrev() const;

};

