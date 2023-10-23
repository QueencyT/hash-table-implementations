#ifndef AVL_FUNCTIONS_H 
#define AVL_FUNCTIONS_H 

#include <iostream>
#include <iomanip>
#include <math.h>

#include "../../includes/avl/tree_node.h"

using namespace std; 


//when it is left heavy aka when 2 (pos 2)
template<typename T> 
void rotate_right(tree_node<T>*& root){
    if(root){ 
        tree_node<T>* temp = root; //3
        root = root->_left;  // 2
        temp->_left = root->_right;  
        root->_right = temp;
        

        root->_right->update_height(); 
        root->update_height(); 
    }
    //should be fine?
}

//when it is right heavy aka when -2 (neg 2)
template<typename T> 
void rotate_left(tree_node<T>*& root){
    if(root){
        tree_node<T>* temp = root; 
        root = root->_right; 
        temp->_right = root->_left; 
        root->_left = temp; 

        root->_left->update_height(); 
        root->update_height(); 
    }
} //needs further testing 

//when it is right heavy and leaning left
template<typename T> 
void rotate_mirror_left(tree_node<T>*& root){
    if(root){
        rotate_right(root->_right); 
        rotate_left(root);  
    } //working so far
}

//when it is left heavy and leaning right
template<typename T> 
void rotate_mirror_right(tree_node<T>*& root){
    if(root){
        rotate_left(root->_left);
        rotate_right(root);
    }//should work
}

template<typename T>
void rotate(tree_node<T>*& root){
    //root->update_height();
    if(root){
        if(root->balance_factor() == 2 && root->_left && root->_left->balance_factor() == -1){//leaning heavy left but also right
           // cout<<"leaning heavy left but also right\n";
            //cout<<"in order before rotate: "<<in_order_string(root)<<endl; 
            rotate_mirror_right(root); 
           // cout<<"in order after rotate: "<<in_order_string(root)<<endl; 
        }
        else if(root->balance_factor() == -2 && root->_right && root->_right->balance_factor() == 1){//leaning heavu right but also left
            //cout<<"leaning heavy right but also left\n";
            //cout<<"in order before rotate: "<<in_order_string(root)<<endl;
            rotate_mirror_left(root); 
            //cout<<"in order after rotate: "<<in_order_string(root)<<endl;
        }
        else if(root->balance_factor() == 2){ //leaning left 
           // cout<<"leaning left\n";
            //cout<<"in order before rotate: "<<in_order_string(root)<<endl;
            rotate_right(root); 
            //cout<<"in order after rotate: "<<in_order_string(root)<<endl; 
        }
        else if(root->balance_factor() == -2){//leaning right
           // cout<<"leaning right\n";
           // cout<<"in order before rotate: "<<in_order_string(root)<<endl;
            rotate_left(root); 
            //cout<<"in order after rotate: "<<in_order_string(root)<<endl; 
        }
    }
   
}


template <typename T>
void tree_insert(tree_node<T>* &root, const T& insert_me){

    if(root == NULL){
        root = new tree_node<T>(insert_me); //should be null left and right //shouldn't matter that it's null since we are inserting to null space 
    } 
    else if(root->_item == insert_me){
        return; 
    }
    else if(insert_me < root->_item){
        tree_insert(root->_left, insert_me); 
    }
    else{
        tree_insert(root->_right, insert_me); 
    }  
    root->update_height(); 
    rotate(root);
}


template <typename T> //erase target from the tree
bool tree_erase(tree_node<T>*& root, const T& target){ 
    bool deleted = false; 
     
    if(!root){
        return deleted; 
    }
    //left subtree but right is null 
    if(root->_item == target){
        
        if(root->_left == NULL){ //in the case where there is no left subtree 
            tree_node<T>* rightNode = root->_right; 
            delete root; 
            root = rightNode; 
        }
        else{ //in the case where there is a left subtree //leftmost of right subtree
            tree_remove_max(root->_left, root->_item);  
        }
        deleted = true;  
    }
    else if(target < root->_item){
        deleted = tree_erase(root->_left, target); 
    }
    else{
        deleted = tree_erase(root->_right, target); 
    }

    if(root) //rotate when we erase
        rotate(root); 
    if(root)
        root->update_height(); 
    return(deleted); //to see if something was deleted or not
}


template <typename T>
tree_node<T>* tree_search(tree_node<T>* root, const T& target){
    tree_node<T>* found = NULL; 

    if(root == NULL){//last node and still not found 
        return NULL; 
    }

    if(root->_item == target){
        return root; //returning copy of root ptr
    }
    //at this point root is not equal to target so its either less than or more than root 
    if(target < root->_item){
        found = tree_search(root->_left, target); 
    }
    else{
        found = tree_search(root->_right, target); 
    }

    return found; 
    //what if the case that target not in tree
}

template <typename T>
bool tree_search(tree_node<T>* root, const T& target, tree_node<T>* &found_ptr){
    found_ptr = tree_search(root, target); 
    return (found_ptr != NULL); //we found a pointer return true
}
//bool is for found not found? 

//let's do this first 
template<typename T>
void tree_print(tree_node<T>* root, int depth=0, ostream& outs=cout){ //what is depth? //what if emoty 
    if(root){
        tree_print(root->_right, depth + 1, outs); 
        outs<<setw(4 * depth)<<root->_item<<endl; 
        tree_print(root->_left, depth + 1, outs);
    }
}

template<typename T> //prints detailes info about each node
void tree_print_debug(tree_node<T>* root, int depth=0, ostream& outs=cout){
    //print out height and stuff 
    if(!root)
        return; 

    tree_print_debug(root->_right, depth + 1, outs); 
    outs<<setw(4 * depth)<<"[H:"<<root->_height<<": B:"<<root->balance_factor()<<"]"<<root->_item<<endl; 
    tree_print_debug(root->_left, depth + 1, outs); 
    //ignore for now 
}
//hmm save for later, need to ask what is "detailed" info

