#ifndef VECTOR
#define VECTOR

#include<iostream>

template<class T>
class Vector{

  public:

      Vector();
      Vector(int);
      Vector(Vector<T>&);

      void add(T);
      void add(T, int);
      T get(int);

      ~Vector();

      int size();
      void sort();

      T& operator[](int);
      Vector<T>& operator=(Vector<T>&);
      Vector<T>& operator+=(T);

  private:

      T* data;

      int num_elements;
      int capacity;

      static const int DEFAULT_CAPACITY = 10;
      static const int RESIZE_FACTOR = 2;

      void resize();

};

template<class T>
Vector<T>::Vector(){
    num_elements = 0;
    capacity = DEFAULT_CAPACITY;
    data = new T[DEFAULT_CAPACITY];
}

template<class T>
Vector<T>::Vector(int startCap){
    num_elements = 0;
    capacity = startCap;
    data = new T[startCap];
}

template<class T>
Vector<T>::Vector(Vector<T>& input){
    num_elements = input.num_elements;
    capacity = input.capacity;
    data = new T[capacity];
    for(int i = 0; i < num_elements; i++)
        data[i] = input[i];
}

template<class T>
void Vector<T>::add(T newItem){
    if(num_elements == capacity) resize();
    data[num_elements++] = newItem;
}

template<class T>
void Vector<T>::add(T newItem, int index){

    if(num_elements == capacity) resize();

    for(int i = num_elements; i > index; i--){
        data[i] = data[i-1];
    }

    data[index] = newItem;
    num_elements++;
}

template<class T>
T Vector<T>::get(int index){
    return data[index];
}

template<class T>
Vector<T>::~Vector(){
    delete[] data;
}

template<class T>
int Vector<T>::size(){
    return num_elements;
}

template<class T>
void Vector<T>::sort(){
    bool sorted = false;
    while(!sorted){
        sorted = true;
        for(int i = 0; i < num_elements - 1; i++){
            if(data[i] > data[i+1]){
                sorted = false;
                T tmp = data[i];
                data[i] = data[i+1];
                data[i+1] = tmp;
            }
        }
    }
}

template<class T>
void Vector<T>::resize(){

    T* tmp = new T[capacity*RESIZE_FACTOR];
    for(int i = 0; i < capacity; i++) tmp[i] = data[i];
    delete[] data;
    data = tmp;
    capacity *= RESIZE_FACTOR;

}

template<class T>
T& Vector<T>::operator[](int index){
    return data[index];
}

template<class T>
Vector<T>& Vector<T>::operator=(Vector<T>& rhs){
    if(data) delete[] data;
    num_elements = rhs.num_elements;
    capacity = rhs.capacity;
    data = new T[capacity];
    for(int i = 0; i < num_elements; i++)
        data[i] = rhs[i];
    return *this;
}

template<class T>
Vector<T>& Vector<T>::operator+=(T t){
    add(t);
}


template<class T>
std::ostream& operator<<(std::ostream& os, Vector<T>& v){
    os << "[";
    for(int i = 0; i < v.size(); i++)
        os << v[i] << ((i == v.size()-1)? "]" : ", ");
    return os;
}

#endif