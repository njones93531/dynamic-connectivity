#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H
#include <iostream>
#include <vector>
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
    SplayTree();
    ~SplayTree() {
      for(SplayTree::Node* a : SplayTree::nodes){
        if(a) delete a;
      }
    delete &nodes;
}

     
    Node * find_rank(int rank, Node * root);
    
    int get_local_rank(Node * a);

    int get_subtree_size(Node * e);

    //Assumes no duplicate ranks
    Node * insert(int rank, int val, Node * root);

    Node * del(int rank, Node * root);
    
    Node * del(Node * e);

    void print_val(Node * root);
    
    void print_rank(Node * root);
    
    Node * max(Node * subroot);

    Node * min(Node * subroot);

    //Assumes trees disjoint
    Node * join(Node * left, Node * right);
    
    void split(int rank, Node * root, Node ** a, Node **b);
    
    Node * splay(Node * e);

    void delete_tree(Node * root);
  
  private:
    vector<Node *> nodes;

    //Assume e is the child of a non-null node
    void rotate_up(Node * e);

    //Return e if it exists, otherwise return NULL
    Node * no_splay_rank(Node * subroot, int rank);

    Node * no_splay_insert(Node * subroot, int rank, int val, Node * p);

    void print_subtree_rank(Node * subroot);

    void print_subtree_val(Node * subroot);

};
#endif
