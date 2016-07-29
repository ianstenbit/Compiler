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

template<class T>
T Queue<T>::dequeue(){
    return data.remove(0);
}

template<class T>
T Queue<T>::peek(){
    return data[0];
}

template<class T>
void Queue<T>::enqueue(T input){
    data.add(input);
}


#endif
