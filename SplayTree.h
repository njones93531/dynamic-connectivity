#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H
#include <iostream>
using namespace std;
class SplayTree
{
  public:
    typedef struct Node {
      int val;
      int key;
      struct Node* left;
      struct Node* right;
      struct Node* parent;
      Node(int key, int val){
        this->left = NULL;
        this->right = NULL;
        this->val = val;
        this->key = key;
      }
    } Node;
    Node * root; 
    SplayTree();
    
    
    void find(int key);

    //Assumes no duplicate keys
    void insert(int key, int val);

    void del(int key);

    void print_val();
    
    void print_key();
 
  
  private:
    
    //Assume e is the child of a non-null node
    void rotate_up(Node * e);

    Node * splay(Node * e);

    //Return e if it exists, otherwise return NULL
    Node * no_splay_find(Node * subroot, int key);

    Node * no_splay_insert(Node * subroot, int key, int val);

    Node * max(Node * subroot);

    Node * min(Node * subroot);

    Node * join(Node * left, Node * right);

    void print_subtree_key(Node * subroot);

    void print_subtree_val(Node * subroot);

};
#endif
