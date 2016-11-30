#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "BranchAccess.h"
#include "Branch.h"

#include <cstdio>

#include "Persistence.h"

using namespace std;
using namespace testing;

class BranchAccessTest : public Test
{
public:
    BranchAccess access;
    BranchAccess access2;
    BranchAccess* branchAccess;

    std::shared_ptr<Persistence<Branch>> persister;

    vector<Branch> noBranches;
    Branch* eastBranch;

    virtual void SetUp()
    {
        branchAccess = new BranchAccess();
        branchAccess->DeleteAll();

        eastBranch = new Branch("1", "east");

        access.DeleteAll();
    }

    virtual void TearDown()
    {
        branchAccess->DeleteAll();
        delete branchAccess;
        delete eastBranch;

        access.DeleteAll();
    }
};

TEST_F(BranchAccessTest, SizeInitiallyZero)
{
    ASSERT_THAT(branchAccess->Size(), Eq(0));
}

TEST_F(BranchAccessTest, SaveIncrementsSize)
{
    branchAccess->Save(*eastBranch);

    ASSERT_THAT(branchAccess->Size(), Eq(1));
}

TEST_F(BranchAccessTest, PersistsBranch)
{
    Branch branch("55", "WEST");
    branch.SetAddress("address");
    access.Save(branch);
    Branch retrieve("55");

    access2.Find(retrieve);

    ASSERT_THAT(retrieve.Address(), Eq("address"));
}

TEST_F(BranchAccessTest, FindAnswersFalseForNonexistentBranch)
{
    Branch east("66");

    ASSERT_THAT(access.Find(east), Eq(false));
}

TEST_F(BranchAccessTest, MultipleItemsPersistedCorrectly)
{
    access.Save(Branch("66", "EAST"));
    access.Save(Branch("77", "NORTH"));
    Branch east("66");
    Branch north("77");

    access2.Find(east);
    access2.Find(north);

    ASSERT_THAT(east.Name(), Eq("EAST"));
    ASSERT_THAT(north.Name(), Eq("NORTH"));
}
