#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H
#include <iostream>
using namespace std;
class SplayTree
{
  public:
    typedef struct Node {
      int val;
      int subtree_size;
      struct Node* left;
      struct Node* right;
      struct Node* parent;
      Node(int val, Node * p){
        this->left = NULL;
        this->right = NULL;
        this->parent = p;
        this->val = val;
        this->subtree_size = 1;
      }
    } Node;
    Node * root; 
    SplayTree();
     
    void find_rank(int rank);
    
    int get_rank(Node * a);

    int get_subtree_size(Node * e);

    //Assumes no duplicate ranks
    void insert(int rank, int val);

    void del(int rank);

    void print_val();
    
    void print_rank();

    //Assumes trees disjoint
    Node * join(Node * left, Node * right);
    
    void split(int rank, Node * root, Node ** a, Node **b);
  
  private:
    
    //Assume e is the child of a non-null node
    void rotate_up(Node * e);

    Node * splay(Node * e);

    //Return e if it exists, otherwise return NULL
    Node * no_splay_rank(Node * subroot, int rank);

    Node * no_splay_insert(Node * subroot, int rank, int val, Node * p);

    Node * max(Node * subroot);

    Node * min(Node * subroot);

    void print_subtree_rank(Node * subroot);

    void print_subtree_val(Node * subroot);

};
#endif
