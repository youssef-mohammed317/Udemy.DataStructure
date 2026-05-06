#pragma once
#include<list>
#include<stdexcept>
using namespace std;
struct KnapsackElement {
	int id;
	double weight;
	double profit;
	double profitByWeight;
	struct KnapsackElement(int id, double wieght, double profit)
	{
		this->id = id;
		this->weight = wieght;
		this->profit = profit;
		this->profitByWeight = profit / weight;
	}
};
class KnapsackAlgorithm
{
	list<KnapsackElement> FractionalSolution(list<KnapsackElement> lst, double maxWeight);
};

