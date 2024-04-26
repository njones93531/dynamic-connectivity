# dynamic-connectivity
Working implementation of dynamic connectivity in a forest using euler tour trees.  

Usage: run `make` to compile.

Binaries: 
- splay_tree_test.exe: tests splay tree implementation for correctness
- forest_test.exe: tests dynamic connectivity in a forest for correctness
- forest_time.exe: tests running time for dynamic connectivity in a forest. Outputs as binary. The testing itself is not as scalable as the dyanmic connectivity code, as the randomly generated inputs can struggle to find valid parameters for certain functions (i.e. add_edge() must operate on disconnected nodes).

Code: 
- SplayTree.cpp/SplayTree.h: Implementation of rank-based splay tree.
- Forest.cpp/Forest.h: Implementation of dynamic connectivity in a forest using euler tour splay trees.
-   Note: delete_edge() is more powerful than required; delete_edge(a, b) will delete node b's outgoing edge that connects to a's tree, regardless of whether a and b share an edge. The runtime is still O(logn).
- forest_test.cpp/forest_time.cpp/splay_tree_test.cpp: Testing scripts that compile into the binaries above.
- plot.py: Written with aid of ChatGPT. Generates a plot with matplotlib demonstrating all functions run in O(logn) time.

Correctness: 
- splay_tree_test.exe runs a relatively extensive randomized testing suite that covers all relevant functions. Some tests may require visual confirmation for correctness.
- forest_test.exe runs a relatively extensive randomized testing suite that covers all relevant functions. Some tests may require visual confirmation for correctness.

Other: 
- BigO.png shows that the average runtime of an operation does not increase significantly as the log of N increases. Therfore, we can conclude that all operations run in O(logn).
- time.out contains the timings used to generate BigO.png.
