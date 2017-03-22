#include "gmock/gmock.h"

#include <string>

using namespace testing;
using namespace std;

constexpr char digitToRomanNumeral(int digit)
{
	return (digit == 1) ? 'I'
		: (digit == 10) ? 'X'
		: throw "?";
}

void convert(int digit, int& number, std::string& result)
{
	while (number >= digit) {
		result += digitToRomanNumeral(digit);
		number -= digit;
	}

}

std::string convert(int number) {
	std::string result;
	convert(10, number, result);
	if (!result.empty())
		return result;
	while (number >= 1) {
		result += digitToRomanNumeral(1);
		number -= 1;
	}
	return result;
}

TEST(ARomanConverter, ConvertsSomeNumbers)
{
	ASSERT_THAT(convert(1), Eq("I"));
	ASSERT_THAT(convert(2), Eq("II"));
	ASSERT_THAT(convert(3), Eq("III"));
	ASSERT_THAT(convert(10), Eq("X"));
	ASSERT_THAT(convert(20), Eq("XX"));
#if false
	
	ASSERT_THAT(convert(2), Eq("II"));
#endif
}
