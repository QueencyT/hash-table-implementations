#ifndef RECORD_H 
#define RECORD_H
#include <iostream>
using namespace std; 

struct record
{
    int _key;
    double _value;
    record(int k=0, double v=0):_key(k), _value(v){}; 

    friend bool operator ==(const record& left, const record& right){
        //id assume its equal when id is equal 
        return (left._key == right._key); 
    }
    friend ostream& operator <<(ostream& outs, const record& print_me){
        outs<<"[id: "<<print_me._key<<"]["<<print_me._value<<"]";
        return outs; 
    }
};

#endif 