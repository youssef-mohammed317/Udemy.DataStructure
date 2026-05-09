#include "Edge.h"
#include "Edge.h"

Edge::Edge(int src, int dest, int weight)
{
	this->src = src;
	this->dest = dest;
	this->weight = weight;
}

Edge::Edge(const Edge& other)
{
	this->src = other.src;
	this->dest = other.dest;
	this->weight = other.weight;
}

int Edge::GetSrc() const
{
	return src;
}

int Edge::GetDest() const
{
	return dest;
}

int Edge::GetWeight() const
{
	return weight;
}

void Edge::SetSrc(int src)
{
	this->src = src;
}

void Edge::SetDest(int dest)
{
	this->dest = dest;
}

void Edge::SetWeight(int weight)
{
	this->weight = weight;
}

Edge Edge::GetNormalized() const
{
	if (this->src > this->dest)
	{
		return Edge(this->dest, this->src, this->weight);
	}

	return *this;
}

Edge& Edge::operator=(const Edge& other)
{
	if (this != &other)
	{
		this->src = other.src;
		this->dest = other.dest;
		this->weight = other.weight;
	}
	return *this;
}

bool Edge::operator==(const Edge& other) const
{
	return (this->src == other.src &&
		this->dest == other.dest &&
		this->weight == other.weight);
}