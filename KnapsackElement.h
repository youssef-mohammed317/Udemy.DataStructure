#pragma once
class KnapsackElement
{
public:
	int eleNumber;//can be name or eny thing
	double profit;
	double weight;
	double profByWeight;
	KnapsackElement(int eleNumber, double profit, double weight)
	{
		this->eleNumber = eleNumber;
		this->profit = profit;
		this->weight = weight;
		this->profByWeight = profit / weight;
	}
};


