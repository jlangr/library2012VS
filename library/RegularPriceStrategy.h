#pragma once

#include "PriceStrategy.h"

class RegularPriceStrategy : public PriceStrategy
{
public:
	RegularPriceStrategy() : PriceStrategy{ PriceCode::REGULAR } {}

	virtual double Fee(int daysRented) const
	{
		auto fee{ 2.0 };
		if (daysRented > 2)
			fee += (daysRented - 2) * 1.5;
		return fee;
	}
};
