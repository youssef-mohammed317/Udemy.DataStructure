#include "MyString.h"
#include<iostream>
#include<cctype>
int MyString::GetLength(const char* string)
{
	int count = 0;
	for (int i = 0; string[i] != '\0'; i++)
		count++;
	return count;
}
void MyString::ChangeCase(char* string)
{
	for (int i = 0; string[i] != '\0'; i++)
	{
		if (IsLower(string[i]))
		{
			string[i] -= 32;
		}
		else if (IsUpper(string[i]))
		{
			string[i] += 32;
		}
	}
}

int MyString::CountWords(const char* string)
{
	int count = 0;
	for (int i = 0; string[i] != '\0'; i++)
	{
		if (string[i] != ' ' && (i == 0 || string[i - 1] == ' '))
		{
			count++;
		}
	}

	return count;
}

int MyString::CountVowels(const char* string)
{
	int count = 0;
	for (int i = 0; string[i] != '\0'; i++)
	{
		if (IsVowel(string[i]))
			count++;
	}
	return count;
}
int MyString::CountConsonents(const char* string)
{
	int count = 0;
	for (int i = 0; string[i] != '\0'; i++)
	{
		if (IsLetter(string[i]))
			if (!IsVowel(string[i]))
				count++;
	}
	return count;
}
bool MyString::IsVowel(char c) {
	switch (c)
	{
	case 'a':
	case 'e':
	case 'o':
	case 'i':
	case 'u':
	case 'A':
	case 'E':
	case 'O':
	case 'I':
	case 'U':
		return true;
	default:
		return false;

	}
}

