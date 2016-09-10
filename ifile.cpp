/*
ifile.cpp
Ian Johnson

Provides an implementation of an ifstream wrapper called iFile
*/

#include "ifile.h"

/*
Default constructor
*/
IFile::IFile(){

}

/*
Constructor with specified fileName
@param fileName: the name of the file to be read
*/
IFile::IFile(const char* fileName){

    in.open(fileName);

}

/*
Checks if there is more content in the file being read
@return: true if the file has more contents, else false
*/
bool IFile::hasNext(){

    return !in.eof();

}

/*
Grabs the next token from the file (space/newline delimited)
@return: the next token from the file
*/
String IFile::next(){

    char word[MAX_FILE_LINE_LENGTH];
    in >> word;
    return String(word);

}

/*
Grabs the next token from the file (newline delimited only)
@return: the next line from the file
*/
String IFile::nextLine(){

    char word[MAX_FILE_LINE_LENGTH];
    in.getline(word, MAX_FILE_LINE_LENGTH);
    return String(word);

}

/*
Closes the internal fstream
*/
void IFile::close(){
    in.close();
}

/*
Overloaded stream insertion operator.
Prints the entire contents of the file into another stream
*/
std::ostream& operator<< (std::ostream& os, IFile& i){

    while(!i.in.eof()){
      os << i.nextLine() << std::endl;
    }

    return os;

}

/*
Destructor
*/
IFile::~IFile(){
    in.close();
}
