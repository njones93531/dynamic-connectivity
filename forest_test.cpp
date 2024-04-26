#include "Forest.h"
#include <iostream>
#include <cstdlib>


using namespace std;

Forest * F;
int test;

void print_val(int a){
  F->trees->print_val(F->trees->splay(F->nodes[a].first));
}

bool check_node_error(){
  bool error = 0;
  for(int i = 0; i < (int)F->nodes.size(); i++){
    if(F->nodes[i].first->val != i){
      cout << "First node wrong for value " << i << endl;
      error = 1;
    }
    if(F->nodes[i].second->val != i){ 
      cout << "Second node wrong for value " << i << endl;
      error = 1;
    }
  }
  return error;
}


void compare(string test_name, int expected, int recieved){
  bool error = check_node_error();
  cout << test++ << ".Simple test " << test_name;
  if(expected != recieved || error)
    cout << " failed. Expected " << expected << ", got " << recieved << endl;
  else 
    cout << " passed." << endl;
}

void simple_test_make_node(){
  string test_name = "make node";
  int expected = F->nodes.size() + 1;
  F->make_node();
  compare(test_name, expected, F->nodes.size());
}

void simple_test_splice(int a){
  //A is the only member of its tree
  if(F->nodes[a].first->parent == F->nodes[a].first->left){
    cout << "Cannot splice " << a << "; Single elements cannot be spliced." << endl;
    return;
  }
  SplayTree::Node *L, *A, *R;
  cout << "a = " << a << endl;
  cout << "Before: ";
  print_val(a);
  F->splice(a, &L, &A, &R);
  cout << "L: ";
  F->trees->print_val(L);
  cout << "A: ";
  F->trees->print_val(A);
  cout << "R: ";
  F->trees->print_val(R);
  F->unsplice(L, A, R);
  cout << "After: ";
  print_val(a);
  string test_string = "splice";
  compare(test_string, 1, 1);
}

void simple_test_add_edge(int a, int b){
  cout << a << ' ' << b << endl;
  cout << "Before A:" << endl;
  print_val(a);
  cout << "Before B:" << endl;
  print_val(b);
  string test_name = "add edge";
  int expected = 1;
  F->add_edge(a, b);
  cout << "After A:" << endl;
  print_val(a);
  cout << "After B:" << endl;
  print_val(b);

  compare(test_name, expected, F->connected(a, b));
}

void simple_test_reroot_size(int a){
  string test_name = "reroot size";
  int expected = F->trees->get_local_rank(F->trees->max(F->trees->splay((F->nodes[a]).first)));
  F->reroot(a);
  int recieved = F->trees->get_local_rank(F->trees->max(F->trees->splay((F->nodes[a]).first)));

  compare(test_name, expected, recieved);
}

void simple_test_reroot_minmax(int a){
  int expected = a;
  F->reroot(a);
  int max = F->trees->max(F->trees->splay((F->nodes[a]).first))->val;
  int min = F->trees->min(F->trees->splay((F->nodes[a]).first))->val;

  string test_name = "reroot min";
  compare(test_name, expected, min);
  test_name = "reroot max";
  compare(test_name, expected, max);
}

void simple_test_delete_edge(int a, int b){
  cout << "Before A:" << endl;
  print_val(a);
  cout << "Before B:" << endl;
  print_val(b);
  string test_name = "delete edge";
  int expected = 0;
  F->delete_edge(a, b);
  compare(test_name, expected, F->connected(a, b));
  cout << "After A:" << endl;
  print_val(a);
  cout << "After B:" << endl;
  print_val(b);

}

void simple_test_not_connected(int a, int b){
  string test_name = "not connected";
  int expected = 0;
  compare(test_name, expected, F->connected(a, b));
}

int main()
{
    test = 0; 
    F = new Forest;

    for(int i = 0; i < 10; i++){
      simple_test_make_node();
    }

    for(int i = 0; i < 10; i++){
      int a = rand() % 10;
      int b = (a + (rand() % 9 + 1)) % 10;
      simple_test_not_connected(a, b);
    }


    for(int i = 0; i < 10; i++){
      int a = rand() % 10;
      int b = (a + (rand() % 9 + 1)) % 10;
      simple_test_add_edge(a, b);
    }

    for(int i = 0; i < 10; i++){
      simple_test_splice(i);
    }



    for(int i = 0; i < 10; i++){
      int a = rand() % 10;
      int b = (a + (rand() % 9 + 1)) % 10;
      simple_test_add_edge(a, b);
      simple_test_delete_edge(a, b);
    }

    return 0;
}
