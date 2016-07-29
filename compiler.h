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
