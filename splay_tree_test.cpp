#include "SplayTree.h"
#include <iostream>
#include <cstdlib>


using namespace std;

SplayTree* tree;
SplayTree::Node * root;

void simple_test_insert(int x, int y){
  cout << "Simple test insert";
  root = tree->insert(x, y, root);
  if(root->val != y)
    cout << " failed. Expected val " << y << ", got val " << root->val << endl;
  else if(tree->get_local_rank(root) != x)
    cout << " failed. Expected rank " << x << ", got rank " << tree->get_local_rank(root) << endl;
  else 
    cout << " passed." << endl;
}

void simple_test_rank(int x){
  cout << "Simple test rank";
  root = tree->find_rank(x, root);
  if(tree->get_local_rank(root) != x)
    cout << " failed. Expected rank " << x << ", got rank " << tree->get_local_rank(root) << endl;
  else 
    cout << " passed." << endl;
}

void simple_test_max(){
  cout << "Simple test max";
  root = tree->max(root);
  if(tree->get_local_rank(root) != tree->get_subtree_size(root)-1)
    cout << " failed. Expected rank " << root->subtree_size -1 << ", got rank " << tree->get_local_rank(root) << endl;
  else 
    cout << " passed." << endl;
}

void simple_test_min(){
  cout << "Simple test min";
  root = tree->min(root);
  if(tree->get_local_rank(root) != 0)
    cout << " failed. Expected rank " << 0 << ", got rank " << tree->get_local_rank(root) << endl;
  else 
    cout << " passed." << endl;
}

void simple_test_delete(int x){
  cout << "Simple test delete";
  int orig_size = root->subtree_size;
  //tree->print_rank();
  root = tree->del(x, root);
  if(root->subtree_size != orig_size - 1)
    cout << " failed. Expected size " << orig_size - 1 << ", got size " << root->subtree_size << endl;
  else 
    cout << " passed." << endl;
}

void simple_test_delete_insert(int x){
  cout << "Simple test delete insert";
  int orig_size = root->subtree_size;
  root = tree->find_rank(x, root);
  int val = root->val;
  root = tree->del(tree->get_local_rank(root), root);
  root = tree->insert(x, val, root);
  if(root->subtree_size != orig_size)
    cout << " failed. Expected size " << orig_size << ", got size " << root->subtree_size << endl;
  else 
    cout << " passed." << endl;
}



void simple_test_split_join(int x){
  cout << "Simple split join" << endl;
  SplayTree::Node * a;
  SplayTree::Node * b = root;
  tree->split(x, root, &a, &b);
  root = tree->join(a, b);
  tree->print_val(root);
  cout << "Are they equal?" << endl;
}



int main()
{

    tree = new SplayTree;
    root = NULL;

    int sequence[10] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    int count = 0;
    for(int i : sequence){
      simple_test_insert(count++, i);
      cout << "Tree size: "<< root->subtree_size << endl;
    }
    tree->print_val(root);

    for(int i = 0; i < 10; i++){
      int rank = rand() % 10;
      simple_test_rank(rank);
    }
    tree->print_val(root);


    for(int i = 0; i < 10; i++){
      int do_max = rand() % 2;
      if(do_max) simple_test_max();
      else simple_test_min();
    }
    tree->print_val(root);



    for(int i = 0; i < 3; i++){
      int rank = rand() % root->subtree_size;
      simple_test_delete(rank);
    }
    tree->print_val(root);

    for(int i = 0; i < 10; i++){
      int rank = rand() % root->subtree_size;
      simple_test_split_join(rank);
    }
    tree->print_val(root);

    for(int i = 0; i < 10; i++){
      int rank = rand() % root->subtree_size;
      simple_test_delete_insert(rank);
    }
    tree->print_val(root);

    tree->delete_tree(root);
   

    return 0;
}
