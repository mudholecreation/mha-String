#pragma once
#include <iostream>

namespace mha
{
	const unsigned int SMALL_STRING_SIZE = 16;
	class String
	{
	public:
		String();
		String(const char character);
		String(const char* cstring);
		String(const String& string);
		String(const int number);
		String(const float number);
		String& operator=(const char* cstring);
		String& operator=(const String& string);
		String operator+(const char* cstring);
		String operator+(const String& string);
		String& operator+=(const char* cstring);
		String& operator+=(const String& string);
		bool operator==(const char* cstring);
		bool operator!=(const char* cstring);
		bool operator==(const String& buffer);
		bool operator!=(const String& buffer);
		void Clear();
		char& operator[](const unsigned int index);
		unsigned int Size() const;
		friend std::ostream& operator<<(std::ostream& os, const String& string);
		unsigned int Capacity() const;
		const char* Data() const;
		void Replace(unsigned int index, char character);
		~String();

	private:
		unsigned int size = 0;
		unsigned int capacity = SMALL_STRING_SIZE;
		char smallString[SMALL_STRING_SIZE];
		char* data = smallString;
	};

	int STOI(String& string);
	float STOF(String& string);
	void StringReverse(String& string);
	bool StringFind(const char * str, unsigned int strSize, const char * data, unsigned int dataSize);
	unsigned int StringLength(const char* cstring);
	void StringLower(String& string);
	void StringLower(char* cstring);
	void StringLower(char* cstring, unsigned int size);


}
