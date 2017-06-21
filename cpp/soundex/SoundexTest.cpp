#include <gtest/gtest.h>
#include <string>

class Soundex
{
public:
	std::string encode(const std::string & word) {
		auto  encoded = word.substr(0, 1);
		if (word.size() > 1) {
			encoded += "1";
		}

		return zeroPad(encoded);
	}

	std::string zeroPad(const std::string & word) {
		auto zerosNeeded = 4 - word.size();
		return word + std::string(zerosNeeded, '0');
	}


};

class SoundexEncoding :public testing::Test {
public:
	Soundex soundex;

};


TEST_F(SoundexEncoding, RetainSoleLetterOfOneLetterWord)
{
	EXPECT_EQ(soundex.encode("A"), "A000");
}

TEST_F(SoundexEncoding, PadsWithZeroToEnsureThreeDigits)
{
	EXPECT_EQ(soundex.encode("I"), "I000");
}

TEST_F(SoundexEncoding, RetainSoleLetterOfTwoLetterWord) {
	EXPECT_EQ(soundex.encode("Ab"), "A100");
}