#include <gtest/gtest.h>
#include <string>
#include <map>

/*
* The correct value can be found as follows:

* 1.Retain the first letter of the name and drop all other occurrences of a, e, i, o, u, y, h, w.
* 2.Replace consonants with digits as follows (after the first letter):
*    b, f, p, v → 1
*    c, g, j, k, q, s, x, z → 2
*    d, t → 3
*    l → 4
*    m, n → 5
*    r → 6
* 3.If two or more letters with the same number are adjacent in the original name (before step 1), only retain the first letter; also two letters with the same number separated by 'h' or 'w' are coded as a single number, whereas such letters separated by a vowel are coded twice. This rule also applies to the first letter.
* 4.If you have too few letters in your word that you can't assign three numbers, append with zeros until there are three numbers. If you have more than 3 letters, just retain the first 3 numbers.

*/
class Soundex
{
public:
	static const size_t MAX_CODE_LENGTH = 4;
	const std::string NOT_A_DIGIT{"*"};

	std::string encode(const std::string & word) {
		return zeroPad(head(word) + tail(encodeDigits(word)));
	}

	std::string head(const std::string & word) {
		return word.substr(0, 1);
	}

	std::string tail(const std::string & word) {
		return word.substr(1);
	}

	std::string encodeDigits(const std::string & word) {
		std::string encoding;

		encoding += encodeDigit(word.front());

		for (auto letter : tail(word)) {
			if (isComplete(encoding))break;

			std::string digit = encodeDigit(letter);
			if (digit != NOT_A_DIGIT && lastDigit(encoding) != encodeDigit(letter))
				encoding += encodeDigit(letter);
		}
		return encoding;
	}

	std::string lastDigit(const std::string & encoding) {
		if (encoding.empty())return NOT_A_DIGIT;
		return std::string(1, encoding.back());
	}

	bool isComplete(const std::string & encode) {
		return encode.size() == MAX_CODE_LENGTH ;
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
		
		auto it = encodings.find(tolower(letter));
		return it == encodings.end()? NOT_A_DIGIT :(it)->second;
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

TEST_F(SoundexEncoding, CombineDuplicateEncodings)
{
	EXPECT_EQ(soundex.encodeDigit('b'), soundex.encodeDigit('f'));
	EXPECT_EQ(soundex.encodeDigit('c'), soundex.encodeDigit('g'));
	EXPECT_EQ(soundex.encodeDigit('d'), soundex.encodeDigit('t'));

	EXPECT_EQ(soundex.encode("Abfcgdt"), "A123");
}

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

TEST_F(SoundexEncoding, IgnoreCaseWhenEncodingConsonants)
{
	EXPECT_EQ(soundex.encode("BCDL"), soundex.encode("Bcdl"));
}