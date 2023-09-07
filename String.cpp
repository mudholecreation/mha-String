#include "String.h"


unsigned int mha::StringLength(const char* cstring)
{
	unsigned int i = 0;
	while ((cstring[i]) != '\0')
	{
		i++;
	}
	return i;
}

void mha::StringLower(String & string)
{
	for (int i = 0; i < string.Size(); i++)
	{
		if (string[i] >= 'A' && string[i] <= 'Z')
		{
			string[i] += ' ';
		}
	}
}

void mha::StringLower(char* cstring)
{
	unsigned int size = StringLength(cstring);
	for (int i = 0; i < size; i++)
	{
		if (cstring[i] >= 'A' && cstring[i] <= 'Z')
		{
			cstring[i] += ' ';
		}
	}
}
void mha::StringLower(char* cstring, unsigned int size)
{
	for (int i = 0; i < size; i++)
	{
		if (cstring[i] >= 'A' && cstring[i] <= 'Z')
		{
			cstring[i] += ' ';
		}
	}
}
mha::String::String()
{
}

mha::String::String(const char character):size(1)
{
	memcpy(smallString, &character, size);
}
mha::String::String(const char* cstring):size(StringLength(cstring))
{
	if (size >= SMALL_STRING_SIZE)
	{
		capacity <<= 1;
		data = (char*)malloc(capacity);
		if (data == nullptr)
		{
			throw std::exception("String(const char* cstring) malloc failed - not enough memory");
		}
	}
	memcpy(data, cstring, size + 1);
}
mha::String::String(const String& string):size(string.size)
{
	if (size >= SMALL_STRING_SIZE)
	{
		capacity <<= 1;

		data = (char*)malloc(capacity);
		if (data == nullptr)
		{
			throw std::exception("String(const String& string) malloc failed - not enough memory");
		}
	}
	memcpy(data, string.data, size + 1);
}
int GetPlaceValue(int number, float digit)
{
	return int(number * digit) % 10;
}
mha::String::String(const int number)
{
	if (number < 0)
	{
		data[size] = '-';
		size++;
	}
	int value = 0;
	for (int i = -9; i < 1; i++)
	{

		value = GetPlaceValue(number, i);
		if (value == -1)
		{
			continue;
		}
		data[size] = char(value + 48);
		size++;
	}
	data[size] = '\0';
}
mha::String::String(const float number)
{
	if (number < 0)
	{
		data[size] = '-';
		size++;
	}
	int value = 0;
	for (int i = -39; i < 6; i++)
	{
		value = GetPlaceValue(number, i);
		if (value == -1)
		{
			continue;
		}
		if (size >= capacity)
		{
			if (capacity > SMALL_STRING_SIZE)
			{
				capacity <<= 1;

				data = (char*)realloc(data, capacity);
				if (data == nullptr)
				{
					throw std::exception("String(const float number) - realloc failed - not enough memory");
				}
			}
			else
			{
				capacity <<= 1;
				data = (char*)malloc(capacity);
				if (data == nullptr)
				{
					throw std::exception("String(const float number) - malloc failed - not enough memory");
				}
			}
		}
		data[size] = char(value + 48);
		size++;
		if (i == 0)
		{
			data[size] = '.';
			size++;
		}
	}
	data[size] = '\0';
}

