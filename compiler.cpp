#include "compiler.h"
#include <cstring>
#include "string.h"

Compiler::Compiler(char* fileName){
    in.open(fileName);
    openOutFile(fileName);
}

void Compiler::openOutFile(char* fileName){
    String s(fileName);
    if(s.substring(-4, -1) == String("spp"))
        out.open((s.substring(0, -4) + "cpp").c_str());
    if(s.substring(-6, -1) == String("class"))
        out.open((s.substring(0, -6) + "h").c_str());
}

void Compiler::getLines(){

    while(!in.eof()){
        String line = nextInputLine();
        Line l(line);
        lines.add(l);
    }

}

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

void Compiler::processIndentation(){

    for(int i = 0; i < lines.size(); i++){
        if(lines[i][-1] == ':'){
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
        } else {
            lines[i].semicolon();
        }
    }

}

void Compiler::translate(){
    for(int i = 0; i < lines.size(); i++){
        lines[i].translate();
    }
}

void Compiler::writeOutput(){
    for(int i = 0; i < lines.size(); i++)
      out << lines[i] << std::endl;
}

String Compiler::nextInputLine(){

    char line[Line::MAX_LINE_LENGTH];
    in.getline(line, Line::MAX_LINE_LENGTH);
    String s(line);

    return s;

}
