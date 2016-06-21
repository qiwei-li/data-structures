# data-structures-and-algorithms
small projects, solving problems with data structures and algorithms in C++ 

## files
* __bags__

 This program simulates the actions of luggage handling for a large aircraft. Luggage is loaded into containers as the luggage arrives. When a container is full, or there is no more luggage, it is loaded into the aircraft. At the destination, the containers are unloaded with the last on being the first off. As each container is unloaded its bags are unloaded in the same order as they were loaded, last on being the last off. This program primarily utilize stacksand queues.

* __balance__

 This program checks if the following symbols are paired: {} \[] () /**/. If all those symbols are paired, the program prints "OK", else it prints the line number of the unpair symbol. This is useful to validate the parenthesis of a code script.

* __timetest__
 
 _timetest.cpp_ will compare the speed of different operations of searching, inserting, and deleting with the following data structures.
    * Linked List
    * Cursor List
    * Stack Array
    * Stack List
    * Queue Array
    * Skip List

* __BTree__
 
 This is my own implementation of the BTree data structure. The program will read a file that contains a series of integers that it will insert into the BTree, and then print the _breadth first traversal_ of the BTree. The program will take three command line parameters: 
    * filename, 
    * M (the number of children that internal nodes have), 
    * L (the number of integers each leaf node holds).
  
* __timetest2__

 _timetest3.cpp_ will compare the speed of different operations of searching, inserting, and deleting with the following data structures.
    * Skip List
    * BST
    * AVL
    * Splay
    * BTree
    * Separate Chaining Hash
    * Quadratic Probing Hash
    * Quadratic Probing Pointer Hash
    * Binary Heap 

* __simulateCache__

 This program is a CPU cache simulator that has all of it data structures fit in 64000 bytes. The goal is to minimize the time as well as the number of reads and writes to/from simulated RAM caused by cache misses processing one million ADD instructures.
 
* __powerGrid__

 This program is an electrical grid optimizer that determines the path of electrical power to each block to minimize the electrical loss. Electrical blocks 0-9 are connected directly to the power house, the rest are connected to with three or five other blocks (directed). The program will print the 