mha::String& mha::String::operator=(const char* cstring)
{
	size = StringLength(cstring);
	if (size >= capacity)
	{
		if (capacity > SMALL_STRING_SIZE)
		{
			capacity <<= 1;
			data = (char*)realloc(data, capacity);
			if (data == nullptr)
			{
				throw std::exception("String::operator=(const char* cstring) - realloc failed - not enough memory");
			}
		}
		else
		{
			capacity <<= 1;
			data = (char*)malloc(capacity);
			if (data == nullptr)
			{
				throw std::exception("String::operator=(const char* cstring) - malloc failed - not enough memory");
			}
		}
	}
	memcpy(data, cstring, size + 1);
	return *this;
}
mha::String& mha::String::operator=(const String& string)
{
	size = string.size;
	if (size >= capacity)
	{
		if (capacity > SMALL_STRING_SIZE)
		{
			capacity <<= 1;
			data = (char*)realloc(data, capacity);
			if (data == nullptr)
			{
				throw std::exception("String::operator=(const String& string) - realloc failed - not enough memory");
			}
		}
		else
		{
			capacity <<= 1;
			data = (char*)malloc(capacity);
			if (data == nullptr)
			{
				throw std::exception("String::operator=(const String& string) - malloc failed - not enough memory");
			}
		}
	}
	memcpy(data, string.data, size + 1);
	return *this;
}
mha::String mha::String::operator+(const char* cstring)
{
	String newString;
	newString.size = size + StringLength(cstring);
	if (newString.size >= SMALL_STRING_SIZE)
	{
		newString.capacity = newString.size + 1;
		newString.data = (char*)malloc(newString.capacity);
		if (newString.data == nullptr)
		{
			throw std::exception("String::operator+(const char* cstring) - malloc failed - not enough memory");
		}
	}
	memcpy(newString.data, data, size);
	memcpy(&newString.data[size], cstring, StringLength(cstring) + 1);
	return newString;
}

mha::String mha::String::operator+(const String& string)
{
	String newString;
	newString.size = size + string.size;
	if (newString.size >= SMALL_STRING_SIZE)
	{
		newString.capacity = newString.size + 1;
		newString.data = (char*)malloc(newString.capacity);
		if (newString.data == nullptr)
		{
			throw std::exception("String::operator+(const String& string) - malloc failed - not enough memory");
		}
	}
	memcpy(newString.data, data, size);
	memcpy(&newString.data[size], string.data, string.size + 1);
	return newString;
}
mha::String& mha::String::operator+=(const char* cstring)
{
	unsigned int oldSize = size;
	size = size + StringLength(cstring);
	if (size >= capacity)
	{
		if (capacity > SMALL_STRING_SIZE)
		{
			capacity <<= 1;
			data = (char*)realloc(data, capacity);
			if (data == nullptr)
			{
				throw std::exception("String - realloc failed - not enough memory");
			}
		}
		else
		{
			char temp[SMALL_STRING_SIZE];
			memcpy(temp, data, oldSize);
			capacity <<= 1;
			data = (char*)malloc(capacity);
			if (data == nullptr)
			{
				throw std::exception("String - malloc failed - not enough memory");
			}
			memcpy(data, temp, oldSize);
		}
	}
	memcpy(&data[oldSize], cstring, StringLength(cstring) + 1);
	return *this;
}
mha::String& mha::String::operator+=(const String& string)
{
	int oldSize = size;
	size += string.size;
	if (size >= capacity)
	{
		if (capacity > SMALL_STRING_SIZE)
		{
			capacity <<= 1;

			data = (char*)realloc(data, capacity);
			if (data == nullptr)
			{
				throw std::exception("String - realloc failed - not enough memory");
			}
		}
		else
		{
			char temp[SMALL_STRING_SIZE];
			memcpy(temp, data, oldSize);
			capacity <<= 1;

			data = (char*)malloc(capacity);
			if (data == nullptr)
			{
				throw std::exception("String - malloc failed - not enough memory");
			}
			memcpy(data, temp, oldSize);
		}
	}
	memcpy(&data[oldSize], string.data, string.size + 1);
	return *this;
}
bool mha::String::operator==(const char * cstring)
{
	if (size == StringLength(cstring))
	{
		if (memcmp(data, cstring, size) == 0)
			return true;
	}
	return false;
}

