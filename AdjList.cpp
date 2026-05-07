#include "AdjList.h"

AdjList::AdjList()
{
	this->source = 0;
	this->size = 0;
	this->head = nullptr;
	this->tail = nullptr;
}

AdjList::AdjList(int source)
{
	this->source = source;
	this->size = 0;
	this->head = nullptr;
	this->tail = nullptr;
}

AdjList::AdjList(const AdjList& other)
{
	this->source = other.source;
	this->size = 0;
	this->head = nullptr;
	this->tail = nullptr;

	AdjNode* current = other.head;
	while (current != nullptr)
	{
		this->AddEdge(current->GetDest(), current->GetWeight());
		current = current->GetNext();
	}
}

AdjList::~AdjList()
{
	Clear();
}

AdjList& AdjList::operator=(const AdjList& other)
{
	if (this != &other)
	{
		Clear();

		this->source = other.source;

		AdjNode* current = other.head;
		while (current != nullptr)
		{
			this->AddEdge(current->GetDest(), current->GetWeight());
			current = current->GetNext();
		}
	}
	return *this;
}

int AdjList::GetSource() const { return source; }
int AdjList::GetSize() const { return size; }
AdjNode* AdjList::GetHead() const { return head; }
AdjNode* AdjList::GetTail() const { return tail; }

void AdjList::SetSource(int source) { this->source = source; }

void AdjList::AddEdge(int dest, int weight)
{
	AdjNode* newNode = new AdjNode(dest, weight);

	if (head == nullptr)
	{
		head = newNode;
		tail = newNode;
	}
	else
	{
		tail->SetNext(newNode);
		tail = newNode;
	}
	size++;
}

void AdjList::RemoveEdge(int dest)
{
	if (head == nullptr)
	{
		return;
	}

	if (head->GetDest() == dest)
	{
		AdjNode* temp = head;
		head = head->GetNext();
		if (head == nullptr)
		{
			tail = nullptr;
		}
		delete temp;
		size--;
		return;
	}

	AdjNode* current = head;
	while (current->GetNext() != nullptr && current->GetNext()->GetDest() != dest)
	{
		current = current->GetNext();
	}

	if (current->GetNext() != nullptr)
	{
		AdjNode* temp = current->GetNext();
		current->SetNext(temp->GetNext());

		if (temp == tail)
		{
			tail = current;
		}

		delete temp;
		size--;
	}
}

bool AdjList::HasEdge(int dest) const
{
	AdjNode* current = head;
	while (current != nullptr)
	{
		if (current->GetDest() == dest)
		{
			return true;
		}
		current = current->GetNext();
	}
	return false;
}

int AdjList::GetWeight(int dest) const
{
	AdjNode* current = head;
	while (current != nullptr)
	{
		if (current->GetDest() == dest)
		{
			return current->GetWeight();
		}
		current = current->GetNext();
	}
	throw std::invalid_argument("Edge not found in the adjacency list.");
}

void AdjList::Clear()
{
	AdjNode* current = head;
	while (current != nullptr)
	{
		AdjNode* temp = current;
		current = current->GetNext();
		delete temp;
	}

	head = nullptr;
	tail = nullptr;
	size = 0;
}

void AdjList::Print() const
{
	std::cout << "Source Node: " << source << " | Total Connections: " << size << "\n";
	AdjNode* current = head;
	if (current == nullptr)
	{
		std::cout << "  [Empty List]\n";
	}
	while (current != nullptr)
	{
		std::cout << "  -> Dest: " << current->GetDest() << " | Cost: " << current->GetWeight() << "\n";
		current = current->GetNext();
	}
	std::cout << "\n";
}