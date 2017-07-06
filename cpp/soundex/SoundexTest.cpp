#include <gtest/gtest.h>
#include <string>

class Soundex
{
public:
	const int MAX_CODING_LENTH = 4;
	const std::string NOT_A_DIGIT = "*";

	std::string encode(const std::string & word)
	{
		std::string encoding = encodeHead(word) + encodeTail(word);
		upperFirst(encoding);
		return padZero(encoding);
	}

	std::string encodeHead(const std::string & word)
	{
		return word.substr(0, 1);
	}

	void upperFirst(std::string & word) {
		word[0] = toupper(word[0]);
	}

	std::string encodeTail(const std::string & word)
	{
		std::string encoding;
		encoding += encodeLetter(word[0]);
		for (auto i = 1u;i < word.size();i++)
		{
			if (isEncodingComplete(encoding))break;

			if (encodeLetter(word[i]) != NOT_A_DIGIT &&
				encodeLetter(word[i]) != lastEncoding(encoding))
			{
				encoding += encodeLetter(word[i]);
			}			
		}

		return encoding.substr(1);
	}

	std::string lastEncoding(const std::string & encoding) {
		return std::string(1, encoding.back());
	}

	bool isEncodingComplete(const std::string encoding)
	{
		return encoding.size() == MAX_CODING_LENTH;
	}

	std::string encodeLetter(char letter) {
		static const std::map<char, std::string > encodeMap = {
			{ 'b',"1" },{ 'f',"1" },{ 'p',"1" },{ 'v',"1" },
			{ 'c',"2" },{ 'g',"2" },{ 'j',"2" },{ 'k',"2" },{ 'q',"2" },{ 's',"2" },{ 'x',"2" },{ 'z',"2" },
			{ 'd',"3" },{ 't',"3" },
			{ 'l',"4" },
			{ 'm',"5" },{ 'n',"5" },
			{ '4',"6" }
		};

		auto it = encodeMap.find(letter);
		return it == encodeMap.end() ? NOT_A_DIGIT : it->second;
	}

	std::string padZero(const std::string & word)
	{
		size_t zeroNeeded = MAX_CODING_LENTH - word.size();
		return word + std::string(zeroNeeded ,'0');
	}
};

class SoundexTest :public testing::Test
{
public:
	Soundex soundex;
};


TEST_F(SoundexTest, WordHasOneWord)
{
	EXPECT_EQ(soundex.encode("A"), "A000");
}

TEST_F(SoundexTest, ShoudPadZeroAfterFirstLetter)
{
	EXPECT_EQ(soundex.encode("B"), "B000");
}

TEST_F(SoundexTest, ShoudEncodeToDigitAfterFirstLetter)
{
	EXPECT_EQ(soundex.encode("Ab"), "A100");
	EXPECT_EQ(soundex.encode("Ac"), "A200");
}

TEST_F(SoundexTest, EncodeMoreLettersAfterFirstLetter)
{
	EXPECT_EQ(soundex.encode("Abcd"), "A123");
}

TEST_F(SoundexTest, EncodeShouldLimitToForeLetters)
{
	EXPECT_EQ(soundex.encode("Abcdefg"), "A123");
}

TEST_F(SoundexTest, ShouldUpperTheFirstLetter)
{
	EXPECT_EQ(soundex.encode("a"), "A000");
	EXPECT_EQ(soundex.encode("b"), "B000");
}

TEST_F(SoundexTest, TestNoEncodingLetters)
{
	EXPECT_EQ(soundex.encode("Aeiou"), "A000");
}

TEST_F(SoundexTest, ShouldIgnoreSameDigitNextToIt)
{
	EXPECT_EQ(soundex.encode("Abbccdd"), "A123");
}