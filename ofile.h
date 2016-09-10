/*
ofile.h
Ian Johnson

Provides an interface to an ofstream wrapper called oFile
*/


#ifndef OFILE
#define OFILE

#include <fstream>

class OFile{

    public:

        OFile();
        OFile(const char*);

        std::ofstream& getStream();

        void close();

        ~OFile();

    private:

        std::ofstream out;

};

#endif
