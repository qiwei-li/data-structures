#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "BTree.h"

using namespace std;

int main(int argc, char *argv[])
{
  BTree tree(atoi(argv[2]), atoi(argv[3]));
  int value;
  char s[80];

  ifstream inf(argv[1]);
  while(inf >> value)
  {
    cout << "Inserting " << value << ". \n";
    tree.insert(value);
    tree.print();
    fgets(s, 80, stdin);
  } // while

  tree.print();
  return 0;
}  // main

