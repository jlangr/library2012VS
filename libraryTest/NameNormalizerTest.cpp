#include "gmock\gmock.h"

#include "NameNormalizer.h"

using namespace testing;
using namespace std;

// You should probably start with StringUtil::split. 
// Unfortunately it only supports a single delimiter currently.

TEST(ANameNormalizer, ReturnsAnEmptyStringWhenGivenSame)
{
    ASSERT_THAT(NameNormalizer::Normalize(""), Eq(""));
}

TEST(ANameNormalizer, SwapsFirstAndLastNames)
{
    ASSERT_THAT(NameNormalizer::Normalize("Joseph Heller"), Eq("Heller, Joseph"));
    ASSERT_THAT(NameNormalizer::Normalize("Haruki Murakami"), Eq("Murakami, Haruki"));
}

TEST(ANameNormalizer, SimplyReturnsASingleWordName)
{
    ASSERT_THAT(NameNormalizer::Normalize("Plato"), Eq("Plato"));
}

TEST(ANameNormalizer, TrimsWhitespace)
{
    ASSERT_THAT(NameNormalizer::Normalize("  Big Boi   "), Eq("Boi, Big"));
}

/*
TEST(ANameNormalizer, InitializesMiddleName)
{
    ASSERT_THAT(NameNormalizer::Normalize("Henry David Thoreau"), Eq("Thoreau, Henry D."));
}

TEST(ANameNormalizer, DoesNotInitializeOneLetterMiddleName)
{
    ASSERT_THAT(NameNormalizer::Normalize("Harry S Truman"), Eq("Truman, Harry S"));
}

TEST(ANameNormalizer, InitializesEachOfMultipleMiddleNames)
{
    ASSERT_THAT(NameNormalizer::Normalize("Julia Scarlett Elizabeth Louis-Dreyfus"), Eq("Louis-Dreyfus, Julia S. E."));
}

TEST(ANameNormalizer, AppendsSuffixesToEnd)
{
    ASSERT_THAT(NameNormalizer::Normalize("Martin Luther King, Jr."), Eq("King, Martin L., Jr."));
}

TEST(ANameNormalizer, ThrowsWhenNameContainsTwoCommas)
{
    // TODO
    NameNormalizer::Normalize("Thurston, Howell, III");
}
*/
