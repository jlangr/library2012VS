#include "gmock/gmock.h"

#include <string>

using namespace testing;
using namespace std;

vector<pair<int, string>> conversions{ 
	{ 1000, "M" },
	{ 900, "CM" },
	{ 500, "D" },
	{ 400, "CD" },
	{ 100, "C" },
	{ 90, "XC" },
	{ 50, "L" },
	{ 40, "XL" },
	{ 10, "X" }, {9, "IX"},  { 5, "V" },{4, "IV"}, { 1, "I" }
};

void decrementAndAppendCorrespondingRomanDigits(int& number, std::string& result,
	std::pair<int, string> arabicToRoman)
{
	auto digit = arabicToRoman.first;
	auto romanDigit = arabicToRoman.second;
	while (number >= digit) 
	{
		result += romanDigit;
		number -= digit;
	}
}

std::string decrementAndAppendCorrespondingRomanDigits(int number) {

	std::string result;
	for (auto arabicToRomanPair : conversions)
		decrementAndAppendCorrespondingRomanDigits(number, result, arabicToRomanPair);
	return result;
}

TEST(ARomanConverter, ConvertsSomeNumbers)
{
	ASSERT_THAT(decrementAndAppendCorrespondingRomanDigits(1), Eq("I"));
	ASSERT_THAT(decrementAndAppendCorrespondingRomanDigits(2), Eq("II"));
	ASSERT_THAT(decrementAndAppendCorrespondingRomanDigits(3), Eq("III"));
	ASSERT_THAT(decrementAndAppendCorrespondingRomanDigits(4), Eq("IV"));
	ASSERT_THAT(decrementAndAppendCorrespondingRomanDigits(5), Eq("V"));
	ASSERT_THAT(decrementAndAppendCorrespondingRomanDigits(9), Eq("IX"));
	ASSERT_THAT(decrementAndAppendCorrespondingRomanDigits(10), Eq("X"));
	ASSERT_THAT(decrementAndAppendCorrespondingRomanDigits(11), Eq("XI"));
	ASSERT_THAT(decrementAndAppendCorrespondingRomanDigits(20), Eq("XX"));
	ASSERT_THAT(decrementAndAppendCorrespondingRomanDigits(40), Eq("XL"));
	ASSERT_THAT(decrementAndAppendCorrespondingRomanDigits(50), Eq("L"));
	ASSERT_THAT(decrementAndAppendCorrespondingRomanDigits(90), Eq("XC"));
	ASSERT_THAT(decrementAndAppendCorrespondingRomanDigits(100), Eq("C"));
	ASSERT_THAT(decrementAndAppendCorrespondingRomanDigits(400), Eq("CD"));
	ASSERT_THAT(decrementAndAppendCorrespondingRomanDigits(500), Eq("D"));
	ASSERT_THAT(decrementAndAppendCorrespondingRomanDigits(900), Eq("CM"));
	ASSERT_THAT(decrementAndAppendCorrespondingRomanDigits(1000), Eq("M"));
	ASSERT_THAT(decrementAndAppendCorrespondingRomanDigits(2038), Eq("MMXXXVIII"));
}
