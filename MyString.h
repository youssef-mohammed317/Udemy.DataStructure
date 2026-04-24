#pragma once
#include <string>
#include <iostream>
using namespace std;


class MyString
{
	static void Perm(char* str = nullptr, int l = 0, int h = 0);
	static void Swap(char& x, char& y);
	static void Permutations(char* str = nullptr, char* res = nullptr, int* flags = nullptr, int k = 0, int l = 0);
public:
	static int GetLength(const char* string);

	static void ChangeCase(char* string);
	static int CountWords(const char* string);
	static int CountVowels(const char* string);
	static int CountConsonents(const char* string);
	static bool IsVowel(char c);
	static bool IsValidString(const char* string); // false if contains speial character
	static bool IsLetter(char c);
	static bool IsAlpha(char c);
	static bool IsNumber(char c);
	static bool IsLower(char c);
	static bool IsUpper(char c);
	static void Reverse(char* string);
	static bool Compare(const char* string1, const char* string2, bool ignoreCase = false);
	static bool IsPalindrome(const char* string);
	static bool IsAnagram(const char* string1, const char* string2);
	static string GetDuplicates(const char* string, bool ignoreCase = false);

	static void PrintPermutationsTreeMethod(char* str);
	static void PrintPermutationsSwapMethod(char* str);


	void static TestBehavior();

};

