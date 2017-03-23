#include "gmock/gmock.h"

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
