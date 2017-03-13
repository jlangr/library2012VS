#include "gmock/gmock.h"
#include "Holding.h"
#include "Book.h"
#include "ClassificationData.h"
#include "BranchTestData.h"
#include "Branch.h"
#include "InvalidBarcodeException.h"
#include "boost/date_time/gregorian/gregorian_types.hpp"

using namespace boost::gregorian;
using namespace BranchTestData;
using namespace ClassificationData;
using namespace std;
using namespace testing;

class HoldingTest : public Test
{
public:
    Holding* holding;
    static const date ARBITRARY_DATE;
    virtual void SetUp()
    {
        holding = new Holding(THE_TRIAL_CLASSIFICATION, 1);
    }

    virtual void TearDown()
    {
        delete holding;
    }

    void VerifyAvailability(const Branch& branch)
    {
        ASSERT_THAT(holding->CurrentBranch(), Eq(branch));
        ASSERT_THAT(holding->IsAvailable(), Eq(branch != Branch::CHECKED_OUT));
    }

    bool IsAvailableAt(Holding* holding, Branch& branch)
    {
        return holding->CurrentBranch() == branch &&
            holding->IsAvailable();
    }

    void MakeAvailableAtABranch(Holding* holding)
    {
        holding->Transfer(EAST_BRANCH);
    }
};

const date HoldingTest::ARBITRARY_DATE(2013, Jan, 1);

TEST_F(HoldingTest, BarcodeRequiresColon)
{
    ASSERT_THROW(Holding("A"), InvalidBarcodeException);
}

TEST_F(HoldingTest, CanExtractClassificationWhenCreatedWithBarcode)
{
    Holding holding(Holding::ConstructBarcode("A123", 3));

    ASSERT_THAT(holding.Classification(), Eq("A123"));
}

TEST_F(HoldingTest, CanExtractCopyNumberWhenCreatedWithBarcode)
{
	try {
		Holding h(Holding::ConstructBarcode("A234", 5));

		ASSERT_THAT(h.CopyNumber(), Eq(5));
	}
	catch (...)
	{
		FAIL();
		cout << "failed test avail" << endl;
	}
}

TEST_F(HoldingTest, IsNotAvailableWhenCreated)
{
	cout << "vavail test" << endl;
	try {
		Holding holding(Holding::ConstructBarcode("A", 1));

		ASSERT_THAT(holding.IsAvailable(), Eq(false));
	}
	catch (...)
	{
		FAIL();
		cout << "failed test avail" << endl;
	}
}

TEST_F(HoldingTest, CanSpecifyClassificationSeparatelyWhenCreated)
{
    Holding holding("B", 2);

    ASSERT_THAT(holding.Classification(), Eq("B"));
}

TEST_F(HoldingTest, CanSpecifyCopyNumberSeparatelyWhenCreated)
{
    Holding holding("A", 7);

    ASSERT_THAT(holding.CopyNumber(), Eq(7));
}

TEST_F(HoldingTest, IsNotAvailableWhenCreatedWithSeparateClassificationAndCopy)
{
    Holding holding("A", 2);

    ASSERT_THAT(holding.IsAvailable(), Eq(false));
}

/*
* assignment copy all members
*/
TEST_F(HoldingTest, AssignmentCopiesAllMembers)
{
	ASSERT_THAT(holding, NotNull());
	// transfer to a different branch
    holding->Transfer(EAST_BRANCH);
    Holding newHolding = *holding;
    ASSERT_THAT(newHolding.Classification(), Eq(THE_TRIAL_CLASSIFICATION));
    ASSERT_THAT(newHolding.CopyNumber(), Eq(holding->CopyNumber()));
    ASSERT_THAT(IsAvailableAt(&newHolding, EAST_BRANCH), Eq(true));
}

TEST_F(HoldingTest, TransferMakesHoldingAvailableAtBranch)
{
    holding->Transfer(EAST_BRANCH);

    ASSERT_THAT(IsAvailableAt(holding, EAST_BRANCH), Eq(true));
}

TEST_F(HoldingTest, BarCodeCombinesClassificationAndCopyNumber)
{
    Holding holding(THE_TRIAL_CLASSIFICATION, 5);
    string barcode = holding.Barcode();
    ASSERT_THAT(barcode, Eq(THE_TRIAL_CLASSIFICATION + ":5"));
}

TEST_F(HoldingTest, AreEqualWhenClassificationAndCopyMatch)
{
    Holding copy(holding->Classification(), holding->CopyNumber());

    ASSERT_THAT(*holding == copy, Eq(true));
}

TEST_F(HoldingTest, AreUnequalWhenCopyDoesNotMatch)
{
    Holding extraCopy(holding->Classification(), holding->CopyNumber() + 1);

    ASSERT_THAT(*holding != extraCopy, Eq(true));
}

TEST_F(HoldingTest, AreUnequalWhenClassificationDoesNotMatch)
{
    Holding differentBook(holding->Classification() + "X", 1);

    ASSERT_THAT(*holding != differentBook, Eq(true));
}

TEST_F(HoldingTest, IsLessThanWhenClassificationsAreLessThan)
{
    Holding a("A:1");
    Holding b("B:1");

    ASSERT_THAT(a < b, Eq(true));
}

TEST_F(HoldingTest, IsNotLessThanWhenClassificationIsNotLessThan)
{
    Holding a("A:1");
    Holding b("B:1");

    ASSERT_THAT(!(b < a), Eq(true));
}

TEST_F(HoldingTest, IsNotLessThanWhenBarcodesAreEqual)
{
    Holding a("A:1");
    Holding aCopy("A:1");

    ASSERT_THAT(a < aCopy, Eq(false));
}

TEST_F(HoldingTest, ck)
{
    holding->Transfer(EAST_BRANCH);
    date ckon(2007, Mar, 1);
    holding->CheckOut(ckon);
    ASSERT_THAT(holding->IsAvailable(), Eq(false));
    ASSERT_THAT(holding->LastCheckedOutOn(), Eq(ckon));
    // verify late
    date_duration daysCheckedOut(Book::BOOK_CHECKOUT_PERIOD + 0);
    date expectedDue = ckon + daysCheckedOut;
    ASSERT_THAT(holding->DueDate(), Eq(expectedDue));
}

TEST_F(HoldingTest, Ckin)
{
    holding->Transfer(EAST_BRANCH);
    date checkoutOn(2007, Mar, 1);
    holding->CheckOut(checkoutOn);
    date checkinOn(2007, Mar, 2);
    Branch branch2("2", "branch2");
    holding->CheckIn(checkinOn, branch2);
    ASSERT_THAT(IsAvailableAt(holding, branch2), Eq(true));
}

TEST_F(HoldingTest, Due)
{
    Holding holdingA(SEVEN_CLASSIFICATION, 1);
    holdingA.Transfer(EAST_BRANCH);
    date checkoutOn(2007, Mar, 1);
    holdingA.CheckOut(checkoutOn);

    ASSERT_THAT(holdingA.DueDate(), Eq(checkoutOn + date_duration(Book::MOVIE_CHECKOUT_PERIOD)));
}

TEST_F(HoldingTest, MoviesDueCheckoutPeriodDaysAfterCheckout)
{
    Holding movie(SEVEN_CLASSIFICATION, 1);
    MakeAvailableAtABranch(&movie);
    movie.CheckOut(ARBITRARY_DATE);
    ASSERT_THAT(movie.DueDate(),
        Eq(ARBITRARY_DATE + date_duration(Book::MOVIE_CHECKOUT_PERIOD)));
}
