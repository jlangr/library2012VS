#include "gmock/gmock.h"

#include <exception>

#include "Portfolio.h"
#include "StockService.h"

using namespace std;
using namespace testing;

//class StubStockService : public StockService
//{
//public:
//	static const unsigned int LUV_PRICE_PER_SHARE{ 100 };
//	static const unsigned int IBM_PRICE_PER_SHARE{ 80 };
//
//	virtual unsigned int CurrentPrice(const std::string& symbol)
//	{
//		if (symbol == "IBM")
//			return IBM_PRICE_PER_SHARE;
//		if (symbol == "LUV")
//			return LUV_PRICE_PER_SHARE;
//		throw "unknown symbol";
//	}
//};
class StubStockService : public StockService
{
public:
	static const unsigned int LUV_PRICE_PER_SHARE{ 100 };
	static const unsigned int IBM_PRICE_PER_SHARE{ 80 };

	MOCK_METHOD1(CurrentPrice, unsigned int(const std::string&));
};

class APortfolio : public testing::Test
{
public:
	Portfolio portfolio;
	StubStockService stockService;

	void SetUp() {
		portfolio.SetStockService(&stockService);
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

TEST_F(APortfolio, IsWorthlessWhenCreated)
{
	ASSERT_THAT(portfolio.Value(), Eq(0));
}

TEST_F(APortfolio, DISABLED_IsWorthPriceOfSymbolForSingleSharePurchase)
{
	portfolio.Purchase("LUV", 1);

	ASSERT_THAT(portfolio.Value(), Eq(StubStockService::LUV_PRICE_PER_SHARE));
}

TEST_F(APortfolio, DISABLED_ValueMultipliesPriceByNumberOfShares)
{
	portfolio.Purchase("LUV", 10);

	ASSERT_THAT(portfolio.Value(),
		Eq(StubStockService::LUV_PRICE_PER_SHARE * 10));
}

TEST_F(APortfolio, AccumulatesValueForAllHoldings)
{
	EXPECT_CALL(stockService, CurrentPrice("IBM"))
		.WillOnce(Return(StubStockService::IBM_PRICE_PER_SHARE));
	EXPECT_CALL(stockService, CurrentPrice("LUV"))
		.WillOnce(Return(StubStockService::LUV_PRICE_PER_SHARE));

	portfolio.Purchase("LUV", 10);
	portfolio.Purchase("IBM", 20);

	ASSERT_THAT(portfolio.Value(), Eq(
		StubStockService::IBM_PRICE_PER_SHARE * 20 +
		StubStockService::LUV_PRICE_PER_SHARE * 10));
}

class Real
{
public:
	virtual string Alpha(string s) {
		throw 1;
	}
	virtual string Alpha(int x) {
		throw 1;
	}
	virtual int Beta(int x) {
		throw 1;
	}
};

class MockReal : public Real
{
public:
	MOCK_METHOD1(Alpha, string(string));
	MOCK_METHOD1(Alpha, string(int));
	MOCK_METHOD1(Beta, int(int));
};

TEST(SomeRealStuff, ForReal)
{
	MockReal mock;

	InSequence dummy;

	EXPECT_CALL(mock, Alpha(A<string>()))
		.WillOnce(Return("hello"));

	ASSERT_THAT(mock.Alpha("1 12 3 4"), Eq("hello"));

}