#ifndef TREE_NODE_H 
#define TREE_NODE_H 

#include <iostream>
using namespace std; 

template <typename T>
struct tree_node{
    T _item;
    tree_node<T>* _left;
    tree_node<T>* _right;
    int _height;

     tree_node(T item=T(), tree_node* left=NULL, tree_node* right=NULL): _item(item), _left(left), _right(right)
    {
        _height = -1;
        //don't forget to set the _height.
    }

    int balance_factor(){
        int leftHeight = -1, rightHeight = -1; 
        if(this->_left){
            leftHeight = this->_left->_height; 
        }

        if(this->_right){
            rightHeight = this->_right->_height; 
        }

        //balance factor = height of the left subtree - the height of the right subtree
        //a NULL child has a height of -1
        //a leaf has a height of 0 
      
        return (leftHeight - rightHeight); 
    }

    int height(){
        //if nullptr --> height equal -1
        int leftHeight = -1, rightHeight = -1; 
        if(this->_left != NULL){
            leftHeight = this->_left->_height; 
        }

        if(this->_right != NULL){
            rightHeight = this->_right->_height; 
        }
        
        // Height of a node is 1 + height of the "taller" child
        //A leaf node has a height of zero: 1 + max(-1,-1) 
        return  (1 + max(leftHeight, rightHeight)); 
    } 


    int update_height(){
        _height = height(); 
        return _height; 
        //set the _height member variable (call height();)
    }

    friend ostream& operator <<(ostream& outs, const tree_node<T>& t_node){
        outs<<"|"<<t_node._item<<"|";
        return outs; //cmake error 1 
    }
};

#endif 