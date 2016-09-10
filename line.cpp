/*
ifile.cpp
Ian Johnson

Provides an implementation of a Line class,
where a line represents a line of code
in Script++ which will be compiled
*/

#include "line.h"
#include <cstring>


/*
Default constructor
*/
Line::Line(){
    indentation = -1;
}

/*
Overloaded constructor which accepts a String as the contents of the line
@param input: the line, as a String
*/
Line::Line(String input){
    original = input;
    calculateIndentation();
}


/*
Calculates the space-indentation of a line.
Note that space indentation is used exclusively in Script++
*/
void Line::calculateIndentation(){
    indentation = 0;
    while(original[indentation++] == ' ');
    if(indentation%4 != 1){
        std::cout << "Indentation error on line:\n" << original << std::endl;
        exit(1);
    }
    indentation /= 4;
}

/*
Get the contents of a line as a String
@return: the Line as a String
*/
String Line::getString(){
    return original;
}

/*
Get the whitespace indentation of the line,
in 4-space levels (1 represents 4 spaces, 2 represents 8, ...)
@return: the indentation of the line
*/
int Line::getIndentation(){
    return indentation;
}

/*
Performs a series of compilation operations to switch from Script++ to C++
*/
void Line::translate(){
    original = original.substring(4*indentation, original.size());
    printCheck();
    includesCheck();
    indent(indentation);
}

/*
Performs compilation operation to translate Script++
print statement to C++
*/
void Line::printCheck(){
    if(original.size() > 6 && original.substring(0, 6) == String("print ")){
        String s = original.substring(6, original.size() - 1);
        s = String("std::cout << ") + s + String(" << std::endl;");
        original = s;
    } else if(original.size() > 8 && original.substring(0, 8) == String("printto ")){
        original = original.split()[1] + String(".getStream() << ") + original.split()[2].substring(0, -2) + String(" << std::endl;");
    }
}

/*
Performs compilation operation to translate Script++
include statement to C++
*/
void Line::includesCheck(){
    if(original.size() > 4 && original.substring(0, 4) == String("use ")){
        String s = original.substring(4, original.size() - 1);
        s = String("#include \"") + s + ".h\"";
        original = s;
    } else if(original.size() > 4 && original.substring(0, 4) == String("lib ")){
        String s = original.substring(4, original.size() - 1);
        s = String("#include <") + s + ">";
        original = s;
    }
}

/*
Checks if a line is a blank line
@return: true if the line is empty, a newline character, or only spaces and a newline
*/
bool Line::isEmpty(){
    if(original.size() <= 1) return true;
    for(int i = 0; i < original.size(); i++){
        if(original[i] != ' ' && original[i] != '\n'){
            return false;
        }
    }
    return true;
}

/*
Indents the line by levels*4 spaces
@param levels: the number of indentation levels to indent the line by
*/
void Line::indent(int levels){
    if(!levels) return;
    char* spaces = new char[levels*4+1];
    for(int i = 0; i < levels*4; i++) spaces[i] = ' ';
    spaces[levels*4] = 0;
    original = String(spaces) + original;
    indentation = levels;
    delete[] spaces;
}

/*
Adds a semicolon to the end of the line
*/
void Line::semicolon(){
    if(original.size() > 1 && original[-1] != '}' && original[-1] != ';')
        original = original + String(";");
}


/*
Stream insertion operator for writing the line to a file
*/
std::ostream& operator<<(std::ostream& os, const Line& line){
    os << line.original;
    return os;
}

/*
Bracket operator to access a specific character in the line
@param index: the index of the character to return
@return: a reference to the character at index
*/
char& Line::operator[] (const int index){
    return original[index];
}
