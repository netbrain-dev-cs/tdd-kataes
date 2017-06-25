#include <gtest/gtest.h>
#include <string>
#include <map>
#include "soundex.h"

class SoundexEncoding :public testing::Test {
public:
	Soundex soundex;

};

//Rule4.单个字符保留首字母,后面补零
TEST_F(SoundexEncoding, RetainSoleLetterOfOneLetterWord)
{
	EXPECT_EQ(soundex.encode("A"), "A000");
}
TEST_F(SoundexEncoding, PadsWithZeroToEnsureThreeDigits)
{
	EXPECT_EQ(soundex.encode("I"), "I000");
}

//Rule1.忽略除第一个字母后面所有的a, e, i, o, u, y, h, w
TEST_F(SoundexEncoding, NotEncodingAllIgnoreLetter)
{
	EXPECT_EQ(soundex.encode("Ae"), "A000");
	EXPECT_EQ(soundex.encode("Ai"), "A000");
	EXPECT_EQ(soundex.encode("Ao"), "A000");
	EXPECT_EQ(soundex.encode("Aaeiouyhw"), "A000");
}

//Rule4,不足四个字符后面补零
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

//忽略相邻的重复编码
TEST_F(SoundexEncoding, CombineDuplicateEncodings)
{
	EXPECT_EQ(soundex.encodeDigit('b'), soundex.encodeDigit('f'));
	EXPECT_EQ(soundex.encodeDigit('c'), soundex.encodeDigit('g'));
	EXPECT_EQ(soundex.encodeDigit('d'), soundex.encodeDigit('t'));

	EXPECT_EQ(soundex.encode("Abfcgdt"), "A123");
}