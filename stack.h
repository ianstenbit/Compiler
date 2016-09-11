/*
stack.h
Ian Johnson

Provides an interface and implementation for a LIFO stack
*/

#ifndef STACK
#define STACK

#include "linkedlist.h"

template<class T>
class Stack{

    public:

        T pop();
        T peek();
        void push(T);

    private:

        LinkedList<T> data;

};

/*
Removes the next item from the stack and returns it
@return: the next item from the stack
*/
template<class T>
T Stack<T>::pop(){
    return data.remove(0);
}

/*
Returns the next item from the stack, without removing it
@return: the next item from the stack
*/
template<class T>
T Stack<T>::peek(){
    return data[0];
}

/*
Adds a new element to the top of the stack
@param input: the new item to add to the top of the stack
*/
template<class T>
void Stack<T>::push(T input){
    data.addToFront(input);
}


#endif
