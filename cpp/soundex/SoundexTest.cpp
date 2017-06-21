#include <gtest/gtest.h>
#include <string>

class Soundex
{
public:
	std::string encode(const std::string & word) {
		return word;
	}

};

TEST(SoundexEncoding, RetainSoleLetterOfOneLetterWord)
{
	Soundex soundex;

	auto encoded = soundex.encode("A");

	EXPECT_EQ(encoded, "A");
}