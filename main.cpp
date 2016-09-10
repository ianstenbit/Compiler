/*
main.cpp
Ian Johnson

Provides a simple program to accept command-line input for compiling
code from Script++ to C++ using the Compiler class
*/

#include "vector.h"
#include "string.h"
#include "stack.h"
#include "queue.h"
#include "linkedlist.h"
#include "avltree.h"
#include "hashtable.h"
#include "line.h"
#include "compiler.h"

#include<iostream>

int main(int argc, char* argv[]){

    for(int i = 1; i < argc; i++){
        Compiler c(argv[i]);
        c.compile();
    }

}
