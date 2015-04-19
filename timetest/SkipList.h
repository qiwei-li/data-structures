//**************************  genSkipL.h  ***************************
//                     generic skip list class
//  Adapted from Drozdek's genSkipL.h by Sean Davis 9/28/01
//  Copy constructor, ==,  and < must be defined for the stored class, T.
//  Added ITEM_NOT_FOUND, and required approx max number in list to be passed
//   in constructor

#ifndef SKIPLIST_H 
  #define SKIPLIST_H

#include <stdlib.h> // for rand()

template<class T> class SkipList;  // forward declaration

template<class T>
class SkipListNode {
  T info;
  SkipListNode<T> **next;
public:
	SkipListNode(const T &el, SkipListNode<T> **n = NULL):info(el),next(n){}
  friend class SkipList<T>;
}; // class SkipListNode


template<class T>
class SkipList {
protected:
  static const int MAX_LEVELS = 33; // Maximum lg(MAX_INT)
  typedef SkipListNode<T> *nodePtr;
  nodePtr *root;
  int *powers;
  int maxLevel;
  T ITEM_NOT_FOUND;
  void choosePowers();
  int  chooseLevel();
public:
  SkipList(const T &el, int MaxSize = 16);
  ~SkipList();
  T& find(const T&); // Will return ITEM_NOT_FOUND if list is empty.
  bool isEmpty(){return root[0] == NULL;}
  void insert(const T&);  // Will not accept duplicates
  bool deleteNode(const T&);  // returns true if element was in list.
}; // class SkipList

#include "SkipList.cpp"

#endif
