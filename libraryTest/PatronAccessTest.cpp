#include "gmock/gmock.h"

#include "PatronAccess.h"
#include "Patron.h"
#include "PatronNotFoundException.h"

#include <vector>

using std::vector;
using namespace testing;

class PatronAccessTest : public Test
{
public:
    PatronAccess access;

    virtual void SetUp()
    {
        PatronAccess::DeleteAll();
    }

    virtual void TearDown()
    {
        PatronAccess::DeleteAll();
    }
};

TEST_F(PatronAccessTest, SizeIsZeroWithNoPatrons)
{
    ASSERT_THAT(access.Size(), Eq(0));
}

TEST_F(PatronAccessTest, IncrementsSizeOnAdd)
{
    Patron patron1("patron1");
    access.Save(patron1);

    ASSERT_THAT(access.Size(), Eq(1));
}

TEST_F(PatronAccessTest, FindAnswersFalseForNonexistentPatron)
{
    Patron patron("nobody");
    ASSERT_THAT(access.Find(patron), Eq(false));
}

TEST_F(PatronAccessTest, FindAnswerTrueForSavedPatron)
{
    Patron patron1("patron1");
    access.Save(patron1);

    Patron retrieved("patron1");
    ASSERT_THAT(access.Find(retrieved), Eq(true));
}

TEST_F(PatronAccessTest, SaveIsPersistentAcrossAccessInstances)
{
    Patron patron1("patron1");
    access.Save(patron1);

    PatronAccess newAccess;
    Patron retrieved("patron1");
    ASSERT_THAT(newAccess.Find(retrieved), Eq(true));
}

TEST_F(PatronAccessTest, SavePersistsAllAttributes)
{
    std::shared_ptr<Patron> patron(new Patron("patron1"));
    access.Save(*patron);

    PatronAccess newAccess;
    Patron& retrieved = newAccess.FindByName("patron1");

    ASSERT_THAT(retrieved.Name(), Eq(patron->Name()));
    ASSERT_THAT(retrieved.FineBalance(), Eq(patron->FineBalance()));
}

TEST_F(PatronAccessTest, FindByNameThrowsWhenNoNameMatches)
{
    EXPECT_THROW(access.FindByName("nobody"), PatronNotFoundException);
}

TEST_F(PatronAccessTest, FindByNameReturnsChronologicallyFirstMatch)
{
    Patron match1("Langr", 1);
    access.Save(match1);
    Patron mismatch("Long", 2);
    access.Save(mismatch);
    Patron match2("Langr", 3);
    access.Save(match2);

    Patron found = access.FindByName("Langr");

    ASSERT_THAT(found.Id(), Eq(1));
}

TEST_F(PatronAccessTest, UpdatePersistsChanges)
{
    int id = 10;
    Patron patron1("x", id);
    access.Save(patron1);
    int fine = 100;
    patron1.AddFine(fine);

    access.Update(patron1);

    Patron retrieved("", id);
    access.Find(retrieved);
    ASSERT_THAT(retrieved.FineBalance(), Eq(fine));
}

TEST_F(PatronAccessTest, GetAllAnswersAllSavedPatrons)
{
    Patron patron1("a", 10);
    Patron patron2("b", 20);
    access.Save(patron1);
    access.Save(patron2);

    vector<Patron> expected{ patron1, patron2 };

    ASSERT_THAT(access.GetAll(), ContainerEq(expected));
}
