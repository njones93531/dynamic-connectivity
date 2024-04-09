#include <iostream>
#include "SplayTree.h"
using namespace std;
 
SplayTree::SplayTree() : root(nullptr) {}

//Assumes node with rank rank exists 
void SplayTree::find_rank(int rank){
  SplayTree::splay(no_splay_rank(root, rank));
}

//O(1) rank deprecated 
int SplayTree::get_rank(Node * e){
  if(e == NULL || e->left == NULL) return 0;
  return SplayTree::get_subtree_size(e->left);
}

int SplayTree::get_subtree_size(Node * e){
  if(e == NULL) return 0;
  return e->subtree_size;
}

//Assumes no duplicate keys
void SplayTree::insert(int rank, int val){
  root = SplayTree:: no_splay_insert(root, rank, val, NULL);
  SplayTree::find_rank(rank);
}

void SplayTree:: del(int rank){
  //After rank, e is at root
  SplayTree::find_rank(rank);
  SplayTree::Node * e = root;
  root = SplayTree::join(e->left, e->right);
  delete e;
}

void SplayTree:: print_val(){
  SplayTree:: print_subtree_val(root);
}

void SplayTree:: print_rank(){
  SplayTree:: print_subtree_rank(root);
}


//Assume e is the child of a non-null node
void SplayTree:: rotate_up(SplayTree::Node * e){
  SplayTree::Node * f = e->parent;
  //If e is left child
  if((e) == e->parent->left){
    //SplayTree::Node * A = e->left;
    SplayTree::Node * B = e->right;
    //SplayTree::Node * C = e->parent->right;
    e->right = f;
    e->parent = f->parent;
    if(B!=NULL) B->parent = f;
    f->parent = e;
    f->left = B;
  }
  else{
    //SplayTree::Node * A = f->left;
    SplayTree::Node * B = e->left;
    //SplayTree::Node * C = e->right;
    e->left = f;
    e->parent = f->parent;
    if(B!=NULL) B->parent = f;
    f->parent = e;
    f->right = B;
  }
    if(e->parent){
      if(e->parent->left == f) e->parent->left = e;
      else e->parent->right = e;
    }
    f->subtree_size = SplayTree::get_subtree_size(f->left) + SplayTree::get_subtree_size(f->right) + 1;
    e->subtree_size = SplayTree::get_subtree_size(e->left) + SplayTree::get_subtree_size(e->right) + 1;
}

//Postcondition: e is root
SplayTree::Node * SplayTree:: splay(SplayTree::Node * e){
  //If root, return
  if(e->parent == NULL){
    root = e;
    return e;
  }
  //If parent is root, rotate up
  if(e->parent->parent == NULL){
    SplayTree:: rotate_up(e);
    root = e;
    return e;
  }
  //If element is "in-line" with parent and grandparent, rotate parent, then e
  //If if e and e-> parent are both left or both not left children, they are "in line" 
 if((e == e->parent->left) == (e->parent == e->parent->parent->left)){
    SplayTree:: rotate_up(e->parent);
    SplayTree:: rotate_up(e);
  }
  else{
    SplayTree:: rotate_up(e);
    SplayTree:: rotate_up(e);
  }
  return SplayTree:: splay(e);
}

//Assumes node with rank *rank* exists
SplayTree::Node * SplayTree:: no_splay_rank(SplayTree::Node * subroot, int rank){
  if(rank == get_rank(subroot)) return subroot;
  if(rank < get_rank(subroot)) return SplayTree:: no_splay_rank(subroot->left, rank);
  return SplayTree:: no_splay_rank(subroot->right, rank - (1+get_subtree_size(subroot->left)));
}

SplayTree::Node * SplayTree:: no_splay_insert(SplayTree::Node * subroot, int rank, int val, Node* p){
  if(subroot==NULL) return new SplayTree::Node(val, p);
  if(rank < get_rank(subroot)){
    subroot->left = SplayTree:: no_splay_insert(subroot->left, rank, val, subroot);
  }else{
    subroot->right = SplayTree:: no_splay_insert(subroot->right, rank - (1+get_subtree_size(subroot->left)), val, subroot); 
  }
  subroot->subtree_size += 1;
  return subroot;
}

SplayTree::Node * SplayTree:: max(SplayTree::Node * subroot){
  if(subroot == NULL) return NULL;
  if(subroot->right == NULL) return subroot;
  return SplayTree:: splay(max(subroot->right));
}

SplayTree::Node * SplayTree:: min(SplayTree::Node * subroot){
  if(subroot == NULL) return NULL;
  if(subroot->left == NULL) return subroot;
  return SplayTree:: splay(min(subroot->left));
}

SplayTree::Node * SplayTree:: join(SplayTree::Node * left, SplayTree::Node * right){       
  left = SplayTree:: max(left);
  left->right = right;
  return left;
}

void SplayTree:: split(int rank, SplayTree::Node * subroot, SplayTree::Node ** a, SplayTree::Node ** b){       
  //Splay the element with rank *rank* to the root
  find_rank(rank);
  root->right->parent = NULL;
  *b = root->right; 
  root->right = NULL;
  *a = root;
}

void SplayTree:: print_subtree_rank(SplayTree::Node * subroot){
  if (subroot == NULL) return;
  SplayTree:: print_subtree_rank(subroot->left);
  cout << get_rank(subroot) << endl;
  SplayTree:: print_subtree_rank(subroot->right);
}

void SplayTree:: print_subtree_val(SplayTree::Node * subroot){
  if (subroot == NULL) return;
  SplayTree:: print_subtree_val(subroot->left);
  cout << subroot->val << endl;
  SplayTree:: print_subtree_val(subroot->right);
}


