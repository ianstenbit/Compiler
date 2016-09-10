/*
Compiler.cpp
Ian Johnson
September 10, 2016

Provides an implementation of a compiler class
which compiles code from "script ++" to cpp
*/

#include "compiler.h"
#include <cstring>
#include "string.h"

/*
Constructor requires name of file to be translated
@param fileName: c-string representing name of file to translate
*/
Compiler::Compiler(char* fileName){
    in.open(fileName);
    openOutFile(fileName);
}

/*
Opens a filestream to write the compiled output to a .cpp or .h file
@param fileName: c-string representing name of file to translate
*/
void Compiler::openOutFile(char* fileName){
    String s(fileName);
    if(s.substring(-4, -1) == String("spp"))
        out.open((s.substring(0, -4) + "cpp").c_str());
    if(s.substring(-6, -1) == String("class"))
        out.open((s.substring(0, -6) + "h").c_str());
}

/*
Reads the lines from the input  file into a vector of lines
*/
void Compiler::getLines(){

    while(!in.eof()){
        String line = nextInputLine();
        Line l(line);
        lines.add(l);
    }

}

/*
Compiles the code by calling a series of pre-processing and compilation methods
*/
void Compiler::compile(){

    std::cout << "Get Lines" << std::endl;
    getLines();

    std::cout << "Process Indentation" << std::endl;
    processIndentation();

    std::cout << "Translate" << std::endl;
    translate();

    std::cout << "Write Output" << std::endl;
    writeOutput();

}

/*
Pre-processing function which replaces colon-whitespace delimiting with bracket delimiting
*/
void Compiler::processIndentation(){

    /*Iterate through every input line*/
    for(int i = 0; i < lines.size(); i++){

        //If a colon is found
        if(lines[i][-1] == ':'){

            //Find the end of the indented block for the colon and add curly braces
            if(lines[i].getString().size() > 6 && lines[i].getString().substring(-8, -1) == String("public:")) continue;
            if(lines[i].getString().size() > 7 && lines[i].getString().substring(-9, -1) == String("private:")) continue;
            lines[i][-1] = '{';
            int index = i;
            int indentation = lines[index++].getIndentation();
            while(index < lines.size() && (lines[index].isEmpty() || lines[index].getIndentation() > indentation)) index++;
            String s("}");
            if(lines[i].getString().size() > 6 && lines[i].getString().substring(0, 6) == "class ")
                s = s + String(";");
            Line newLine(s);
            newLine.indent(indentation);
            lines.add(newLine, index);

        //If no colon is found
        } else {

            //Add a semicolon
            lines[i].semicolon();

        }
    }

}

/*
Translates each line of code line-by-line. Main compile step
*/
void Compiler::translate(){
    for(int i = 0; i < lines.size(); i++){
        lines[i].translate();
    }
}

/*
Writes the translated output to the output file stream
*/
void Compiler::writeOutput(){
    for(int i = 0; i < lines.size(); i++)
      out << lines[i] << std::endl;
}

/*
Reads the next input line from the file and returns it as a String
*/
String Compiler::nextInputLine(){

    char line[Line::MAX_LINE_LENGTH];
    in.getline(line, Line::MAX_LINE_LENGTH);
    String s(line);

    return s;

}
