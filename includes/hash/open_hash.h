#ifndef OPEN_HASH_H 
#define OPEN_HASH_H

#include "../../includes/hash/constants.h"
#include <vector>

using namespace std; 


template <typename T> 
class OpenHash
{
public:
    static const int CAPACITY = TABLE_SIZE;        //size of the table //so cap
    OpenHash( ); //CTOR

    bool insert(const T& entry);   
    //insert entry; false if overwriting. //false if full and trying to insert? //or full 
    bool remove(int key);               
    //remove this key

    bool is_present(int key) const;      //is this key present?
    bool find(int key, T& result) const; //result <- record with this key
    int size( ) const { return used; }   //number of keys in this table
                                         //number of collisions in this table
    long collisions() const {return _collisions;} //need to updtate collisions 
    long capacity() const {return CAPACITY;}

    //print the entire talbe with keys, records, and hash values
    template<class TT>
    friend ostream& operator << (ostream& outs, const OpenHash<TT>& h){
        for(int i = 0; i < h.CAPACITY; i++){
            if(!h.is_vacant(i)){
                outs<<h._data[i]<<endl;  
            }
        }
        return outs; 
    }
private:

    static const int NEVER_USED = -1;        //this cell has never had a value
    static const int PREVIOUSLY_USED = -2;   //this cell has previously held a value that has since
                                             //been deleted.

    vector<T> _data;                          //table of records //include vector 
    int used;                                //number of keys in the table
    long _collisions;

    int hash(int key) const{
        return key % CAPACITY; 
    }//hash function

    bool find_index(int key, int& index) const{ //key being ID number I assume 
       int count = 0, findIndex = hash(key); 
       while(_data[findIndex]._key != key && !never_used(findIndex) && count < CAPACITY){ //while still in neighborhood
        findIndex++; 
        count++; 
        if(findIndex == CAPACITY){
            findIndex = 0; 
        }
       }
       index = findIndex; 
       return (_data[index]._key == key);  
    }//find index of this key

    bool never_used(int index) const{
        return (_data[index]._key == NEVER_USED); 
    }      //is this cell NEVER_USED

    bool is_vacant(int index) const{
        return (_data[index]._key == NEVER_USED || _data[index]._key == PREVIOUSLY_USED); 
    }//is this cell available for insert
};

template <typename T>
OpenHash<T>::OpenHash( ){
    used = 0; 
    _collisions = 0; 
}

template <typename T> 
bool OpenHash<T>::insert(const T& entry){
    int index = hash(entry._key), foundIndex; 

    if(used == CAPACITY){
        return false; 
    }

    if(find_index(entry._key, foundIndex)){
        _data[foundIndex] = entry; 
        return false; 
    }
    else{
        while(!is_vacant(index)){ //at this point, there's gotta be at least one open spot we just gotta find it
            index++; 
            _collisions++;
            index = hash(index); //see if we need to roll over 
        }
        _data[index] = entry; 
    }
    used++; 
    return true; 
} 
//insert entry; false if overwriting. //false if full and trying to insert? //or full 

template <typename T>
bool OpenHash<T>::remove(int key){
    int foundIndex; 
    if(find_index(key, foundIndex)){
        _data[foundIndex]._key = PREVIOUSLY_USED; //just turn to previously used?
        used--; 
        return true; 
    }
    return false; 
}            
//remove this key

template <typename T> 
bool OpenHash<T>::is_present(int key) const{ 
    int tempIndex; 
    return find_index(key, tempIndex); 
}//is this key present?

template <typename T>
bool OpenHash<T>::find(int key, T& result) const{
    int foundIndex; 
    if(find_index(key, foundIndex)){
        result = _data[foundIndex]; 
        return true; 
    }
    return false; 
}//result <- record with this key


#endif 