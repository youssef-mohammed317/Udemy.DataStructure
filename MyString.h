#pragma once
class MyString
{

public:
	int static GetLength(const char* string);

	void static ChangeCase(char* string);
	int static CountWords(const char* string);
	int static CountVowels(const char* string);
	int static CountConsonents(const char* string);
	bool static  IsVowel(char c);
	bool static IsValidString(const char* string); // false if contains speial character
	bool static IsLetter(char c);
	bool static IsAlpha(char c);
	bool static IsNumber(char c);
	bool static IsLower(char c);
	bool static IsUpper(char c);
	void static Reverse(char* string);


	void static TestBehavior();

};

