#ifndef AVL_H 
#define AVL_H 

#include "../../includes/avl/tree_node.h" 
#include "../../includes/avl/avl_functions.h"

using namespace std; 

template <typename T>
class AVL{
public:
    AVL(){
        _root = NULL; 
    }
    AVL(const T *list, int size = -1){
        _root = tree_from_sorted_list(list, size); 
    }
    //. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    AVL(const AVL<T> &copy_me){
       _root = tree_copy(copy_me._root); 
    }

    AVL<T> &operator=(const AVL<T> &rhs){
        if(this == &rhs){
            return *this; 
        }

        tree_clear(_root); 
        _root = tree_copy(rhs._root); 
        return *this; 
    }
    ~AVL(){
        tree_clear(_root); 
        _root = NULL; 
    }

    //. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    bool insert(const T &insert_me){
        tree_insert(_root, insert_me); 
        return (tree_search(_root, insert_me) != NULL); //since no duplicates, gotta return true //gotta ask?? 
    }

    bool erase(const T &target){
        return tree_erase(_root, target); 
    }

    bool contains(const T &target) const{
        return tree_search(_root, target); 
    }

    void clear(){
        tree_clear(_root); 
    }

    void clear_all(){
        tree_clear(_root); //?? difference? 
    }

    bool empty()const{
        return (_root == NULL); 
    }

    string pre_order() const{
        return pre_order_string(_root); 
    }

    string in_order() const{
        return in_order_string(_root);
    }

    string post_order() const{
        return post_order_string(_root); 
    }

    bool search(const T &target, tree_node<T> *&found_ptr) const{
        return tree_search(_root, target, found_ptr); 
    }

    void output_inorder(ostream &outs){
        in_order(_root, outs); 
    }

    friend ostream& operator <<(ostream& outs, const AVL<T>& tree){
       // tree_print_debug(tree._root,0,outs); 
        tree_print(tree._root, 0, outs);
        return outs;
    }

    AVL<T> &operator+=(const AVL<T> &rhs){
        tree_add(_root, rhs._root);  
        return *this; 
    }

private:
    tree_node<T>* _root;
};

#endif 
