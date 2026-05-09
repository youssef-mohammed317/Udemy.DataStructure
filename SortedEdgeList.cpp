#include "SortedEdgeList.h"

SortedEdgeList::SortedEdgeList()
{
	head = nullptr;
	count = 0;
}

SortedEdgeList::~SortedEdgeList()
{
	Clear();
}

void SortedEdgeList::Insert(Edge e)
{
	EdgeNode* newNode = new EdgeNode(e);
	count++;

	if (head == nullptr || e.GetWeight() < head->GetEdge().GetWeight())
	{
		newNode->SetNext(head);
		head = newNode;
		return;
	}

	EdgeNode* current = head;

	while (current->GetNext() != nullptr &&
		current->GetNext()->GetEdge().GetWeight() <= e.GetWeight())
	{
		current = current->GetNext();
	}

	newNode->SetNext(current->GetNext());
	current->SetNext(newNode);
}

Edge SortedEdgeList::ExtractFirst()
{
	if (head == nullptr)
	{
		throw std::out_of_range("Cannot extract from an empty edge list.");
	}

	EdgeNode* temp = head;
	Edge extractedEdge = temp->GetEdge();

	head = head->GetNext();

	delete temp;
	count--;

	return extractedEdge;
}

bool SortedEdgeList::IsEmpty() const
{
	return head == nullptr;
}

int SortedEdgeList::GetSize() const
{
	return count;
}

void SortedEdgeList::Clear()
{
	EdgeNode* current = head;
	while (current != nullptr)
	{
		EdgeNode* nextNode = current->GetNext();
		delete current;
		current = nextNode;
	}
	head = nullptr;
	count = 0;
}