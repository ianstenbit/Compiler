#include "ifile.h"

IFile::IFile(){

}

IFile::IFile(const char* fileName){

    in.open(fileName);

}

bool IFile::hasNext(){

    return !in.eof();

}

String IFile::next(){

    char word[MAX_FILE_LINE_LENGTH];
    in >> word;
    return String(word);

}

String IFile::nextLine(){

    char word[MAX_FILE_LINE_LENGTH];
    in.getline(word, MAX_FILE_LINE_LENGTH);
    return String(word);

}

void IFile::close(){
    in.close();
}

std::ostream& operator<< (std::ostream& os, IFile& i){

    while(!i.in.eof()){
      os << i.nextLine() << std::endl;
    }

    return os;

}

IFile::~IFile(){
    in.close();
}