bool MyString::IsValidString(const char* string)
{
	for (int i = 0; string[i] != '\0'; i++)
	{
		if (!IsAlpha(string[i]))
			return false;
	}
	return true;
}
bool MyString::IsAlpha(char c)
{
	return(IsNumber(c) || IsLetter(c));
}
bool MyString::IsNumber(char c)
{
	return (c >= '0' && c <= '9');
}
bool MyString::IsLetter(char c)
{
	return ((c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z'));
}
bool MyString::IsLower(char c)
{
	return (c >= 'a' && c <= 'z');
}
bool MyString::IsUpper(char c)
{
	return (c >= 'A' && c <= 'Z');
}

void MyString::Reverse(char* string)
{
	int j = GetLength(string) - 1;
	for (int i = 0; j > i; i++, j--)
	{
		char temp = string[i];
		string[i] = string[j];
		string[j] = temp;
	}
}
bool MyString::Compare(const char* string1, const char* string2, bool ignoreCase)
{
	int i = 0, j = 0;

	while (string1[i] != '\0' && string2[j] != '\0')
	{
		if (!ignoreCase)
		{
			if (string1[i] != string2[j])
				return false;
		}
		else
		{
			if (std::tolower(string1[i]) != std::tolower(string2[j]))
				return false;
		}
		i++;
		j++;
	}
	return (string1[i] == '\0' && string2[j] == '\0');
}
bool MyString::IsPalindrome(const char* string)
{
	for (int i = 0, j = GetLength(string) - 1; j > i; i++, j--)
	{
		if (string[i] != string[j])
			return false;
	}
	return true;
}

std::string MyString::GetDuplicates(const char* string, bool ignoreCase)
{
	std::string result = "";
	unsigned long long H = 0, x = 0; // int 4 bytes 32 bits (26 char)
	for (int i = 0; string[i] != '\0'; i++)
	{
		if (!IsLetter(string[i]))
			continue;
		x = 1;
		if (ignoreCase)
		{
			x <<= std::tolower(string[i]) - 'a';
		}
		else {
			if (IsLower(string[i]))
				x <<= string[i] - 'a';
			else
				x <<= (string[i] - 'A') + 26;
		}
		if ((x & H) > 0)
		{
			result += string[i];
		}
		H |= x;
	}

	return result;
}
bool MyString::IsAnagram(const char* string1, const char* string2)
{
	int HashTable[26] = { 0 };
	int i = 0, j = 0;
	while (string1[i] != '\0' && string2[j] != '\0')
	{
		HashTable[std::tolower(string1[i]) - 'a']++;
		HashTable[std::tolower(string2[j]) - 'a']--;
		j++;
		i++;
	}
	if (string1[i] == '\0' && string2[j] == '\0')
	{
		for (int k = 0; k < 26; k++)
		{
			if (HashTable[k] != 0)
			{
				return false;
			}
		}
		return true;
	}
	return false;
}

void MyString::Permutations(char* str, char* res, int* flags, int k, int l)
{
	if (str == nullptr || flags == nullptr || k < 0 || k > l)return;

	if (str[k] == '\0')
	{
		res[k] = '\0';
		cout << res << " ";
	}
	else {

		for (int i = 0; str[i] != '\0'; i++)
		{
			if (flags[i] == 0)
			{
				res[k] = str[i];
				flags[i] = 1;
				Permutations(str, res, flags, k + 1, l);
				flags[i] = 0;
			}
		}
	}

}

void MyString::PrintPermutationsTreeMethod(char* str)
{

	int l = GetLength(str) + 1;

	int* flags = new int[l] {0};
	char* res = new char[l];

	Permutations(str, res, flags, 0, l);

	delete[]flags;
	delete[]res;
}


void MyString::Swap(char& x, char& y)
{
	char t = x;
	x = y;
	y = t;
}

void MyString::Perm(char* str, int l, int h)
{
	if (str == nullptr)return;
	if (l == h)
	{
		cout << str << " ";
	}
	else {
		for (int i = l; i <= h; i++)
		{
			Swap(str[i], str[l]);
			Perm(str, l + 1, h);
			Swap(str[i], str[l]);
		}
	}
}
void MyString::PrintPermutationsSwapMethod(char* str)
{
	if (str == nullptr)return;

	int h = GetLength(str) - 1;
	Perm(str, 0, h);
}

void MyString::TestBehavior()
{
	std::cout << "=========== TEST START ===========\n\n";

	char str1[] = "Hello World";
	char str2[] = "ah1M0eD";
	char str3[] = "AEIOU";
	char str4[] = "bcdfg";
	char str5[] = "Hello123";
	char str6[] = "Hello@123";
	char str7[] = "DATASrucDTure";
	char str8[] = "aBcD";
	char str9[] = "madam";
	char str10[] = "hello";
	char str11[] = "Silent";
	char str12[] = "Listen";
	char str13[] = "Triangle";
	char str14[] = "Integral";
	char str15[] = "DataStructure";
	char str16[] = "Programming";

	// GetLength
	std::cout << "GetLength\n";
	std::cout << "\"" << str1 << "\" -> " << GetLength(str1) << "\n";
	std::cout << "\"" << str2 << "\" -> " << GetLength(str2) << "\n\n";

	// ChangeCase
	std::cout << "ChangeCase\n";
	std::cout << "Before: " << str8 << "\n";
	ChangeCase(str8);
	std::cout << "After : " << str8 << "\n\n";

	// CountWords
	std::cout << "CountWords\n";
	std::cout << "\"" << str1 << "\" -> " << CountWords(str1) << "\n";
	std::cout << "\"One Two Three\" -> " << CountWords("One Two Three") << "\n\n";

	// CountVowels
	std::cout << "CountVowels\n";
	std::cout << "\"" << str1 << "\" -> " << CountVowels(str1) << "\n";
	std::cout << "\"" << str3 << "\" -> " << CountVowels(str3) << "\n\n";

	// CountConsonents
	std::cout << "CountConsonents\n";
	std::cout << "\"" << str1 << "\" -> " << CountConsonents(str1) << "\n";
	std::cout << "\"" << str4 << "\" -> " << CountConsonents(str4) << "\n\n";

	// Reverse
	std::cout << "Reverse\n";
	std::cout << "Before: " << str7 << "\n";
	Reverse(str7);
	std::cout << "After : " << str7 << "\n\n";

	// Character Tests
	std::cout << "Character Tests\n";
	char testChars[] = { 'a', 'Z', '5', '@' };

	for (int i = 0; i < 4; i++)
	{
		char c = testChars[i];
		std::cout << "\nTesting: " << c << "\n";
		std::cout << "IsLetter: " << IsLetter(c) << "\n";
		std::cout << "IsNumber: " << IsNumber(c) << "\n";
		std::cout << "IsAlpha : " << IsAlpha(c) << "\n";
		std::cout << "IsLower : " << IsLower(c) << "\n";
		std::cout << "IsUpper : " << IsUpper(c) << "\n";
		std::cout << "IsVowel : " << IsVowel(c) << "\n";
	}

	// IsValidString
	std::cout << "\nIsValidString\n";
	std::cout << "\"" << str5 << "\" -> " << IsValidString(str5) << "\n";
	std::cout << "\"" << str6 << "\" -> " << IsValidString(str6) << "\n";
	std::cout << "\"HelloWorld\" -> " << IsValidString("HelloWorld") << "\n\n";

	// Compare
	std::cout << "Compare\n";
	std::cout << "\"Hello\" vs \"Hello\" (false) -> "
		<< Compare("Hello", "Hello", false) << "\n";
	std::cout << "\"Hello\" vs \"hello\" (false) -> "
		<< Compare("Hello", "hello", false) << "\n";
	std::cout << "\"Hello\" vs \"hello\" (true)  -> "
		<< Compare("Hello", "hello", true) << "\n\n";

	// IsPalindrome
	std::cout << "IsPalindrome\n";
	std::cout << "\"" << str9 << "\" -> " << IsPalindrome(str9) << "\n";
	std::cout << "\"" << str10 << "\" -> " << IsPalindrome(str10) << "\n\n";

	// GetDuplicates
	std::cout << "GetDuplicates\n";
	std::cout << "\"" << str5 << "\" -> " << GetDuplicates(str5) << "\n";
	std::cout << "\"" << str15 << "\" ignoreCase=true  -> "
		<< GetDuplicates(str15, true) << "\n";
	std::cout << "\"" << str15 << "\" ignoreCase=false -> "
		<< GetDuplicates(str15, false) << "\n";
	std::cout << "\"" << str16 << "\" ignoreCase=true  -> "
		<< GetDuplicates(str16, true) << "\n\n";

	// IsAnagram
	std::cout << "IsAnagram\n";
	std::cout << "\"" << str11 << "\" and \"" << str12 << "\" -> "
		<< IsAnagram(str11, str12) << "\n";
	std::cout << "\"" << str13 << "\" and \"" << str14 << "\" -> "
		<< IsAnagram(str13, str14) << "\n";
	std::cout << "\"Hello\" and \"World\" -> "
		<< IsAnagram("Hello", "World") << "\n\n";

	// PrintPermutationsTreeMethod
	std::cout << "PrintPermutationsTreeMethod\n";
	char permStr1[] = "ABC";
	std::cout << "\"" << permStr1 << "\" -> ";
	PrintPermutationsTreeMethod(permStr1);
	std::cout << "\n\n";

	// PrintPermutationsSwapMethod
	std::cout << "PrintPermutationsSwapMethod\n";
	char permStr2[] = "ABC";
	std::cout << "\"" << permStr2 << "\" -> ";
	PrintPermutationsSwapMethod(permStr2);
	std::cout << "\n\n";

	std::cout << "=========== TEST END ===========\n";
}