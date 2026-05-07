#include "DijkstraAlgorithm.h"


std::list<Edge>* DijkstraAlgorithm::Execute(Graph graph, int source)
{
	int vertices = graph.GetVertices();
	bool* selected = new bool[vertices + 1] {0};
	int* distances = new int[vertices + 1] {0};
	for (int i = 1; i <= vertices; i++)
		distances[i] = INT_MAX;
	distances[source] = 0;
	selected[source] = true;

	std::list<Edge>* result = new std::list<Edge>[vertices + 1];
	int weight, minWeight, dest = source, src = source;
	for (int k = 1; k < vertices; k++)
	{
		minWeight = INT_MAX;
		for (int i = 1; i <= vertices; i++)
		{
			if (!selected[i] && distances[i] < minWeight)
			{
				minWeight = distances[i];
				src = i;
			}
		}
		selected[src] = true;
		for (dest = 1; dest <= vertices; dest++)
		{
			if (!selected[dest])
			{
				weight = graph.GetWeight(src, dest);
				if (weight != INT_MAX && weight + distances[src] < distances[dest])
				{
					distances[dest] = weight + distances[src];
					// result[dest] = (result[src] + Edge(src, dest, weight));
					// Pseudocode idea: Copy the shortest path of 'src' and append the new edge to it.
					// Note: C++ std::list doesn't support the '+' operator for appending elements, 
					// so we manually copy the previous path and push the new edge below.
					result[dest].clear();
					for (Edge& e : result[src])
					{
						result[dest].push_back(e);
					}
					result[dest].push_back(Edge(src, dest, weight));
				}
			}
		}
	}

	delete[]selected;
	delete[]distances;
	return result;
}