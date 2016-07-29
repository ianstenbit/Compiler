#include "string.h"


String::String(){
    data = 0;
    length = 0;
}

String::String(const char* input){
    length = strlen(input);
    data = new char[length+1];
    strcpy(data, input);
}

String::String(const String& input){
    length = input.length;
    data = new char[length + 1];
    strcpy(data, input.data);
}

String& String::operator= (const char* rhs){
    length = strlen(rhs);
    if(data) delete[] data;
    data = new char[length+1];
    strcpy(data, rhs);
    return *this;
}

String& String::operator= (const String& rhs){
    length = strlen(rhs.data);
    if(data) delete[] data;
    data = new char[length+1];
    strcpy(data, rhs.data);
    return *this;
}

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

char& String::operator[] (const int index){
    if(index < 0)
      return data[length + index];
    else
      return data[index];
}

char* String::c_str(){
    return data;
}

bool String::operator== (const char* rhs){
    return strcmp(data, rhs) == 0;
}

bool String::operator== (const String& rhs){
    return strcmp(data, rhs.data) == 0;
}

bool String::operator> (const String& rhs){
    return strcmp(data, rhs.data) > 0;
}

int String::size(){
    return length;
}

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

std::ostream& operator<< (std::ostream& os, const String& in){
    os << in.data;
    return os;
}

String::~String(){
    if(data) delete[] data;
}
