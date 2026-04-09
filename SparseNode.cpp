#include "SparseNode.h"

SparseNode::SparseNode(int raw, int col, int data, SparseNode* next) {
	this->raw = raw;
	this->col = col;
	this->data = data;
	this->next = next;
}

SparseNode::~SparseNode() {}

int SparseNode::GetRaw() {
	return raw;
}

int SparseNode::GetCol() {
	return col;
}

int SparseNode::GetData() {
	return data;
}

void SparseNode::SetRaw(int raw) {
	this->raw = raw;
}

void SparseNode::SetCol(int col) {
	this->col = col;
}

void SparseNode::SetData(int data) {
	this->data = data;
}

SparseNode* SparseNode::GetNext() {
	return next;
}

void SparseNode::SetNext(SparseNode* next) {
	this->next = next;
}