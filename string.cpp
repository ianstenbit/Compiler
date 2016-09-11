/*
string.cpp
Ian Johnson

Provides an implementation of a String class
*/


#include "string.h"

/*
Default constructor
*/
String::String(){
    data = 0;
    length = 0;
}

/*
Constructor which accepts c-string to build string
@param input: c-string which will be wrapped in the String class
*/
String::String(const char* input){
    length = strlen(input);
    data = new char[length+1];
    strcpy(data, input);
}

/*
Copy constructor
*/
String::String(const String& input){
    length = input.length;
    data = new char[length + 1];
    strcpy(data, input.data);
}

/*
Assignment operator to char*
*/
String& String::operator= (const char* rhs){
    length = strlen(rhs);
    if(data) delete[] data;
    data = new char[length+1];
    strcpy(data, rhs);
    return *this;
}

/*
Assignment operator to String class
*/
String& String::operator= (const String& rhs){
    length = strlen(rhs.data);
    if(data) delete[] data;
    data = new char[length+1];
    strcpy(data, rhs.data);
    return *this;
}

/*
Addition operator for concatenating two strings
*/
String String::operator+(const String& rhs){
    int len = length + rhs.length;
    char* newData = new char[len + 1];
    for(int i = 0; i < length; i++) newData[i] = data[i];
    for(int i = length; i < len; i++) newData[i] = rhs.data[i-length];
    newData[len] = 0;
    String s(newData);
    delete[] newData;
    return s;
}

/*
Bracket access operator to get a character from a String
@param index: the index of the char to return
@return: the char at the specified index, by reference
*/
char& String::operator[] (const int index){
    if(index < 0)
      return data[length + index];
    else
      return data[index];
}

/*
Getter for the c-string payload of the string
*/
char* String::c_str(){
    return data;
}

/*
Equality operator to check if String equals c-string
*/
bool String::operator== (const char* rhs){
    return strcmp(data, rhs) == 0;
}

/*
Equality operator to check if String equals String
*/
bool String::operator== (const String& rhs){
    return strcmp(data, rhs.data) == 0;
}

/*
Greater than operator for comparison of Strings
(for standard library sorting)
*/
bool String::operator> (const String& rhs){
    return strcmp(data, rhs.data) > 0;
}

/*
Gets the size of the string
@return: the number of non-null characters in the string
*/
int String::size(){
    return length;
}

/*
Splits the string based on a space delimiter
@return: a vector of strings, representing all space-delimited tokens in this string
*/
Vector<String> String::split(){

    Vector<String> ret;

    int ind = 0;
    char* tmp = new char[length];
    while(ind < length){

        int len = 0;
        while(data[ind++] != ' ') tmp[len++] = data[ind-1];
        tmp[len] = 0;

        if(len == 0) continue;

        ret.add(String(tmp));

    }

    delete[] tmp;

    return ret;

}

/*
Returns a section of the original string
@param start: the index of the first character to include
@param end: the index of the last character to include
@return: the section of the String from start to end
*/
String String::substring(int start, int end){
    if(start < 0) start += length + 1;
    if(end < 0) end += length + 1;
    char* tmp = new char[end - start + 1];
    for(int i = 0; i < end - start; i++) tmp[i] = data[i + start];
    tmp[end - start] = 0;
    String s(tmp);
    delete [] tmp;
    return s;
}

/*
Converts the string to lower case and returns the lower case form
Does not modify the existing string.
@return: the string, in lower case
*/
String String::toLower(){
    char* tmp = new char[length];
    for(int i = 0; i < length; i++)
        tmp[i] = tolower(data[i]);
    String s(tmp);
    return s;
}

/*
Stream insertion operator for printing
*/
std::ostream& operator<< (std::ostream& os, const String& in){
    os << in.data;
    return os;
}

/*
Destructor
*/
String::~String(){
    if(data) delete[] data;
}
