#include "Catalog.h"
#include "Holding.h"
#include "ClassificationData.h"

#include "gmock/gmock.h"

#include <set>
#include <vector>
#include <iostream>

using namespace std;
using namespace ClassificationData;
using namespace testing;

class CatalogTest : public Test
{
public:
    Catalog catalog;
    Holding* theTrialHolding;
    Holding* catch22Holding;
    Holding* catch22HoldingCopy2;

    virtual void SetUp()
    {
        Catalog::DeleteAll();
        theTrialHolding = new Holding(THE_TRIAL_CLASSIFICATION, 1);
        catch22Holding = new Holding(CATCH22_CLASSIFICATION, 1);
        catch22HoldingCopy2 = new Holding(CATCH22_CLASSIFICATION, 2);
    }

    virtual void TearDown()
    {
        delete theTrialHolding;
        delete catch22Holding;
        delete catch22HoldingCopy2;
        Catalog::DeleteAll();
    }
};

TEST_F(CatalogTest, IsEmptyOnCreation)
{
    ASSERT_THAT(catalog.Size(), Eq(0));
}

TEST_F(CatalogTest, AddIncrementsCount)
{
    catalog.Add(*theTrialHolding);

    ASSERT_THAT(catalog.Size(), Eq(1));
}

TEST_F(CatalogTest, FindByBarCodeAnswersFalseWhenNotFound)
{
    Holding holding(THE_TRIAL_CLASSIFICATION, 1);

    ASSERT_THAT(catalog.FindByBarCode(holding), Eq(false));
}

TEST_F(CatalogTest, AddedHoldingCanBeRetrieved)
{
    catalog.Add(*theTrialHolding);
    Holding retrieved(theTrialHolding->Classification(), theTrialHolding->CopyNumber());

    ASSERT_THAT(catalog.FindByBarCode(retrieved), Eq(true));
}

TEST_F(CatalogTest, FindByBarCodePopulatesMembers)
{
    Branch west("1", "West");
    theTrialHolding->Transfer(west);
    catalog.Add(*theTrialHolding);
    Holding holding(THE_TRIAL_CLASSIFICATION, 1);

    catalog.FindByBarCode(holding);

    ASSERT_THAT(holding.CurrentBranch(), Eq(west));
}

TEST_F(CatalogTest, FindByClassificationAnswersMatchingHoldings)
{
    catalog.Add(*theTrialHolding);
    catalog.Add(*catch22Holding);
    catalog.Add(*catch22HoldingCopy2);

    set<Holding> holdings;
    catalog.FindByClassification(CATCH22_CLASSIFICATION, holdings);

    ASSERT_THAT(holdings, Eq(set<Holding>{ *catch22Holding, *catch22HoldingCopy2 }));
}
