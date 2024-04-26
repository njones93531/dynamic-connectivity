#include "Forest.h"
#include <iostream>
#include <cstdlib>
#include <sys/time.h>
#include <chrono>

using namespace std;

Forest * F;

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

void simple_test_not_connected(int a, int b){
  F->connected(a, b);
}

void time_test(void test(int a, int b), int trials, string test_name){
  double t_total = 0;
  for(int i = 0; i < trials; i++){
    int a = rand() % trials;
    int b = rand() % trials;
    while(a == b){
      b = rand() % trials;
    }
    auto t_start = std::chrono::high_resolution_clock::now();
    test(a, b);
    auto t_end = std::chrono::high_resolution_clock::now();
    t_total += std::chrono::duration<double, std::milli>(t_end-t_start).count();
  }
  cout << test_name << ",\t" << trials << ",\t" << t_total << ",\t" << t_total / (double) trials << endl;
}

int main()
{ 
  cout << "test_name,\t" << "n,\t" << "t_total,\t" << "t_avg\n";
  for(int trials = 10; trials < 10000; trials *= 10){

    F = new Forest;

    time_test(simple_test_make_node, trials, "make_nw_node");
    time_test(simple_test_not_connected, trials, "nt_connected");
    time_test(simple_test_add_edge, trials, "add_new_edge");
    time_test(simple_test_add_delete_edge, trials, "add_delete_e");
  }

  return 0;
}
