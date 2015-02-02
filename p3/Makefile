timetest3.out: timetest3.o BTree.o  BTreeNode.o InternalNode.o LeafNode.o 
	g++ -Wall -ansi -g -o timetest3.out timetest3.o BTree.o BTreeNode.o InternalNode.o LeafNode.o  

timetest3.o : timetest3.cpp AvlTree.h  CPUTimer.h  QuadraticProbing.h \
  SkipList.h  vector.h BinaryHeap.h CursorList2.h  QueueAr.h \
  SplayTree.h dsexceptions.h LinkedList.h  QueueLL.h StackAr.h \
  BinarySearchTree.h mystring.h SeparateChaining.h StackLi.h QuadraticProbingPtr.h
	g++ -Wall -ansi -g -c timetest3.cpp

BTree.o: BTree.cpp BTree.h BTreeNode.h LeafNode.h InternalNode.h 
	g++ -Wall -ansi -g -c BTree.cpp

BTreeNode.o: BTreeNode.cpp BTreeNode.h 
	g++ -Wall -ansi -g -c BTreeNode.cpp

InternalNode.o: InternalNode.cpp InternalNode.h 
	g++ -Wall -ansi -g -c InternalNode.cpp

LeafNode.o: LeafNode.cpp LeafNode.h InternalNode.h QueueAr.h 
	g++ -Wall -ansi -g -c LeafNode.cpp


clean:
	rm -f timetest3.out timetest3.o BTree.o BTreeNode.o BTreeShort.o InternalNode.o LeafNode.o  
