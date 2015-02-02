#include <fstream>
#include <cstdlib>
#include "BTree.h"

using namespace std;

int main(int argc, char *argv[])
{
  BTree tree(atoi(argv[2]), atoi(argv[3]));
  int value;

  ifstream inf(argv[1]);
  while(inf >> value)
  {
    tree.insert(value);
  } // while

  tree.print();
  return 0;

}  // main

