/*
hashtable.h
Ian Johnson

Provides an interface and implementation of a
double-templated hash table in C++.

Collisions are handled by linked-list chaining.
*/

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

/*
Default constructor
*/
template <class KEY, class VALUE>
HashTable<KEY, VALUE>::HashTable(){
    data = new LinkedList< std::pair<KEY, VALUE> >[DEFAULT_SIZE];
    iterator.first = 0;
    iterator.second = -1;
    height = DEFAULT_SIZE;
    num_elements = 0;
}

/*
Iterator used for custom for-each loops.
Increments the internal iterator by one item in the map.
Note: may behave incorrectly if insertion occurs between iterations
@return: true if there was another element, false if end of map was found
*/
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


/*
Part of iterator for custom for-each loops
Returns the next item in the map using the internal iterator
@return: A key-value pair representing the next item in the map
*/
template <class KEY, class VALUE>
std::pair<KEY, VALUE> HashTable<KEY, VALUE>::next(){
    return data[iterator.first][iterator.second];
}

/*
Checks if the map is empty
@return: true if the map is empty, else false
*/
template <class KEY, class VALUE>
bool HashTable<KEY, VALUE>::empty(){
    return num_elements == 0;
}

/*
Copy constructor
Conforms to standard C++ STL copy constructor standard
*/
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

/*
Assignment operator
Conforms to standard C++ STL assignment operator standard
*/
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


/*
Destructor -- frees all data from map
*/
template <class KEY, class VALUE>
HashTable<KEY, VALUE>::~HashTable(){
    delete[] data;
}

/*
Inserts a new key/value pair into the map
@param key: the key of the new value to be inserted
@param value: the new value to be inserted
*/
template <class KEY, class VALUE>
void HashTable<KEY, VALUE>::insert(KEY key, VALUE value){
    data[hasher(key)%height].add(std::make_pair(key, value));
    num_elements++;
    if(num_elements / height >= CRITICAL_LOAD) rehash();
}

/*
Inserts a new key/value pair into the map
@param pair: a std::pair of the new key and values to add
*/
template <class KEY, class VALUE>
void HashTable<KEY, VALUE>::insert(std::pair<KEY, VALUE> pair){
    insert(pair.first, pair.second);
}

/*
Gets the value associated with a given key
@param key: the key being searched for
@return: the item associated with key, or null if no such item exists
*/
template <class KEY, class VALUE>
VALUE HashTable<KEY, VALUE>::get(KEY key){
    int index = hasher(key)%height;
    for(int i = 0; i < data[index].size(); i++){
        if(data[index][i].first == key)
            return data[index][i].second;
    }
    return NULL;
}

/*
Bracket index operator for accessing by key
Shortcut for .get(key)
*/
template <class KEY, class VALUE>
VALUE HashTable<KEY, VALUE>::operator[](KEY key){
    return get(key);
}

/*
Re-hash function which is called when CRITICAL_LOAD is reached
*/
template <class KEY, class VALUE>
void HashTable<KEY, VALUE>::rehash(){

    //calculate new height
    int newHeight = height * RESIZE_FACTOR;

    //Allocate new array of lists
    LinkedList< std::pair<KEY, VALUE> >* tmp = new LinkedList< std::pair<KEY, VALUE> >[newHeight];

    //Perform expensive re-hashing
    for(int i = 0; i < height; i++){
        for(int j = 0; j < data[i].size(); j++){
             tmp[hasher(data[i][j].first)%newHeight].add(data[i][j]);
        }
    }

    //Delete the old and save the new one
    delete[] data;
    data = tmp;
    height = newHeight;
}

/*
Overloaded stream insertion operator for printing everything in the table
Conforms to C++ STL stream insertion operator spec
*/
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
