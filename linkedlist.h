/*
linkedlist.h
Ian Johnson

Provides an interface and implementation for a templated
singly-linked list. Includes head pointer only
*/

#ifndef LINKED_LIST
#define LINKED_LIST

#include <iostream>

/*
Node structure for singly-lined list
*/
template <class T>
struct Node{
  Node<T>* next;
  T data;
};


template<class T>
class LinkedList{

    public:

        LinkedList();
        LinkedList(T);
        LinkedList(const LinkedList<T>&);

        void add(T);
        void addToFront(T);
        T get(int);
        int size();
        T remove(int);

        ~LinkedList();

        T& operator[](int);
        LinkedList<T>& operator=(LinkedList<T>&);

    private:

        Node<T>* head;
        int num_elements;

};

/*
Default constructor
*/
template<class T>
LinkedList<T>::LinkedList(){
    head = 0;
    num_elements = 0;
}

/*
Constructor which accepts a first element
@param input: the first element to put at the head of the list
*/
template<class T>
LinkedList<T>::LinkedList(T input){
    head = new Node<T>();
    head->data = input;
    head->next = 0;
    num_elements = 1;
}

/*
Copy Constructor
*/
template<class T>
LinkedList<T>::LinkedList(const LinkedList<T>& input){
    head = 0;
    Node<T>* tmp = input.head;
    while(tmp){
        add(tmp->data);
        tmp = tmp->next;
    }
    num_elements = input.num_elements;
}

/*
Adds an element to the tail of the list
@param input: the element to add to the tail of the list
*/
template<class T>
void LinkedList<T>::add(T input){
    Node<T>* tmp = new Node<T>();
    tmp->data = input;
    tmp->next = 0;

    if(head){
        Node<T>* it = head;
        while(it->next) it = it->next;
        it->next = tmp;
    } else {
        head = tmp;
    }

    num_elements++;
}

/*
Adds an element to the front of the list
@param input: the item to add to the head of the list
*/
template<class T>
void LinkedList<T>::addToFront(T input){
    Node<T>* tmp = new Node<T>();
    tmp->data = input;
    tmp->next = head;
    head = tmp;
    num_elements++;
}


/*
Removes an element from a given index in the list
@param index: the index from which to remove the element
*/
template<class T>
T LinkedList<T>::remove(int index){

    if(index == 0){

        Node<T>* tmp = head->next;
        T ret = head->data;
        delete head;
        head = tmp;
        return ret;

    }

    Node<T>* tmp = head;
    for(int i = 0; i < index - 1; i++) tmp = tmp->next;
    Node<T>* nxt = tmp->next->next;
    T ret = tmp->next->data;
    delete tmp->next;
    tmp->next = nxt;
    return ret;

}

/*
Get the item at a given index
@param index: the index of the item to return
*/
template<class T>
T LinkedList<T>::get(int index){
    Node<T>* tmp = head;
    for(int i = 0; i < index; i++) tmp = tmp->next;
    return tmp->data;
}

/*
Gets the number of elements in the list
@return: the number of elements in the list
*/
template<class T>
int LinkedList<T>::size(){
    return num_elements;
}

/*
Assignment operator
*/
template<class T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList<T>& input){
    head = 0;
    Node<T>* tmp = input.head;
    while(tmp){
        add(tmp->data);
        tmp = tmp->next;
    }
    num_elements = input.num_elements;
    return *this;
}

/*
Bracket access operator -- syntax sugar for .get(index)
*/
template<class T>
T& LinkedList<T>::operator[](int index){
    Node<T>* tmp = head;
    for(int i = 0; i < index; i++) tmp = tmp->next;
    return tmp->data;
}

/*
Destructor
*/
template<class T>
LinkedList<T>::~LinkedList(){
    Node<T>* tmp = head;
    while(tmp){
      Node<T>* nxt = tmp->next;
      delete tmp;
      tmp = nxt;
    }
    head = 0;
}


/*
Stream insertion operator for printing list
This is N^2. Can be done in linear time. Just threw this together
*/
template<class T>
std::ostream& operator<< (std::ostream& os, LinkedList<T>& L){
    for(int i = 0; i < L.size(); i++){
        os << L[i] << std::endl;
    }
    return os;
}

#endif