bool mha::String::operator!=(const char * cstring)
{
	if (size == StringLength(cstring))
	{
		if (memcmp(data, cstring, size) == 0)
			return false;
	}
	return true;
}
bool mha::String::operator==(const String& string)
{
	if (size == string.size)
	{
		if (memcmp(data, string.data, size) == 0)
		return true;
	}
	return false;
}

bool mha::String::operator!=(const String& string)
{
	if (size == string.size)
	{
		if (memcmp(data, string.data, size) == 0)
			return false;
	}
	return true;
}
void mha::String::Clear()
{
	if (capacity > SMALL_STRING_SIZE)
	{
		free(data);
		data = nullptr;
	}
	data = smallString;
	capacity = SMALL_STRING_SIZE;
	size = 0;
	memset(&data, 0, SMALL_STRING_SIZE);
}
char& mha::String::operator[](const unsigned int index)
{
	if (index >= size || index < 0)
	{
		Clear();
		throw std::exception("String::operator[](const unsigned int index) - Index out of range");
	}
	return data[index];
}
unsigned int mha::String::Size() const
{
	return size;
}
std::ostream& mha::operator<<(std::ostream& os, const mha::String& string)
{
	os << string.data;
	return os;
}
unsigned int mha::String::Capacity() const
{
	return capacity - 1;
}
const char* mha::String::Data() const
{
	return data;
}
void mha::String::Replace(unsigned int index, char character)
{
	if (index >= size || index < 0)
	{
		if (size > SMALL_STRING_SIZE)
		{
			Clear();
		}
		throw std::exception("String::Replace(unsigned int index, char character) - Array index out of range");
	}
	else
	{
		memcpy(&data[index], &character, 1);
	}
}
mha::String::~String()
{
	if (capacity > SMALL_STRING_SIZE)
	{
		free(data);
		data = nullptr;
	}
}

int mha::STOI(String& string)
{
	int number(0);
	bool negative(string.Data()[0] == '-');
	for (unsigned int i = negative; i < string.Size(); i++)
	{
		if (string.Data()[i] >= '0' && string.Data()[i] <= '9')
		{
			number = (number * 10) + (string.Data()[i] - '0');
		}
		else
		{
			if (!number)
			{
				throw std::exception("String - STOI - Invalid Argument");
			}
			break;
		}
	}
	number = number * ((negative * -2) + 1);
	if (!negative && number < 0 || negative && number > 0)
	{
		throw std::exception("String - STOI - Number out of range");
	}
	return number;
}

float mha::STOF(String & string)
{
	float number(0.0);
	bool negative(string.Data()[0] == '-');
	float decimal(1.0f);
	bool found = false;
	for (unsigned int i = negative; i < string.Size(); i++)
	{
		if (string.Data()[i] >= '0' && string.Data()[i] <= '9')
		{
			if (!found)
			{
				number = (number * 10) + (string.Data()[i] - '0');
			}
			else
			{
				number = number + ((string.Data()[i] - '0') * (decimal *= 0.1f));
			}
		}
		else
		{
			if (string.Data()[i] == '.')
			{
				found = true;
			}
			else
			{
				if (!number)
				{
					throw std::exception("String - STOF - Invalid Argument");
				}
				break;
			}
		}
	}
	
	if (number >= INFINITY)
	{
		throw std::exception("String - STOF - Number out of range");
	}
	number = number * ((negative * -2) + 1);
	
	return number;
}

void mha::StringReverse(String& string)
{
	String newString(string);
	int j = newString.Size() - 1;
	for (unsigned int i = 0; i < newString.Size(); i++)
	{
		string[i] = newString[j];
		j--;
	}
}

bool mha::StringFind(const char* str, unsigned int strSize,
	const char* data, unsigned int dataSize)
{
	unsigned int j = 0;
	for (size_t i = 0; i < dataSize; i++)
	{
		if (data[i] == str[j])
		{
			if (j == strSize - 1)
			{
				return true;
			}
			j++;
		}
		else
		{
			j = 0;
		}
	}
	return false;
}

