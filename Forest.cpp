#include <iostream>
#include <vector>
#include "SplayTree.h"
#include "Forest.h"
using namespace std;

//Trees will only be maintained as euler tours
//vector<SplayTree::SplayTree> trees;    

//SplayTree::Nodes appear >=1 times in a Euler tour, keep a pointer
//to first and last occurrence
//SplayTree::Nodes can be referenced by their index in this->vector
//vector<pair<SplayTree::Node*, SplayTree::Node*>> this->nodes;


//Makes a new tree with a single node 
void Forest::make_node(){
  //New node in its own tree
  SplayTree::Node * new_node = this->trees->insert(0, this->nodes.size(), NULL);
  
  //Add node pointers to this->nodes
  this->nodes.push_back(make_pair(new_node, new_node));
}

//Because this->is a tree, assert !connected first
void Forest::add_edge(int a, int b){
  if(connected(a, b)){
    cerr << "Failed to add edge. SplayTree::Node " << a << " and node " << b
         << " are already connected.\n";
    return; 
  }

  //Split tree where new subsequence should be inserted
  int rank = this->trees->get_local_rank(nodes[a].second);
  SplayTree::Node * L = NULL;
  SplayTree::Node * R = NULL;
  this->trees->split(rank, this->nodes[a].second, &L, &R);

  //Insertion is only easy when B is the root of its euler tour
  reroot(b);

  //Append subsequence, then extra A, then rest of original tree
  SplayTree::Node * root = this->trees->join(L, this->trees->splay(this->nodes[b].first));
  SplayTree::Node * extra_A = this->trees->insert(0, a, NULL);
  this->nodes[a].second = extra_A;
  root = this->trees->join(root, extra_A);
  root = this->trees->join(root, R);
}

//Assumes L and R will not be empty 
void Forest::splice(int a, SplayTree::Node ** L, SplayTree::Node ** A, SplayTree::Node ** R){
  SplayTree::Node * root = this->trees->splay(this->nodes[a].first);
  int L_max_rank = this->trees->get_local_rank(this->nodes[a].first) - 1;
  this->trees->split(L_max_rank, root, L, A);

  root = this->trees->splay(this->nodes[a].second);
  int A_max_rank = this->trees->get_local_rank(this->nodes[a].second);
  this->trees->split(A_max_rank, root, A, R);

}

void Forest::unsplice(SplayTree::Node * L, SplayTree::Node * M, SplayTree::Node * R){
  //Rootify
  if(L) L = this->trees->splay(L);
  if(M) M = this->trees->splay(M);
  if(R) R = this->trees->splay(R);

  //Join
  SplayTree::Node * root = this->trees->join(L, M);
  root = this->trees->join(root, R);
}

//Alter the euler tour such that the tour begins at a
SplayTree::Node * Forest::reroot(int a){
  //If a is already the start of the tour, return
  SplayTree::Node * root = this->trees->splay(this->nodes[a].first);
  root = this->trees->min(root);
  if(root->val == a) return root;

  //Split tree into L, A, and R
  SplayTree::Node *L, *A, *R;
  splice(a, &L, &A, &R);

  //Right branch needs A at end and remove old root from start
  R = this->trees->insert(this->trees->get_subtree_size(R), a, R);
  SplayTree::Node * to_delete = this->trees->min(R);
  L = this->trees->max(L);
  int val = to_delete->val; 
  if(this->nodes[val].second == to_delete) nodes[val].second = L; 
  R = this->trees->del(to_delete); 

  //Join this->trees
  if(A) A = this->trees->splay(A);
  if(L) L = this->trees->splay(L);
  if(R) R = this->trees->splay(R);
  root = this->trees->join(A, L);
  root = this->trees->join(root, R);

  //Fix a pointers
  root = this->trees->min(root);
  this->nodes[a].first = root;
  root = this->trees->max(root);
  this->nodes[a].second = root;
  return root;
}

//Assert connected
void Forest::delete_edge(int a, int b){
  if(!connected(a, b)){
    cerr << "Failed to remove edge. SplayTree::Node " << a << " and node " << b
         << " are not connected.\n";
    return; 
  }

  //Splicing b out becomes way easier if b is not the root 
  reroot(a);

  //Splice out b
  SplayTree::Node *L, *B, *R;
  splice(b, &L, &B, &R);
    
  //Remove pred of b.first
  L = this->trees->max(L);
  int val = L->val; 
  R = this->trees->min(R);
  //Maintain val first pointer
  if(this->nodes[val].first == L) nodes[val].first = R; 
  L = this->trees->del(L);

  //Join this->trees not containing b
  this->trees->join(L, R);
}

bool Forest::connected(int a, int b){
  SplayTree::Node * A = this->trees->splay(this->nodes[a].first);
  SplayTree::Node * B = this->trees->splay(this->nodes[b].first);
  //If A and B are both roots, they are not in the same tree
  return !(A->parent == NULL && B->parent == NULL); 
}
    
