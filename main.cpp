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
