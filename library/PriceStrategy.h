#pragma once

class PriceStrategy
{
public:
	PriceStrategy() {}
	PriceStrategy(int priceCode)
		: mPriceCode(priceCode)
	{
	}

	~PriceStrategy() {}

private:
	int mPriceCode;
};
