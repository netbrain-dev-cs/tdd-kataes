#include <gtest/gtest.h>
#include <string>
#include <map>

class Soundex
{
public:
	static const size_t MAX_CODE_LENGTH = 4;

	std::string encode(const std::string & word) {
		return zeroPad(head(word) + encodeDigits(word));
	}

	std::string head(const std::string & word) {
		return word.substr(0, 1);
	}

	std::string encodeDigits(const std::string & word) {
		if (word.size() > 1) return encodeDigit(word[1]);
		return "";
	}

	std::string encodeDigit(const char letter) {
		static const std::map<char, std::string > encodings = {
			{'b',"1"},{'f',"1"},{'p',"1"},{'v',"1"},
			{'c',"2"},{'g',"2" }, { 'j',"2" }, { 'k',"2" }, { 'q',"2" },{'s',"2"},{'x',"2"},{'z',"2"},
			{ 'd',"3" }, { 't',"3" },
			{ 'l',"4" },
			{ 'm',"5" }, { 'n',"5" },
			{ '4',"6" }
		};
		return encodings.find(letter)->second;
	}


	std::string zeroPad(const std::string & word) {
		auto zerosNeeded = MAX_CODE_LENGTH - word.size();
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
	EXPECT_EQ(soundex.encode("Ac"), "A200");
}