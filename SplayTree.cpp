#include <iostream>
#include "SplayTree.h"
using namespace SplayTree;
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
 
SplayTree() : root(nullptr) {}

void find(int key){
  root = splay(no_splay_find(root, key));
}

//Assumes no duplicate keys
void insert(int key, int val){
  root = no_splay_insert(root, key, val);
  find(key);
}

void del(int key){
  //After find, e is at root
  find(key);
  Node * e = root;
  root = join(e->left, e->right);
  delete e;
}

void print_val(){
  print_subtree_val(root);
}

void print_key(){
  print_subtree_key(root);
}
     
//Assume e is the child of a non-null node
void rotate_up(Node * e){
  //If e is left child
  if(e->key < e->parent->key){
    Node * orphan = e->right;
    e->right = e->parent;
    e->parent = e->parent->parent;
    e->right->left = orphan;
  }
  else{
    Node * orphan = e->left;
    e->left = e->parent;
    e->parent = e->parent->parent;
    e->left->right = orphan;
  }
}

Node * splay(Node * e){
  //If root, return
  if(e->parent == NULL) return e;
  //If parent is root, rotate up
  if(e->parent->parent == NULL){
    rotate_up(e);
    return e;
  }
  //If element is "in-line" with parent and grandparent, rotate parent, then e
  //If a and b have same sign, then "in-line" = True
  if((e->key - e->parent->key < 0) == (e->parent->key - e->parent->parent->key < 0)){
    rotate_up(e->parent);
    rotate_up(e);
  }
  else{
    rotate_up(e);
    rotate_up(e);
  }
  return splay(e);
}

//Return e if it exists, otherwise return NULL
Node * no_splay_find(Node * subroot, int key){
  if(subroot==NULL || key == subroot->key) return subroot;
  if(key < subroot->key) return no_splay_find(subroot->left, key);
  return no_splay_find(subroot->right, key);
}

Node * no_splay_insert(Node * subroot, int key, int val){
  if(subroot==NULL) return new Node(key, val);
  if(key < subroot->key){
    subroot->left = no_splay_insert(subroot->left, key, val);
    subroot->left->parent = subroot;
  }else{
    subroot->right = no_splay_insert(subroot->right, key, val); 
    subroot->right->parent = subroot;
  }
  return subroot;
}

Node * max(Node * subroot){
  if(subroot == NULL) return NULL;
  if(subroot->right == NULL) return subroot;
  return splay(max(subroot->right));
}

Node * min(Node * subroot){
  if(subroot == NULL) return NULL;
  if(subroot->left == NULL) return subroot;
  return splay(min(subroot->left));
}

Node * join(Node * left, Node * right){       
  left = max(left);
  left->right = right;
  return left;
}

void print_subtree_key(Node * subroot){
  if (subroot == NULL) return;
  print_subtree_key(subroot->left);
  cout << subroot->key << endl;
  print_subtree_key(subroot->right);
}

void print_subtree_val(Node * subroot){
  if (subroot == NULL) return;
  print_subtree_val(subroot->left);
  cout << subroot->val << endl;
  print_subtree_val(subroot->right);
}



