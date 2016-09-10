/*
ofile.cpp
Ian Johnson

Provides an implementation of an ofstream wrapper called oFile
*/


#include "ofile.h"

/*
Default constructor
*/
OFile::OFile(){

}

/*
Constructor which accepts file name of file to write to
@param fileName: the name of the file to write to
*/
OFile::OFile(const char* fileName){
    out.open(fileName);
}

/*
Returns the ofstream object which this class wraps, by reference
@return: a reference to the internal ofstream object
*/
std::ofstream& OFile::getStream(){
    return out;
}

/*
Closes this file stream
*/
void OFile::close(){
    out.close();
}

/*
Destructor
*/
OFile::~OFile(){
    out.close();
}
