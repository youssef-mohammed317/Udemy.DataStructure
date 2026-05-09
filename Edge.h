#pragma once 

class Edge
{
private:
	int src, dest, weight;

public:
	Edge(int src = 0, int dest = 0, int weight = 0);
	Edge(const Edge& other);

	int GetSrc() const;
	int GetDest() const;
	int GetWeight() const;

	void SetSrc(int src);
	void SetDest(int dest);
	void SetWeight(int weight);

	Edge GetNormalized() const;

	Edge& operator=(const Edge& other);
	bool operator==(const Edge& other) const;
};