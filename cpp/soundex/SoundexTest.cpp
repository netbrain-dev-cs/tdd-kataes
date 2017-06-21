#include <gtest/gtest.h>
#include <string>

class Soundex
{
public:
	std::string encode(const std::string & word) {
		return word + "000";
	}

};

class SoundexEncoding :public testing::Test {
public:
	Soundex soundex;

};


TEST_F(SoundexEncoding, RetainSoleLetterOfOneLetterWord)
{
	auto encoded = soundex.encode("A");

	EXPECT_EQ(encoded, "A000");
}