#include <iostream>
#include <climits>
#include "SplayTree.h"
using namespace std;
 
SplayTree::SplayTree(){}
//Assumes node with rank rank exists 
SplayTree::Node * SplayTree::find_rank(int rank, SplayTree::Node * root){
  return SplayTree::splay(no_splay_rank(root, rank));
}

int SplayTree::get_local_rank(SplayTree::Node * e){
  if(e == NULL || e->left == NULL) return 0;
  return SplayTree::get_subtree_size(e->left);
}

int SplayTree::get_subtree_size(SplayTree::Node * e){
  if(e == NULL) return 0;
  return e->subtree_size;
}

//Assumes no duplicate keys
SplayTree::Node * SplayTree::insert(int rank, int val, SplayTree::Node * root){
  root = SplayTree:: no_splay_insert(root, rank, val, NULL);
  return SplayTree::find_rank(rank, root);
}

SplayTree::Node * SplayTree:: del(int rank, SplayTree::Node * root){
  //After rank, e is at root
  root = SplayTree::find_rank(rank, root);
  SplayTree::Node * e = root;
  SplayTree::Node * A = e->left;
  SplayTree::Node * B = e->right;
  if(A) A->parent = NULL;
  if(B) B->parent = NULL;
  e->left = NULL;
  e->right = NULL;
  delete e;
  return SplayTree::join(A, B);
}

SplayTree::Node * SplayTree:: del(SplayTree::Node * e){
  splay(e);
  SplayTree::Node * A = e->left;
  SplayTree::Node * B = e->right;
  if(A) A->parent = NULL;
  if(B) B->parent = NULL;
  e->left = NULL;
  e->right = NULL;
  delete e;
  return SplayTree::join(A, B);
}


void SplayTree:: print_val(SplayTree::Node * root){
  SplayTree:: print_subtree_val(root);
}

void SplayTree:: print_rank(SplayTree::Node * root){
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
    return e;
  }
  //If parent is root, rotate up
  if(e->parent->parent == NULL){
    SplayTree:: rotate_up(e);
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
  if(rank == get_local_rank(subroot)) return subroot;
  if(rank < get_local_rank(subroot)) return SplayTree:: no_splay_rank(subroot->left, rank);
  return SplayTree:: no_splay_rank(subroot->right, rank - (1+get_subtree_size(subroot->left)));
}

SplayTree::Node * SplayTree:: no_splay_insert(SplayTree::Node * subroot, int rank, int val, SplayTree::Node* p){
  if(subroot==NULL){
    SplayTree::Node * new_node = new SplayTree::Node(val, p);
    SplayTree::nodes.push_back(new_node);
    return new_node;
  }
  if(rank <= get_local_rank(subroot)){
    subroot->left = SplayTree:: no_splay_insert(subroot->left, rank, val, subroot);
  }else{
    subroot->right = SplayTree:: no_splay_insert(subroot->right, rank - (1+get_subtree_size(subroot->left)), val, subroot); 
  }
  subroot->subtree_size += 1;
  return subroot;
}

SplayTree::Node * SplayTree:: max(SplayTree::Node * subroot){
  return SplayTree::splay(no_splay_rank(subroot, get_subtree_size(subroot)-1));
}

SplayTree::Node * SplayTree:: min(SplayTree::Node * subroot){
  return SplayTree::splay(no_splay_rank(subroot, 0));
}

SplayTree::Node * SplayTree:: join(SplayTree::Node * left, SplayTree::Node * right){
  if(left == NULL) return right;
  if(right == NULL) return left;
  left->parent = NULL;
  right->parent = NULL;
  left = SplayTree:: max(left);
  left->right = right;
  right->parent = left;
  left->subtree_size += get_subtree_size(left->right);
  return left;
}

void SplayTree:: split(int rank, SplayTree::Node * root, SplayTree::Node ** a, SplayTree::Node ** b){
  if(rank < 0){
    *b = root;
    *a = NULL;
    return;
  }
  if(rank >= get_subtree_size(root)){
    *a = root;
    *b = NULL;
    return;
  }
  //Splay the element with rank *rank* to the root
  root = find_rank(rank, root);
  if(root->right) root->right->parent = NULL;
  SplayTree::Node * b_ret = root->right; 
  root->right = NULL;
  SplayTree::Node * a_ret = root;
  if(a_ret) (a_ret)->subtree_size -= get_subtree_size(b_ret);
  *a = a_ret;
  *b = b_ret;
}

void SplayTree:: print_subtree_rank(SplayTree::Node * subroot){
  if (subroot == NULL) return;
  SplayTree:: print_subtree_rank(subroot->left);
  cout << get_local_rank(subroot) << ' ';
  SplayTree:: print_subtree_rank(subroot->right);
  if(subroot->parent == NULL) cout << endl;
}

void SplayTree:: print_subtree_val(SplayTree::Node * subroot){
  if (subroot == NULL) return;
  SplayTree:: print_subtree_val(subroot->left);
  cout << subroot->val << ' ';
  SplayTree:: print_subtree_val(subroot->right);
  if(subroot->parent == NULL) cout << endl;
}

void SplayTree::delete_tree(SplayTree::Node * root){
  if(root == NULL) return; 
  delete_tree(root->left);
  delete_tree(root->right);
  delete root;
}


