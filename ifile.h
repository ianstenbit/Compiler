/*
ifile.h
Ian Johnson

Provides an interface to an ifstream wrapper called iFile
*/

#ifndef IFILE
#define IFILE

#include "string.h"
#include <iostream>
#include <fstream>

#define MAX_FILE_LINE_LENGTH 1024

class IFile{

    public:

        IFile();
        IFile(const char*);

        ~IFile();

        String next();
        String nextLine();
        bool hasNext();
        void close();

        friend std::ostream& operator<< (std::ostream&, IFile&);

    private:

        std::ifstream in;

};


#endif
