#ifndef HASH_TABLE
#define HASH_TABLE

#include <iostream>
#include <functional>
#include "linkedlist.h"

template <class KEY, class VALUE>
class HashTable{

  public:

      void insert(KEY, VALUE);
      void insert(std::pair<KEY, VALUE>);
      VALUE get(KEY);
      VALUE operator[] (KEY);

      void print();
      std::pair<KEY, VALUE> next();
      bool iterate();
      bool empty();

      HashTable();
      HashTable(HashTable&);
      ~HashTable();

      HashTable& operator=(const HashTable&);

  private:

      LinkedList< std::pair<KEY, VALUE> >* data;
      int height;
      int num_elements;

      std::hash<KEY> hasher;
      std::pair<int, int> iterator;

      static const int RESIZE_FACTOR = 2;
      static const int CRITICAL_LOAD = 2;
      static const int DEFAULT_SIZE = 10;

      void rehash();

};

template <class KEY, class VALUE>
HashTable<KEY, VALUE>::HashTable(){
    data = new LinkedList< std::pair<KEY, VALUE> >[DEFAULT_SIZE];
    iterator.first = 0;
    iterator.second = -1;
    height = DEFAULT_SIZE;
    num_elements = 0;
}

template <class KEY, class VALUE>
bool HashTable<KEY, VALUE>::iterate(){
    if(iterator.second < data[iterator.first].size() - 1){
        iterator.second++;
        return true;
    } else {
        while(++iterator.first < height){
            if(data[iterator.first].size() > 0){
                iterator.second = 0;
                return true;
            }
        }
        iterator.first = 0;
        return false;
    }
}

template <class KEY, class VALUE>
std::pair<KEY, VALUE> HashTable<KEY, VALUE>::next(){
    return data[iterator.first][iterator.second];
}

template <class KEY, class VALUE>
bool HashTable<KEY, VALUE>::empty(){
    return num_elements == 0;
}

template <class KEY, class VALUE>
HashTable<KEY, VALUE>::HashTable(HashTable<KEY, VALUE>& other){
    data = new LinkedList< std::pair<KEY, VALUE> >[DEFAULT_SIZE];
    height = DEFAULT_SIZE;
    iterator.first = 0;
    iterator.second = 0;
    while(other.iterate()){
        insert(other.next());
    }
}

template <class KEY, class VALUE>
HashTable<KEY, VALUE>& HashTable<KEY, VALUE>::operator=(const HashTable<KEY, VALUE>& other){
    data = new LinkedList< std::pair<KEY, VALUE> >[DEFAULT_SIZE];
    height = DEFAULT_SIZE;
    iterator.first = 0;
    iterator.second = 0;
    do{
        insert(other.next());
    } while(other.iterate());
    return *this;
}

template <class KEY, class VALUE>
HashTable<KEY, VALUE>::~HashTable(){
    delete[] data;
}

template <class KEY, class VALUE>
void HashTable<KEY, VALUE>::insert(KEY key, VALUE value){
    data[hasher(key)%height].add(std::make_pair(key, value));
    num_elements++;
    if(num_elements / height >= CRITICAL_LOAD) rehash();
}

template <class KEY, class VALUE>
void HashTable<KEY, VALUE>::insert(std::pair<KEY, VALUE> pair){
    insert(pair.first, pair.second);
}

template <class KEY, class VALUE>
VALUE HashTable<KEY, VALUE>::get(KEY key){
    int index = hasher(key)%height;
    for(int i = 0; i < data[index].size(); i++){
        if(data[index][i].first == key)
            return data[index][i].second;
    }
    return NULL;
}

template <class KEY, class VALUE>
VALUE HashTable<KEY, VALUE>::operator[](KEY key){
    return get(key);
}

template <class KEY, class VALUE>
void HashTable<KEY, VALUE>::rehash(){
    int newHeight = height * RESIZE_FACTOR;
    LinkedList< std::pair<KEY, VALUE> >* tmp = new LinkedList< std::pair<KEY, VALUE> >[newHeight];
    for(int i = 0; i < height; i++){
        for(int j = 0; j < data[i].size(); j++){
             tmp[hasher(data[i][j].first)%newHeight].add(data[i][j]);
        }
    }
    delete[] data;
    data = tmp;
    height = newHeight;
}

template <class KEY, class VALUE>
void HashTable<KEY, VALUE>::print(){

    for(int i = 0; i < height; i++){
        for(int j = 0; j < data[i].size(); j++){
            std::cout << "[" << data[i][j].first << ", " << data[i][j].second << "]" << std::endl;
        }
    }

}

template <class KEY, class VALUE>
std::ostream& operator<< (std::ostream& os, HashTable<KEY, VALUE> t){

    if(t.empty()) return os << "Empty HashTable";

    os << "[";

    while(t.iterate()){
        std::pair<KEY, VALUE> pair = t.next();
        os << "{" << pair.first << ", " << pair.second << "}, ";
    }

    return os << "\b\b]";

}

#endif
