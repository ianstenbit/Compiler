#ifndef LINKED_LIST
#define LINKED_LIST

#include <iostream>

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

template<class T>
LinkedList<T>::LinkedList(){
    head = 0;
    num_elements = 0;
}

template<class T>
LinkedList<T>::LinkedList(T input){
    head = new Node<T>();
    head->data = input;
    head->next = 0;
    num_elements = 1;
}

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

template<class T>
void LinkedList<T>::addToFront(T input){
    Node<T>* tmp = new Node<T>();
    tmp->data = input;
    tmp->next = head;
    head = tmp;
    num_elements++;
}


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

template<class T>
T LinkedList<T>::get(int index){
    Node<T>* tmp = head;
    for(int i = 0; i < index; i++) tmp = tmp->next;
    return tmp->data;
}

template<class T>
int LinkedList<T>::size(){
    return num_elements;
}

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

template<class T>
T& LinkedList<T>::operator[](int index){
    Node<T>* tmp = head;
    for(int i = 0; i < index; i++) tmp = tmp->next;
    return tmp->data;
}

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
This is N^2. Can be done in linear time
*/
template<class T>
std::ostream& operator<< (std::ostream& os, LinkedList<T>& L){
    for(int i = 0; i < L.size(); i++){
        os << L[i] << std::endl;
    }
    return os;
}

#endif
