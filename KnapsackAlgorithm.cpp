#include "KnapsackAlgorithm.h"


list<KnapsackElement> KnapsackAlgorithm::FractionalSolution(list<KnapsackElement> lst, double maxweight)
{
	if (lst.size() < 1 || maxweight <= 0)
	{
		throw exception("invalid input");
	}
	lst.sort([](const KnapsackElement& a, const KnapsackElement& b) {
		return a.profitByWeight > b.profitByWeight;
		});

	list<KnapsackElement>res;
	for (KnapsackElement& k : lst)
	{
		if (maxweight >= k.weight)
		{
			res.push_back(k);
		}
		else {
			k.weight = maxweight;
			k.profit = maxweight * k.profitByWeight;
			res.push_back(k);
		}
		maxweight -= k.weight;
		if (maxweight == 0)
			break;
	}
	return res;
}