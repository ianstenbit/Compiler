/*
Compiler.h
Ian Johnson
September 10, 2016

Provides an interface to a compiler class
which compiles code from "script ++" to cpp
*/

#ifndef COMPILER
#define COMPILER

#include <iostream>
#include <fstream>

#include "vector.h"
#include "line.h"
#include "string.h"

class Compiler{

    public:

        Compiler(char*);
        void compile();

    private:

        std::ifstream in;
        std::ofstream out;
        Vector<Line> lines;

        void openOutFile(char*);
        void getLines();
        void translate();
        void writeOutput();
        void processIndentation();
        String nextInputLine();

};

#endif
