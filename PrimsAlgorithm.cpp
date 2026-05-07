#include "PrimsAlgorithm.h"


std::list<Edge> PrimsAlgorithm::Execute(Graph& graph)
{
	std::list<Edge> result;
	std::list<Edge> edges = graph.GetEdges();
	int vertices = graph.GetVertices();
	int* near = new int[vertices + 1] {0};
	bool* selected = new bool[vertices + 1] {0};

	Edge e = graph.GetMinWeight();
	result.push_back(e);
	selected[e.src] = selected[e.dest] = true;
	for (int i = 1; i <= vertices; i++)
	{
		if (selected[i] == false)
		{
			if (graph.GetWeight(i, e.src) < graph.GetWeight(i, e.dest))
			{
				near[i] = e.src;
			}
			else
			{
				near[i] = e.dest;
			}
		}
	}
	int minWeight = INT_MAX, weight, src, dest;
	for (int k = 1; k <= vertices - 2; k++)
	{
		minWeight = INT_MAX;
		for (int i = 1; i <= vertices; i++)
		{
			if (!selected[i])
			{
				weight = graph.GetWeight(near[i], i);
				if (weight < minWeight)
				{
					minWeight = weight;
					src = near[i];
					dest = i;
				}
			}
		}
		if (minWeight < INT_MAX) {
			result.push_back(Edge(src, dest, minWeight));
			selected[dest] = true;
		}
		else {
			break;// graph disconnected
		}
		for (int i = 1; i <= vertices; i++)
		{
			if (!selected[i])
			{
				if (graph.GetWeight(i, dest) < graph.GetWeight(i, near[i]))
				{
					near[i] = dest;
				}
			}
		}
	}

	delete[]near;
	delete[]selected;
	return result;
}