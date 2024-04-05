#include "SplayTree.h"
#include <iostream>

using namespace std;

int main()
{

    SplayTree tree;
    int sequence[10] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    int count = 0;
    for(int i : sequence){
      tree.insert(count++, i);
    }

    cout << "KEYS:" << endl;
    tree.print_key();
    cout << "VALS:" << endl;
    tree.print_val();

    return 0;
}
