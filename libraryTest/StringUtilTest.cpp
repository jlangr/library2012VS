#include "gmock/gmock.h"

#include "StringUtil.h"

#include <vector>

using namespace testing;
using namespace std;

TEST(StringUtilTest, SplitsStringIntoTwo)
{
    ASSERT_THAT(StringUtil::split("abc-def", '-'), Eq(vector<string>{ "abc", "def" }));
}

TEST(StringUtilTest, SupportsAlternateDelimiters)
{
    ASSERT_THAT(StringUtil::split("abc def", ' '), Eq(vector<string>{ "abc", "def" }));
}

TEST(StringUtilTest, SplitsIntoSeveralTokens)
{
    ASSERT_THAT(StringUtil::split("abc def ghi", ' '), Eq(vector<string>{ "abc", "def", "ghi" }));
}

TEST(StringUtilTest, HandlesDelimiterAtEnd)
{
    ASSERT_THAT(StringUtil::split("abc:def:", ':'), Eq(vector<string>{ "abc", "def", "" }));
}

TEST(StringUtilTest, NoDelimiterReturnsUnchangedString)
{
    ASSERT_THAT(StringUtil::split("abcdef", ':'), Eq(vector<string>{ "abcdef" }));
}

TEST(StringUtilTest, EmptyStringReturnsEmptyString)
{
    ASSERT_THAT(StringUtil::split("", ':'), Eq(vector<string>{ "" }));
}