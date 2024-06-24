#include "String.h"
#include <string>
#include <iostream>


String::String()
{
	data = new char[1];
	data[0] = '\0';
}

String::String(const char* _str)
{
	data = new char[strlen(_str) + 1];
	strcpy_s(data, strlen(_str) + 1, _str);
}

//Copy contructor
String::String(const String& _other)
{
	size_t l = strlen(_other.CStr()) + 1; // find out how big the buffer needs to be
	data = new char[l]; //create the new char*
	strcpy_s(data, l, _other.CStr()); //copy data over
}

String::~String()
{
	delete data;
}

size_t String::Length() const
{
	return strlen(data);
}

char& String::CharacterAt(size_t _index)
{
	return data[_index];
}

const char& String::CharacterAt(size_t _index) const
{
	return data[_index];
}

bool String::EqualTo(const String& _other) const
{
	return strcmp(data, _other.CStr()) == 0; //Returns 0 if	equal 
}

String& String::Append(const String& _str)
{
	size_t newLength = strlen(_str.data) + strlen(data) + 1;
	char* buffer = new char[newLength];
	buffer[0] = '\0';
	strcat_s(buffer, newLength, data);
	strcat_s(buffer, newLength, _str.data);
	
	delete data;
	data = buffer;
	
	return *this;

}

String& String::Prepend(const String& _str)
{
	size_t newLength = strlen(_str.data) + strlen(data) + 1;
	char* buffer = new char[newLength];
	buffer[0] = '\0';
	strcat_s(buffer, newLength, _str.data);
	strcat_s(buffer, newLength, data);
	
	
	delete data;
	data = buffer;

	return *this;
}

const char* String::CStr() const
{
	return data;
}

String& String::ToLower()
{
	for (int i = 0; i < strlen(data); i++) {
		data[i] = tolower(data[i]);
	}
	return *this;
}

String& String::ToUpper()
{
	for (int i = 0; i < strlen(data); i++) {
		data[i] = toupper(data[i]);
	}
	return *this;
}

size_t String::Find(const String& _str)
{
	return Find(0, _str);
}

size_t String::Find(size_t _startIndex, const String& _str)
{
	//char* buffer = strstr(data, _str.data);
	size_t index = SIZE_T_MAX;
	char* haystack = this->data;
	char* needle = _str.data;
	//haystack is this string, we need to brute force search too find the needle (incoming string)
	bool found = false;
	for (int i = _startIndex; i < strlen(haystack); i++) {
		if (found) {
			break; //If we found it leave the looop to avoid unnecessary work. 
		}
		else {
			if (haystack[i] == needle[0]) {

				index = i;
				//Early out if the needle is only on length 1 we know we have already found it
				if (strlen(needle) <= 1) {
					found = true;
					break;
				}
				//Else we need to loop through needle 
				for (int y = 1; y < strlen(needle); y++) {

					if (haystack[i + y] == needle[y]) {
						//If we have reached the end of the needle we have found the whole needle
						if (y == strlen(needle) - 1) {
							found = true; //set found to true
						}
						continue; //We always continue
					}
					else {
						index = SIZE_T_MAX;//set index to max 
						break; //Break the loop
					}
				}

			}
		}
	}
	return index;
}

String& String::Replace(const String& _find, const String& _replace)
{
	
	size_t indexOfFind = Find(_find);

	if (_find.Length() == _replace.Length()) {
		for (int i = 0; i < _find.Length(); i++) {
			data[indexOfFind + i] = _replace[i];
		}
	}
	//This is so dirty~!
	else if (_find.Length() >= _replace.Length()) {
		int newLength = Length() - (_find.Length() - _replace.Length()) + 1;
		char* buffer = new char[newLength];
		for (int i = 0; i < indexOfFind; i++) {
			buffer[i] = data[i];
		}
		for (int i = 0; i < _replace.Length(); i++) {
			buffer[indexOfFind + i] = _replace[i];
		}
		for (int i = indexOfFind + _replace.Length(); i < newLength - 1; i++) {
			buffer[i] = data[i + _find.Length()];
		}
		buffer[newLength - 1] = '\0';
		delete data;
		data = buffer;

	}

	else if (_find.Length() >= _replace.Length()) {
		int newLength = Length() + (_find.Length() - _replace.Length()) + 1;
		char* buffer = new char[newLength];

		for (int i = 0; i < indexOfFind; i++) {
			buffer[i] = data[i];
		}
	}
	// TODO: insert return statement here
	return *this;
}


bool String::operator==(const String& _other)
{
	return (*this).EqualTo(_other);
}

bool String::operator!=(const String& _other)
{
	return !(*this).EqualTo(_other);
}

String& String::operator=(const String& _str)
{
	size_t l = strlen(_str.data) + 1; // find out how big the buffer needs to be
	char* buffer = new char[l];
	strcpy_s(buffer, l, _str.data); //copy data over
	delete data;
	data = buffer; //create the new char*
	return *this;
}



char& String::operator[](size_t _index)
{
	return data[_index];
}

const char& String::operator[](size_t _index) const
{
	return data[_index];
}
