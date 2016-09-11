/*
queue.h
Ian Johnson

Provides an implementation and interface to a FIFO queue structure
*/

#ifndef QUEUE
#define QUEUE

#include "linkedlist.h"

template<class T>
class Queue{

    public:

        T dequeue();
        T peek();
        void enqueue(T);

    private:

        LinkedList<T> data;

};

/*
Grab and remove the next element from the queue (FIFO)
@return: the next item in the queue
*/
template<class T>
T Queue<T>::dequeue(){
    return data.remove(0);
}

/*
Get the next item in the queue without removing it
@return: the next item in the queue
*/
template<class T>
T Queue<T>::peek(){
    return data[0];
}

/*
Add a new item to the queue
@param input: the new item to put into the list
*/
template<class T>
void Queue<T>::enqueue(T input){
    data.add(input);
}


#endif
