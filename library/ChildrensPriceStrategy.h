#pragma once

#include "PriceStrategy.h"

class ChildrensPriceStrategy : public PriceStrategy
{
public:
	ChildrensPriceStrategy() : PriceStrategy{ PriceCode::CHILDRENS } {}

	virtual double Fee(int daysRented) const
	{
		double fee{ 1.5 };
		if (daysRented > 2)
			fee += (daysRented - 2) * 1.5;
		return fee;
	}
};
