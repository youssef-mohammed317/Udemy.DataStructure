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
void MyString::TestBehavior()
{
	std::cout << "=========== TEST START ===========\n\n";

	char str1[] = "Hello World";
	char str2[] = "ah1M0eD";
	char str3[] = "AEIOU";
	char str4[] = "bcdfg";
	char str5[] = "Hello123";
	char str6[] = "Hello@123";
	char str7[] = "DataStructure";
	char str8[] = "aBcD";

	// GetLength
	std::cout << "GetLength\n";
	std::cout << "Hello World -> " << GetLength(str1) << "\n";
	std::cout << "ah1M0eD -> " << GetLength(str2) << "\n\n";

	// ChangeCase
	std::cout << "ChangeCase\n";
	std::cout << "Before: " << str8 << "\n";
	ChangeCase(str8);
	std::cout << "After : " << str8 << "\n\n";

	// CountWords
	std::cout << "CountWords\n";
	std::cout << "Hello World -> " << CountWords(str1) << "\n\n";

	// CountVowels
	std::cout << "CountVowels\n";
	std::cout << "Hello World -> " << CountVowels(str1) << "\n";
	std::cout << "AEIOU -> " << CountVowels(str3) << "\n\n";

	// CountConsonents
	std::cout << "CountConsonents\n";
	std::cout << "Hello World -> " << CountConsonents(str1) << "\n";
	std::cout << "bcdfg -> " << CountConsonents(str4) << "\n\n";

	// Reverse
	std::cout << "Reverse\n";
	std::cout << "Before: " << str7 << "\n";
	Reverse(str7);
	std::cout << "After : " << str7 << "\n\n";

	// Character checks
	std::cout << "Character Tests\n";
	char testChars[] = { 'a','Z','5','@' };

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
	std::cout << "Hello123 -> " << IsValidString(str5) << "\n";
	std::cout << "Hello@123 -> " << IsValidString(str6) << "\n";

	std::cout << "\n=========== TEST END ===========\n";
}