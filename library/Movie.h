#pragma once

#include <string>
#include <memory>

#include "PriceStrategy.h"
#include "PriceCode.h"

class Movie
{
public:
	explicit Movie(const std::string& title, int priceCode);
	virtual ~Movie();
	std::string title() const;
	int priceCode() const;
   void setPriceCode(int priceCode);
   double Fee(int daysRented) const;

private:
	std::string mTitle;
	// unique_ptr can't be copied?...
	std::shared_ptr<PriceStrategy> mPriceStrategy;
};
