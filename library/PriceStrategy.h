#pragma once

#include "PriceCode.h"

class PriceStrategy
{
public:
	PriceStrategy() {}
	PriceStrategy(int priceCode)
		: mPriceCode(priceCode)
	{
	}

	virtual ~PriceStrategy() {}

	virtual double Fee(int daysRented) const = 0;

	int PriceCode() const
	{
		return mPriceCode;
	}

private:
	int mPriceCode;
};
