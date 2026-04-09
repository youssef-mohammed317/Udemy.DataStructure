#pragma once
class SparseNode
{
	int raw;
	int col;
	int data;
	SparseNode* next;
public:
	SparseNode(int raw, int col, int data, SparseNode* next = nullptr);
	~SparseNode();

	int GetRaw();
	int GetCol();
	int GetData();
	SparseNode* GetNext();
	void SetCol(int col);
	void SetRaw(int raw);
	void SetData(int data);
	void SetNext(SparseNode* next);
};

