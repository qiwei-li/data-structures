#include <iostream>

using namespace std;

template <class Comparable>
class BinaryTree
{
  Comparable object;
  BinaryTree<Comparable> *left;
  BinaryTree<Comparable> *right;

public:
  BinaryTree();
  BinaryTree(const Comparable &ob, BinaryTree<Comparable> *l,
    BinaryTree<Comparable> *r);
  bool operator< (const BinaryTree <Comparable> &rhs)const;
  void printTree(char encoding[], int count);
  const Comparable& getObject()const;
};


template <class Comparable>
BinaryTree<Comparable>::BinaryTree() : left(NULL), right(NULL)
{
} // BinaryTree()

template <class Comparable>
BinaryTree<Comparable>::BinaryTree(const Comparable &ob, BinaryTree<Comparable> *l,
  BinaryTree<Comparable> *r) : object(ob), left(l), right(r)
{
} // BinaryTree()

template <class Comparable>
const Comparable& BinaryTree<Comparable>::getObject()const
{
  return object;
} // getObject()

template <class Comparable>
bool BinaryTree<Comparable>::operator< (const BinaryTree <Comparable> &rhs)const
{
  return object < rhs.object;
} // operator<


template <class Comparable>
void BinaryTree<Comparable>::printTree(char encoding[], int count)
{
  if(left)
  {
    encoding[count] = '0';
    left->printTree(encoding, count + 1);
  }

  if(right)
  {
    encoding[count] = '1';
    right->printTree(encoding, count + 1);
  }
  
  if(!left && !right)
  {
    cout << object << ' ';
    for(int i = 0; i < count; i++)
      cout << encoding[i];
    cout << endl;
  }
} // printTree()


