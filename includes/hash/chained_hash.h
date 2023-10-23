#ifndef CHAINED_HASH_H 
#define CHAINED_HASH_H 
#include <iostream>

#include "../../includes/hash/constants.h"
#include "../../includes/avl/avl.h"

using namespace std; 

template <typename T> 
class ChainedHash
{
public:
    ChainedHash( );                              //CTOR

    bool insert(const T& entry);            //insert entry; false if overwriting.
    bool remove(int key);                   //remove this key

    bool find(int key, T& result) const;    //result <- record with key
    bool is_present(int key) const;         //is this key present in table?
    int size( ) const { return total_records; }  //number of keys in the table
    long capacity(){return TABLE_SIZE;}


    //print entire table with keys, etc.
    template<class TT>
    friend ostream& operator << (ostream& outs, const ChainedHash<TT>& h){
        for(int i = 0; i < TABLE_SIZE; i++){
           if(h._data[i].empty()){
            continue; 
           }
           outs<<h._data[i]; 
        }
        return outs; 
    }

private:
    AVL<T> _data[TABLE_SIZE];               //table chains
    int total_records;                      //number of keys in the table

    int hash(int key) const{
        return key % TABLE_SIZE; 
    }               //hash function
};

template <typename T>
ChainedHash<T>::ChainedHash( ){
    total_records = 0; 
}                              //CTOR

template <typename T>
bool ChainedHash<T>::is_present(int key) const{
    T temp; 
    return find(key, temp); 
}//is this key present in table?

template <typename T>
bool ChainedHash<T>::find(int key, T& result) const{
    T findThis (key); 
    tree_node<T>* foundEntry;
    int findIndex = hash(key); 
    
    if(_data[findIndex].search(findThis, foundEntry)){
        result = foundEntry->_item; 
        return true; 
    } 

    return false;
}//result <- record with key

template <typename T>
bool ChainedHash<T>::insert(const T& entry){
   // cout<<"entry: "<<entry<<endl; 
    int index = hash(entry._key); 
    T findThis(entry._key); 
    tree_node<T>* foundEntry; 
    
    if(total_records == TABLE_SIZE){
        return false; 
    }

    if(is_present(entry._key)){ //already there
        _data[index].search(entry, foundEntry); //was just entry before //nvm works either way
        *foundEntry = entry; //update entry 
        return false; //did not insert 
    }
    
    _data[index].insert(entry); //hmm? will this do what I want
    total_records++; 
    return true; 
}           //insert entry; false if overwriting.

template <typename T> 
bool ChainedHash<T>::remove(int key){
    T findThis(key); 
    int index = hash(key); 

    if(_data[index].erase(findThis)){
        total_records--; 
        return true; 
    }

    return false; 
}//remove this key
#endif 