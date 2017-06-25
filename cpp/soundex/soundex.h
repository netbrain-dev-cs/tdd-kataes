#pragma once
#include <string>

/*
* The correct value can be found as follows:

* 1.Retain the first letter of the name and drop all other occurrences of a, e, i, o, u, y, h, w.
* 2.Replace consonants with digits as follows (after the first letter):
*    b, f, p, v ¡ú 1
*    c, g, j, k, q, s, x, z ¡ú 2
*    d, t ¡ú 3
*    l ¡ú 4
*    m, n ¡ú 5
*    r ¡ú 6
* 3.If two or more letters with the same number are adjacent in the original name (before step 1), only retain the first letter; also two letters with the same number separated by 'h' or 'w' are coded as a single number, whereas such letters separated by a vowel are coded twice. This rule also applies to the first letter.
* 4.If you have too few letters in your word that you can't assign three numbers, append with zeros until there are three numbers. If you have more than 3 letters, just retain the first 3 numbers.

*/
class Soundex
{
public:
	static const size_t MAX_CODE_LENGTH = 4;
	const std::string NOT_A_DIGIT{ "*" };

	std::string encode(const std::string & word) {
		std::string encoding = head(word) + tail(encodeDigits(word));
		encoding = upperFront(encoding);
		encoding = zeroPad(encoding);
		return encoding;
	}

	std::string upperFront(const std::string & word) {
		std::string upperWord = word;
		if (!upperWord.empty()) {
			upperWord[0] = toupper(upperWord[0]);
		}		
		return upperWord;
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
		return encode.size() == MAX_CODE_LENGTH;
	}

	std::string encodeDigit(const char letter) {
		static const std::map<char, std::string > encodings = {
			{ 'b',"1" },{ 'f',"1" },{ 'p',"1" },{ 'v',"1" },
			{ 'c',"2" },{ 'g',"2" },{ 'j',"2" },{ 'k',"2" },{ 'q',"2" },{ 's',"2" },{ 'x',"2" },{ 'z',"2" },
			{ 'd',"3" },{ 't',"3" },
			{ 'l',"4" },
			{ 'm',"5" },{ 'n',"5" },
			{ '4',"6" }
		};

		auto it = encodings.find(tolower(letter));
		return it == encodings.end() ? NOT_A_DIGIT : (it)->second;
	}


	std::string zeroPad(const std::string & word) {
		auto zerosNeeded = MAX_CODE_LENGTH - word.size();
		return word + std::string(zerosNeeded, '0');
	}
};