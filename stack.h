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

template<class T>
T Stack<T>::pop(){
    return data.remove(0);
}

template<class T>
T Stack<T>::peek(){
    return data[0];
}

template<class T>
void Stack<T>::push(T input){
    data.addToFront(input);
}


#endif
