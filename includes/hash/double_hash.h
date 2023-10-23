#ifndef DOUBLE_HASH_H 
#define DOUBLE_HASH_H

#include <vector>
#include <iostream>
#include "../../includes/hash/constants.h"


//a normal array //two hashing functions

using namespace std; 

template <typename T> 
class DoubleHash
{
public:
    static const int CAPACITY = TABLE_SIZE;        //size of the table //so cap
    DoubleHash( ); //CTOR

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
    friend ostream& operator << (ostream& outs, const DoubleHash<TT>& h){
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

    int hash2(int key) const{
        return (1 + key % (CAPACITY - 2)); //1 + so at least oneaway, //why Capacity - 2?
    }              //hash2 function

    //int next_index(int index, int key) const;       //wrap around index

    bool find_index(int key, int& index) const{ //key being ID number I assume 
       int count = 0, findIndex = hash(key); 
       while(_data[findIndex]._key != key && count < CAPACITY){
        if(findIndex == CAPACITY){
            findIndex = 0; 
        }
        findIndex++; 
        count++; 
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
DoubleHash<T>::DoubleHash( ){
    used = 0; 
    _collisions = 0; 

    //do we insert -1 here for entire vector data 
    for(int i = 0; i < CAPACITY; i++){
        _data.push_back(T()); //just using default constructor of T
        _data[i]._key = NEVER_USED; //default initialized //default intialize with empty recrods, with keys of -1? //doesnt exists so cant just index them 
    }
}//CTOR

template <typename T> 
bool DoubleHash<T>::insert(const T& entry){ //what if full?
    int jumpIndexes, index = hash(entry._key), findIndex; //hashing the key of the entry, not the entry itself cause don't make sense to hash a record 
    bool inserted = true; 

    if(used == CAPACITY){ //if full, don't insert
        return false; 
    }
    if(find_index(entry._key, findIndex)){//if already there, update //entry._key
        _data[findIndex] = entry; //does this count as a collision?
        return false; 
    }
    else{
        while(!is_vacant(index)){//find a vacant spot to insert //maybe start from index and not 0 becasue spreading?
        //newIndex = index; //set back to original index? //without the steps? or not necessary? //if reset will be giving me the same thing over and voer 
        _collisions++; 
        jumpIndexes = hash2(entry._key); //what if over capacity //going to give me the same jump indexes //hashing the entry I assume
        index += jumpIndexes;
        index = hash(index); //then we hash again to see if we need to roll over or not
       //not going to do a count variable since there must be at least one spot at this point, we just gotta find it
       }
       _data[index] = entry; 
    }
    //once we get out of the loop we should have an index that is indeed vacant 
   used++; 
   return inserted; 
} //so far seems to be working --> but deffo needs further testing for collision and used
//insert entry; false if overwriting. 

template <typename T>
bool DoubleHash<T>::remove(int key){
    int index; 
    if(find_index(key, index)){//if record found, delete 
        _data[index]._key = PREVIOUSLY_USED; 
        used--; 
        return true; 
    }
    //set removed index to previously used
    return false; 
}           
//remove this key

template<typename T>
bool DoubleHash<T>::is_present(int key) const{
    int tempIndex; 
    return (find_index(key, tempIndex)); 
}     
//is this key present?
//stopping at never used probably doesn't make sense for double hashing.. so just linear probe? 

template<typename T>
bool DoubleHash<T>::find(int key, T& result) const{//return the record with this key
int findIndex; 
    if(find_index(key, findIndex)){//if found, 
        result = _data[findIndex]; 
        return true; 
    }
    return false; 
} //result <- record with this key
#endif
