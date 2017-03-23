#pragma once

#include "PriceStrategy.h"

class NewReleasePriceStrategy : public PriceStrategy
{
public:
	NewReleasePriceStrategy() : PriceStrategy{ PriceCode::NEW_RELEASE } {}

	virtual double Fee(int daysRented) const
	{
		return daysRented * 3;
	}
};
