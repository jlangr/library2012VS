#include <string>

#include "Movie.h"
#include "PriceCode.h"
#include "PriceStrategy.h"
#include "RegularPriceStrategy.h"
#include "ChildrensPriceStrategy.h"
#include "NewReleasePriceStrategy.h"

using namespace std;

Movie::Movie(const std::string& title, int priceCode)
	: mTitle(title)
{
	setPriceCode(priceCode);
}

Movie::~Movie()
{
}

double Movie::Fee(int daysRented) const
{
	return mPriceStrategy->Fee(daysRented);
}

std::string Movie::title() const
{
	return mTitle;
}

int Movie::priceCode() const
{
	return mPriceStrategy->PriceCode();
}

void Movie::setPriceCode(int priceCode)
{
	switch (priceCode)
	{
	case PriceCode::REGULAR:
		mPriceStrategy = make_shared<RegularPriceStrategy>();
		break;
	case PriceCode::NEW_RELEASE:
		mPriceStrategy = make_shared<NewReleasePriceStrategy>();
		break;
	case PriceCode::CHILDRENS:
		mPriceStrategy = make_shared<ChildrensPriceStrategy>();
		break;
	}
}