template <typename T> //clear the tree
void tree_clear(tree_node<T>* &root){ //have to go to end and delete? 
    if(root){
        tree_clear(root->_left); //if root->left ends up being null won't enter if statement and will automatically return
        tree_clear(root->_right); //if root->right ends up being null it wont enter if statement as well and will auto return here 
        delete root; //this means we're at a "last node" and so delete
        root = NULL; 
    }
    //if problems look here --> maybe height set to -1
}//must test and check 
//you have to remember that root and what it means changes with each call

//erase a specific value from tree

template <typename T> //erase rightmost node from the tree -> max_value //purpose it to remove the rightmost node and put its val into maxVal
void tree_remove_max(tree_node<T>* &root, T& max_value){
    if(root == NULL){
        return; //empty so cannot remove 
    } 
    //want to remove max so going right
    if(root->_right == NULL){ 
        max_value = root->_item; 
        if(root->_left != NULL){ //if there is a left child
            tree_node<T>* leftNode = root->_left; 
            delete root; 
            root = leftNode; 
        }else{ //else delete root immediately since has no left child and no right child 
            delete root; 
            root = NULL;
            return; 
        }
    }
    tree_remove_max(root->_right, max_value);  //Height? must ask professor
}

template <typename T> //print in_order
void in_order(tree_node<T>* root,ostream& outs=cout){
    if(root){
        in_order(root->_left); 
        outs<<root->_item<<endl; 
        in_order(root->_right); 
    }
}

template <typename T> //print pre_order //root left right 
void  pre_order(tree_node<T>* root,ostream& outs=cout){ //made test function, is working so far 
    //better to do if(root) and NOT if(!root){return;}
    if(root){ //while root is not empty 
        outs<<root->_item<<endl; //for now like this, later use actual overload operator
        pre_order(root->_left, outs); 
        pre_order(root->_right, outs); //i think should work hmm
    } 
}

template <typename T> //print post_order must test  //what if one node case
void  post_order(tree_node<T>* root, ostream& outs=cout){

    if(root){ //root == NULL return , if leaf node return
        post_order(root->_left, outs); //these are like continue statements until we reach  root is null
        post_order(root->_right, outs); //want to go as most left as possible then as most right as possible
        outs<<root->_item<<endl; 
    }
}

template <typename T> //string in_order //what if empty
string in_order_string(tree_node<T>* root){ 
    //left, middle, right 
    if(!root){
        return ""; 
    } 
    string inOrderString = ""; 
    string result;

    inOrderString += in_order_string(root->_left); 
    inOrderString += "[" + to_string(root->_item) + "]"; 
    inOrderString += in_order_string(root->_right);  

    return inOrderString; 
    //string of our in order result 
}

//ctr click function go to f def

template <typename T> //string pre_order
string pre_order_string(tree_node<T>* root){
    if(!root){
        return ""; 
    } 
    string preOrderString = "[" + to_string(root->_item) + "]"; 
    preOrderString += pre_order_string(root->_left);
    preOrderString += pre_order_string(root->_right); 
    
    return preOrderString; 
    //string of our pre order result 
}

template <typename T> //string post_order
string post_order_string(tree_node<T>* root){
    if(!root){
        return ""; 
    }
    string postOrder = ""; 
    postOrder += post_order_string(root->_left); 
    postOrder += post_order_string(root->_right); 
    postOrder += "[" + to_string(root->_item) + "]";  

    return postOrder; 
    //string of our post order result "8,9,10,11"; 
}


template <typename T> //return copy of tree pointed to by root
tree_node<T>* tree_copy(tree_node<T>* root){ //making copies of empty??
    //copy left, then copy middle, then copy right? 
    if(!root){ //root == null
        return NULL;
    }

    tree_node<T>* copyRoot = new tree_node<T>(root->_item, NULL, NULL); 
    copyRoot->_left = tree_copy(root->_left); 
    copyRoot->_right = tree_copy(root->_right); 
    copyRoot->update_height();
    return copyRoot; 
}

template <typename T> //Add tree src to dest //add? 
void tree_add(tree_node<T>* & dest, const tree_node<T>* src){ ///so far working
    //assuming dest is pretty well sorted?? hm
    
    if(dest == NULL && src){ //src != null, but dest == null
        tree_add(dest, src->_left); 
        tree_insert(dest, src->_item); 
        tree_add(dest, src->_right); 
        return; 
    } //src == null don't want to do anything since there's nothing to append
    
   if(dest && src){
        tree_add(dest->_left, src->_left); 
        tree_insert(dest, src->_item);  
        tree_add(dest->_right, src->_right); 
    } 
}
//ok try with one nodes first


//sort an array of 1,000,000 elements 
//only access 10 items at a time from a file
//merge sort
template <typename T> // sorted array -> tree
tree_node<T>* tree_from_sorted_list(const T* a, int size){//not snug array Im guessing 
    tree_node<T>* ourRoot = NULL;
    for(int i = 0; i < size; i++){
        tree_insert(ourRoot, a[i]); 
    }
    return ourRoot;  
} //?

//0 1 2 3 4 5?
template <typename T> //sorted array of ints -> tree
tree_node<T>* tree_from_sorted_list(const T* a){ //snug array Im guessing? 
    int size = 0; 
    while(a[size] != -1){
        size++;
    }
    tree_node<T>* ourRoot = tree_from_sorted_list(a, size); //cmake error 2 and 3 //idk putting 10 for now b/c I have no idea what goes here 
    return ourRoot; 
} //? 

#endif 