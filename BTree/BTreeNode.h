#ifndef BTreeNodeH
#define BTreeNodeH

#include "QueueAr.h"

class InternalNode;  // forward declaration

class BTreeNode
{
protected:
  int count;
  int leafSize;
  InternalNode *parent;
  BTreeNode *leftSibling;
  BTreeNode *rightSibling;
public:
  BTreeNode(int LSize, InternalNode *p, BTreeNode *left, BTreeNode *right);
  virtual ~BTreeNode() {}  
  int getCount() const;
  BTreeNode* getLeftSibling();
  virtual int getMinimum()const = 0;
  BTreeNode* getRightSibling();
  virtual BTreeNode* insert(int value) = 0;
  virtual void print(Queue <BTreeNode*> &queue) = 0;
  void setLeftSibling(BTreeNode *left);
  void setParent(InternalNode *p);
  void setRightSibling(BTreeNode *right);
}; //BTreeNode class

#endif
