#include "gmock/gmock.h"

#include <exception>

#include "Portfolio.h"

using namespace std;
using namespace testing;

class APortfolio : public testing::Test
{
public:
	Portfolio portfolio;

	void SetUp() {
	}
};

TEST_F(APortfolio, IsEmptyWhenCreated)
{
	ASSERT_THAT(portfolio.IsEmpty(), Eq(true));
}

TEST_F(APortfolio, IsNotEmptyAfterPurchase)
{
	portfolio.Purchase("IBM", 10);

	ASSERT_THAT(portfolio.IsEmpty(), Eq(false));
}

TEST_F(APortfolio, HasSizeZeroWhenCreated)
{
	ASSERT_THAT(portfolio.Size(), Eq(0));
}

TEST_F(APortfolio, IncrementsSizeOnPurchase)
{
	portfolio.Purchase("IBM", 10);

	ASSERT_THAT(portfolio.Size(), Eq(1));
}

TEST_F(APortfolio, DoesNotIncrementSizeOnPurchaseSameSymbol)
{
	portfolio.Purchase("IBM", 10);
	portfolio.Purchase("IBM", 20);

	ASSERT_THAT(portfolio.Size(), Eq(1));
}

TEST_F(APortfolio, AnswersZeroForSharesOfUnpurchasedSymbol)
{
	ASSERT_THAT(portfolio.Shares("IBM"), Eq(0));
}

TEST_F(APortfolio, ReturnsOnlySharesSpecificToPurchase)
{
	portfolio.Purchase("IBM", 20);
	portfolio.Purchase("LUV", 10);

	ASSERT_THAT(portfolio.Shares("IBM"), Eq(20));
}

TEST_F(APortfolio, SumsSharesForPurchaseOfSameSymbol)
{
	portfolio.Purchase("IBM", 20);
	portfolio.Purchase("IBM", 10);

	ASSERT_THAT(portfolio.Shares("IBM"), Eq(20 + 10));
}

TEST_F(APortfolio, ReducesSharesOnSell)
{
	portfolio.Purchase("IBM", 20);

	portfolio.Sell("IBM", 15);

	ASSERT_THAT(portfolio.Shares("IBM"), Eq(20 - 15));
}

TEST_F(APortfolio, RemovesSymbolWhenAllSharesSold)
{
	portfolio.Purchase("IBM", 20);

	portfolio.Sell("IBM", 20);

	ASSERT_THAT(portfolio.Size(), Eq(0));
}

TEST_F(APortfolio, ThrowsOnPurchaseOfZeroShares)
{
	ASSERT_THROW(portfolio.Purchase("IBM", 0), std::exception);
}

TEST_F(APortfolio, ThrowsWhenSellingTooManyShares)
{
	ASSERT_THROW(portfolio.Sell("IBM", 1), std::exception);
}