#include "Forest.h"
#include <iostream>
#include <cstdlib>
#include <sys/time.h>
#include <chrono>
#include <iomanip>

using namespace std;

Forest * F;

bool connected(int a, int b){
  return (a!=b && F->connected(a, b));
}

bool not_connected(int a, int b){
  return (a!=b && !F->connected(a, b));
}

bool not_equal(int a, int b){
  return a!=b;
}

bool ret_true(int a, int b){
  return true;
}

void simple_test_make_node(int a, int b){
  F->make_node();
}

void simple_test_add_edge(int a, int b){
  F->add_edge(a, b);
}

void simple_test_add_delete_edge(int a, int b){
  F->add_edge(a, b);
  F->delete_edge(a, b);
}

void simple_test_connected(int a, int b){
  F->connected(a, b);
}

void time_test(void test(int a, int b), bool test_req(int a, int b), int trials, string test_name){
  double t_total = 0;
  for(int i = 0; i < trials; i++){
    int a,b;
    if (!F->nodes.empty()){
      a = rand() % (int)F->nodes.size();
      b = rand() % (int)F->nodes.size();
      while(!test_req(a, b)){
        b++;
        if(b >= (int)F->nodes.size()) b = 0;
      }
    }
    auto t_start = std::chrono::high_resolution_clock::now();
    test(a, b);
    auto t_end = std::chrono::high_resolution_clock::now();
    t_total += std::chrono::duration<double, std::milli>(t_end-t_start).count();
  }
  cout << setw(8) << test_name << "," << setw(8) << trials << "," << setw(8) << t_total << "," << setw(8) << t_total / (double) trials << endl;
}

int main()
{ 
  cout << "test_name," << "n," << "t_total," << "t_avg\n";
  for(int trials = 10; trials <= 1000000; trials *= 10){

    F = new Forest;
    //Make 2N nodes to help find unconnected nodes to add edges to
    time_test(simple_test_make_node, ret_true, trials*2, "make_node");
    time_test(simple_test_add_edge, not_connected, trials, "add_new_edge");
    time_test(simple_test_add_delete_edge, not_connected, trials, "add_delete_e");
    time_test(simple_test_connected, not_equal, trials, "connected");
  }

  return 0;
}
