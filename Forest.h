#ifndef FOREST_H
#define FOREST_H
#include <iostream>
#include <vector>
#include "SplayTree.h"
using namespace std;
class Forest
{
  public:
    typedef struct Edge {
      int weight;
      int a;
      int b;
      Node(int a, int b, int weight){
        this->a = a;
        this->b = b;
        this->weight = weight;
      }
    } Edge;
    
    vector<SplayTree::Node *> vectors;
    vector<SplayTree::SplayTree *> trees;
    
    //Assumes edge is valid
    void insert_edge(int a, int b);

    //Assumes edge exists
    void delete_edge(int a, int b);

    void connected(int a, int b);    
 
  
  private:
    
};
#endif
