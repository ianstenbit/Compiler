#include "line.h"
#include <cstring>


Line::Line(){
    indentation = -1;
}

Line::Line(String input){
    original = input;
    calculateIndentation();
}


void Line::calculateIndentation(){
    indentation = 0;
    while(original[indentation++] == ' ');
    if(indentation%4 != 1){
        std::cout << "Indentation error on line:\n" << original << std::endl;
        exit(1);
    }
    indentation /= 4;
}

String Line::getString(){
    return original;
}

int Line::getIndentation(){
    return indentation;
}

void Line::translate(){
    std::cout << original << "=====" << std::endl;
    original = original.substring(4*indentation, original.size());
    printCheck();
    includesCheck();
    doForEach();
    indent(indentation);
}

void Line::doForEach(){
    if(original.size() > 8 && original.substring(0,8) == String("foreach ")){
        Vector<String> words = original.split();
        if(words[4][-1] == ':') words[4] = words[4].substring(0,-1);

        original = String("if(!") + words[4] + String(".empty()){\n")
                 + String("do { \n")
                 + words[1] + String(" ") + words[2] + String(" = ") + words[4]
                 + "\n}";
    }
}

void Line::printCheck(){
    if(original.size() > 6 && original.substring(0, 6) == String("print ")){
        String s = original.substring(6, original.size() - 1);
        s = String("std::cout << ") + s + String(" << std::endl;");
        original = s;
    } else if(original.size() > 8 && original.substring(0, 8) == String("printto ")){
        original = original.split()[1] + String(".getStream() << ") + original.split()[2].substring(0, -2) + String(" << std::endl;");
    }
}

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

bool Line::isEmpty(){
    if(original.size() <= 1) return true;
    for(int i = 0; i < original.size(); i++){
        if(original[i] != ' ' && original[i] != '\n'){
            return false;
        }
    }
    return true;
}

void Line::indent(int levels){
    if(!levels) return;
    char* spaces = new char[levels*4+1];
    for(int i = 0; i < levels*4; i++) spaces[i] = ' ';
    spaces[levels*4] = 0;
    original = String(spaces) + original;
    indentation = levels;
    delete[] spaces;
}

void Line::semicolon(){
    if(original.size() > 1 && original[-1] != '}' && original[-1] != ';')
        original = original + String(";");
}

std::ostream& operator<<(std::ostream& os, const Line& line){
    os << line.original;
    return os;
}

char& Line::operator[] (const int index){
    return original[index];
}
