//Author: Qiwei Li, Jiaping Zhang
#include <iostream>
#include "LeafNode.h"
#include "InternalNode.h"
#include "QueueAr.h"

using namespace std;


LeafNode::LeafNode(int LSize, InternalNode *p,
  BTreeNode *left, BTreeNode *right) : BTreeNode(LSize, p, left, right)
{
  values = new int[LSize];
}  // LeafNode()



int LeafNode::getMinimum()const
{
  if(count > 0)  // should always be the case
    return values[0];
  else
    return 0;

} // LeafNode::getMinimum()


LeafNode* LeafNode::insert(int value)
{
  if(count == 0)
  {
    values[0]=value; 
    count++;
    return NULL;
  } //if leaf is empty, insert at [0]
  else if(count < leafSize)
  {
    values[count]=value;
    for(int pos=count; pos>=0; pos--)
    {
      if(values[pos]>value)
      {
        values[pos+1]=values[pos];
        values[pos] = value; 
      }
    }
    count++;
    return NULL;
  } //if not full, insert and sort 
  else
  {
    int max = -1;
    if(value > values[leafSize-1])
      max = value;
    else 
    {
      max = values[leafSize-1];
      values[leafSize-1] = value;
      for(int pos=leafSize-1; pos>=0; pos--)
      {
        if(values[pos]>value)
        {
          values[pos+1]=values[pos];
          values[pos]=value;
        }
      }
    }
    if(leftSibling!=NULL && ((LeafNode*)leftSibling)->count < leafSize)
    {
      ((LeafNode*)leftSibling)->insert(values[0]);
      for(int pos=1; pos<leafSize; pos++)
        values[pos-1]=values[pos];
      values[leafSize-1]=max;
      return NULL;
    } //look left
    else if(rightSibling!=NULL && ((LeafNode*)rightSibling)->count < leafSize)
    {
      ((LeafNode*)rightSibling)->insert(max);
      return NULL;      
    } //look right
    else
    {
      LeafNode* newNode = new LeafNode(leafSize, parent, this, rightSibling);
      if(rightSibling != NULL)
        ((LeafNode*)rightSibling)->setLeftSibling(newNode);
      this->setRightSibling(newNode);
      newNode->insert(max);
      if (leafSize%2)
      {
        while(count > (leafSize/2)+1)
        {
          newNode->insert(values[count-1]);
          count--;
        }
      } //leafSize is odd
      else
      {
        while(count > (leafSize/2))
        {
          newNode->insert(values[count-1]);
          count--;
        }
      } //leafSize is even
      return newNode;
    }
  } //split
}  // LeafNode::insert()

void LeafNode::print(Queue <BTreeNode*> &queue)
{
  cout << "Leaf: ";
  for (int i = 0; i < count; i++)
    cout << values[i] << ' ';
  cout << endl;
} // LeafNode::print()


