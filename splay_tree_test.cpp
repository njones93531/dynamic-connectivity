#include "SplayTree.h"
#include <iostream>
#include <cstdlib>


using namespace std;

SplayTree* tree;

void simple_test_insert(int x, int y){
  cout << "Simple test insert";
  tree->insert(x, y);
  if(tree->root->val != y)
    cout << " failed. Expected val " << y << ", got val " << tree->root->val << endl;
  else if(tree->get_rank(tree->root) != x)
    cout << " failed. Expected rank " << x << ", got rank " << tree->get_rank(tree->root) << endl;
  else 
    cout << " passed." << endl;
}

void simple_test_rank(int x){
  cout << "Simple test rank";
  tree->find_rank(x);
  if(tree->get_rank(tree->root) != x)
    cout << " failed. Expected rank " << x << ", got rank " << tree->get_rank(tree->root) << endl;
  else 
    cout << " passed." << endl;
}

void simple_test_max(){
  cout << "Simple test max";
  tree->max(tree->root);
  if(tree->get_rank(tree->root) != tree->get_subtree_size(tree->root)-1)
    cout << " failed. Expected rank " << tree->root->subtree_size -1 << ", got rank " << tree->get_rank(tree->root) << endl;
  else 
    cout << " passed." << endl;
}

void simple_test_min(){
  cout << "Simple test min";
  tree->min(tree->root);
  if(tree->get_rank(tree->root) != 0)
    cout << " failed. Expected rank " << 0 << ", got rank " << tree->get_rank(tree->root) << endl;
  else 
    cout << " passed." << endl;
}

void simple_test_delete(int x){
  cout << "Simple test delete";
  int orig_size = tree->root->subtree_size;
  //tree->print_rank();
  tree->del(x);
  if(tree->root->subtree_size != orig_size - 1)
    cout << " failed. Expected size " << orig_size - 1 << ", got size " << tree->root->subtree_size << endl;
  else 
    cout << " passed." << endl;
}

void simple_test_delete_insert(int x){
  cout << "Simple test delete insert";
  int orig_size = tree->root->subtree_size;
  tree->find_rank(x);
  int val = tree->root->val;
  tree->del(tree->get_rank(tree->root));
  tree->insert(x, val);
  if(tree->root->subtree_size != orig_size)
    cout << " failed. Expected size " << orig_size << ", got size " << tree->root->subtree_size << endl;
  else 
    cout << " passed." << endl;
}



void simple_test_split_join(int x){
  cout << "Simple split join" << endl;
  SplayTree::Node * a;
  SplayTree::Node * b = tree->root;
  tree->split(x, tree->root, &a, &b);
  tree->root = tree->join(a, b);
  tree->print_val();
  cout << "Are they equal?" << endl;
}



int main()
{

    tree = new SplayTree;

    int sequence[10] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    int count = 0;
    for(int i : sequence){
      simple_test_insert(count++, i);
      cout << "Tree size: "<< tree->root->subtree_size << endl;
    }
    tree->print_val();

    for(int i = 0; i < 10; i++){
      int rank = rand() % 10;
      simple_test_rank(rank);
    }
    tree->print_val();


    for(int i = 0; i < 10; i++){
      int do_max = rand() % 2;
      if(do_max) simple_test_max();
      else simple_test_min();
    }
    tree->print_val();



    for(int i = 0; i < 3; i++){
      int rank = rand() % tree->root->subtree_size;
      simple_test_delete(rank);
    }
    tree->print_val();

    for(int i = 0; i < 10; i++){
      int rank = rand() % tree->root->subtree_size;
      simple_test_split_join(rank);
    }
    tree->print_val();

    for(int i = 0; i < 10; i++){
      int rank = rand() % tree->root->subtree_size;
      simple_test_delete_insert(rank);
    }
    tree->print_val();
   

    return 0;
}
