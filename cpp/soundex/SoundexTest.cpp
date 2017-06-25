#include <gtest/gtest.h>
#include <string>
#include <map>

class Soundex
{
public:
	static const size_t MAX_CODE_LENGTH = 4;

	std::string encode(const std::string & word) {
		return zeroPad(head(word) + encodeDigits(tail(word)));
	}

	std::string head(const std::string & word) {
		return word.substr(0, 1);
	}

	std::string tail(const std::string & word) {
		return word.substr(1);
	}

	std::string encodeDigits(const std::string & word) {
		std::string result;
		for (auto ch : word) {
			result += (encodeDigit(ch));
			if (IsComplete(result))break;
		}
		return result;
	}

	bool IsComplete(const std::string & encode) {
		return encode.size() == MAX_CODE_LENGTH - 1;
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
		auto it = encodings.find(letter);
		return it == encodings.end()?"":(it)->second;
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

TEST_F(SoundexEncoding, RetainSoleLetterOfTwoLetterWord)
{
	EXPECT_EQ(soundex.encode("Ab"), "A100");
	EXPECT_EQ(soundex.encode("Ac"), "A200");
}

TEST_F(SoundexEncoding,IgnoreNoneAlphabetics)
{
	ASSERT_EQ(soundex.encode("A#"), "A000");
}

TEST_F(SoundexEncoding, RetainSoleLetterOfMoreLetterWord)
{
	EXPECT_EQ(soundex.encode("Abc"), "A120");
	EXPECT_EQ(soundex.encode("Abcd"), "A123");
}

TEST_F(SoundexEncoding, LimitResultOfForeLetterWord)
{
	EXPECT_EQ(soundex.encode("Abcdfg"), "A123");
}