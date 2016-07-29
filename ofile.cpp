#include "ofile.h"

OFile::OFile(){

}

OFile::OFile(const char* fileName){
    out.open(fileName);
}

std::ofstream& OFile::getStream(){
    return out;
}

void OFile::close(){
    out.close();
}

OFile::~OFile(){
    out.close();
}
