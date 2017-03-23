#include "Movie.h"
#include <string>
#include "PriceCode.h"

Movie::Movie(const std::string& title, int priceCode)
	: mTitle(title)
	, mPriceCode(priceCode)
{
}

Movie::~Movie()
{
}

double Movie::Fee(int daysRented) const
{
	auto fee{ 0.0 };
	switch (priceCode()) {

	case PriceCode::REGULAR:
		fee += 2;
		if (daysRented > 2)
			fee += (daysRented - 2) * 1.5;
		break;

	case PriceCode::NEW_RELEASE:
		fee += daysRented * 3;
		break;

	case PriceCode::CHILDRENS:
		fee += 1.5;
		if (daysRented > 2)
			fee += (daysRented - 2) * 1.5;
		break;
	}
	return fee;
}

std::string Movie::title() const
{
	return mTitle;
}

int Movie::priceCode() const
{
	return mPriceCode;
}

void Movie::setPriceCode(int priceCode)
{
	mPriceCode = priceCode;
}
