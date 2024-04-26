#ifndef FOREST_H
#define FOREST_H
#include <iostream>
#include <vector>
#include "SplayTree.h"
using namespace std;
class Forest
{
  public:
    //Trees will only be maintained as euler tours
    SplayTree * trees;
    //Nodes appear >= 1 times in a tour; keep pointers to
    //first and last occurrence
    //Nodes can be referenced by their index in this vector
    vector<pair<SplayTree::Node*, SplayTree::Node*>> nodes;
    Forest(){
      trees = new SplayTree;
    }
    ~Forest(){
      delete trees;
    }
    //Makes a new tree with a single node 
    void make_node();
    //Because this is a tree, assert !connected first
    void add_edge(int a, int b);
    //Assumes edge exists
    void delete_edge(int a, int b);
    //Splay a and b; if both have no parent, connected 
    bool connected(int a, int b);    
    //Restructure the euler tour to start at a
    SplayTree::Node * reroot(int a);
    //Splice b out of a euler tour tree
    //Assumes b is not the start of the tour
    void splice(int b, SplayTree::Node ** L, SplayTree::Node ** B, SplayTree::Node ** R);
    //Join but 3 for convenience
    void unsplice(SplayTree::Node * L, SplayTree::Node * B, SplayTree::Node * R);
  private:
    
};
#endif
