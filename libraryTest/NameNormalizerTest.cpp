#include "gmock\gmock.h"

#include "NameNormalizer.h"

using namespace testing;
using namespace std;

TEST(ANameNormalizer, ReturnsAnEmptyStringWhenGivenSame)
{
    ASSERT_THAT(NormalizedName{""}.AsString(), Eq(""));
}

TEST(ANameNormalizer, SwapsFirstAndLastNames)
{
    ASSERT_THAT(NormalizedName{"Joseph Heller"}.AsString(), Eq("Heller, Joseph"));
    ASSERT_THAT(NormalizedName{"Haruki Murakami"}.AsString(), Eq("Murakami, Haruki"));
}

TEST(ANameNormalizer, SimplyReturnsASingleWordName)
{
    ASSERT_THAT(NormalizedName{"Plato"}.AsString(), Eq("Plato"));
}

TEST(ANameNormalizer, TrimsWhitespace)
{
    ASSERT_THAT(NormalizedName{"  Big Boi   "}.AsString(), Eq("Boi, Big"));
}

TEST(ANameNormalizer, ReplacesMiddleNameWithInitial)
{
    ASSERT_THAT(NormalizedName{"Henry David Thoreau"}.AsString(), Eq("Thoreau, Henry D."));
}

TEST(ANameNormalizer, DoesNotInitializeOneLetterMiddleName)
{
    ASSERT_THAT(NormalizedName{"Harry S Truman"}.AsString(), Eq("Truman, Harry S"));
}

TEST(ANameNormalizer, InitializesEachOfMultipleMiddleNames)
{
    ASSERT_THAT(NormalizedName{"Julia Scarlett Elizabeth Louis-Dreyfus"}.AsString(), Eq("Louis-Dreyfus, Julia S. E."));
}

TEST(ANameNormalizer, AppendsSuffixesToEnd)
{
    ASSERT_THAT(NormalizedName{"Martin Luther King, Jr."}.AsString(), Eq("King, Martin L., Jr."));
}

TEST(ANameNormalizer, ThrowsWhenNameContainsTwoCommas)
{
    ASSERT_THROW(NormalizedName{"Thurston, Howell, III"}, InvalidNameException);
}
