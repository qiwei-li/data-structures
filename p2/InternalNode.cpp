//Author: Qiwei Li, Jiaping Zhang
#include <iostream>
#include "InternalNode.h"

using namespace std;

InternalNode::InternalNode(int ISize, int LSize,
  InternalNode *p, BTreeNode *left, BTreeNode *right) :
  BTreeNode(LSize, p, left, right), internalSize(ISize)
{
  keys = new int[internalSize]; // keys[i] is the minimum of children[i]
  children = new BTreeNode* [ISize];
} // InternalNode::InternalNode()


int InternalNode::getMinimum()const
{
  if(count > 0)   // should always be the case
    return children[0]->getMinimum();
  else
    return 0;
} // InternalNode::getMinimum()


InternalNode* InternalNode::insert(int value)
{
  for(int c=0; c<count; c++)
    keys[c]=children[c]->getMinimum();
  
  if(count < internalSize)
  {  
    if(keys[0]>value)
    {
      BTreeNode *lowerlevelptr = children[0]->insert(value);
      keys[0]=(children[0])->getMinimum();  
      if(lowerlevelptr!=NULL)
      {
        for(int pos=count-1; pos>0; pos--)
        {
          keys[pos+1]=keys[pos];
          children[pos+1]=children[pos];
        }
        keys[0]=value;
        keys[1]=lowerlevelptr->getMinimum();
        children[1]=lowerlevelptr;
        count++;
      } //if child split and current has space
      return NULL;
    } //find value at beginning
    else if(keys[count-1] < value)
    {
      BTreeNode *lowerlevelptr = children[count-1]->insert(value);
      keys[count-1]=(children[count-1])->getMinimum();
      if(lowerlevelptr!=NULL)
      {
        keys[count]=lowerlevelptr->getMinimum();
        children[count]=lowerlevelptr;
        count++;
      } //if child split and current has space
      return NULL;
    } //find value at the end
    else
    {
      int pos=0;
      while(keys[pos]<value)
        pos++;
      BTreeNode* lowerlevelptr = children[pos-1]->insert(value);
      keys[pos]=children[pos]->getMinimum();
      if(lowerlevelptr!=NULL)
      {
        for(int i=count-1; i>=pos; i--)
        {
          keys[i+1]=keys[i];
          children[i+1]=children[i];
        }
        children[pos]=lowerlevelptr;
        keys[pos]=children[pos]->getMinimum();
        count++;
      } //if child split and current has space
      return NULL;
    } //not full, search middle
  } //not full

  else //current internalnode is full
  {
    if(keys[0]>value)
    {
      BTreeNode *lowerlevelptr = children[0]->insert(value);
      keys[0]=(children[0])->getMinimum();   
      if(lowerlevelptr!=NULL)
      {
        int maxkey = keys[internalSize-1];
        BTreeNode* maxchild = children[internalSize-1];
        keys[internalSize-1]=lowerlevelptr->getMinimum();
        children[internalSize-1]=lowerlevelptr;
        for(int i=internalSize-1; i>0; i--)
        {
          if(keys[i]<keys[i-1]);
          {
            keys[i]=keys[i-1];
            children[i]=children[i-1];
            keys[i-1]=lowerlevelptr->getMinimum();
            children[i-1]=lowerlevelptr;
          }
        }
        if(leftSibling!=NULL && ((InternalNode*)leftSibling)->count < internalSize)
        {
          ((InternalNode*)leftSibling)->insert(children[0]);
          for(int pos2=1; pos2<internalSize; pos2++)
          {
            keys[pos2-1]=keys[pos2];
            children[pos2-1]=children[pos2];
          }
          keys[internalSize-1]=maxkey;
          children[internalSize-1]=maxchild;
          return NULL;
        } //look left
        else if(rightSibling!=NULL && ((InternalNode*)rightSibling)->count < internalSize)
        {
          ((InternalNode*)rightSibling)->insert(maxchild);
          return NULL;
        } //look right
        else
        {
          InternalNode* newNode = new InternalNode(internalSize, leafSize, parent, this, rightSibling);
          if(rightSibling!=NULL)
            ((InternalNode*)rightSibling)->setLeftSibling(newNode);
          this->setRightSibling(newNode);
          newNode->insert(maxchild);
          if(internalSize%2)
          {
            while(count>(internalSize/2)+1)
            {
              newNode->insert(children[count-1]);
              count--;
            }
          } //odd
          else
          {
            while(count>(internalSize/2))
            {
              newNode->insert(children[count-1]);
              count--;
            }
          } //even
          
          return newNode;
        }//split    
      } //children split, current either left or right or split
    } //find value at beginning
    else if(keys[count-1] < value)
    {
      BTreeNode *lowerlevelptr = children[count-1]->insert(value);
      keys[count-1]=(children[count-1])->getMinimum();
      if(lowerlevelptr!=NULL)
      {
        int maxkey = lowerlevelptr->getMinimum();
        BTreeNode* maxchild = lowerlevelptr;
        if(leftSibling!=NULL && ((InternalNode*)leftSibling)->count < internalSize)
        {
          ((InternalNode*)leftSibling)->insert(children[0]);
          for(int pos2=1; pos2<internalSize; pos2++)
          {
            keys[pos2-1]=keys[pos2];
            children[pos2-1]=children[pos2];
          }
          keys[internalSize-1]=maxkey;
          children[internalSize-1]=maxchild;
          return NULL;
        } //look left
        else if(rightSibling!=NULL && ((InternalNode*)rightSibling)->count < internalSize)
        {
          ((InternalNode*)rightSibling)->insert(maxchild);
          return NULL;
        } //look right
        else
        {
          InternalNode* newNode = new InternalNode(internalSize, leafSize, parent, this, rightSibling);
          if(rightSibling!=NULL)
            ((InternalNode*)rightSibling)->setLeftSibling(newNode);
          this->setRightSibling(newNode);
          newNode->insert(maxchild);
          if(internalSize%2)
          {
            while(count>(internalSize/2)+1)
            {
              newNode->insert(children[count-1]);
              count--;
            }
          } //odd
          else
          {
            while(count>(internalSize/2))
            {
              newNode->insert(children[count-1]);
              count--;
            }
          } //even
          return newNode;
        }//split 
      } //if split
    } //find value at the end
    else
    {
      int pos=0;
      while(keys[pos]<value)
        pos++;
      BTreeNode* lowerlevelptr = children[pos-1]->insert(value);
      keys[pos-1]=children[pos-1]->getMinimum();
      keys[pos]=children[pos]->getMinimum();
      if(lowerlevelptr!=NULL)
      {
        int maxkey=keys[internalSize-1];
        BTreeNode* maxchild=children[internalSize-1];
        keys[internalSize-1]=lowerlevelptr->getMinimum();
        children[internalSize-1]=lowerlevelptr;
        for(int i=internalSize-1; i>0; i--)
        {
          if(keys[i]<keys[i-1])
          {
            keys[i]=keys[i-1];
            children[i]=children[i-1];
            keys[i-1]=lowerlevelptr->getMinimum();
            children[i-1]=lowerlevelptr;
          }
        }
        if(leftSibling!=NULL && ((InternalNode*)leftSibling)->count < internalSize)
        {
          ((InternalNode*)leftSibling)->insert(children[0]);
          for(int pos2=1; pos2<internalSize; pos2++)
          {
            keys[pos2-1]=keys[pos2];
            children[pos2-1]=children[pos2];
          }
          keys[internalSize-1]=maxkey;
          children[internalSize-1]=maxchild;
          return NULL;
        } //look left
        else if(rightSibling!=NULL && ((InternalNode*)rightSibling)->count < internalSize)
        {
          ((InternalNode*)rightSibling)->insert(maxchild);
          return NULL;
        } //look right
        else
        {
          InternalNode* newNode = new InternalNode(internalSize, leafSize, parent, this, rightSibling);
          if(rightSibling!=NULL)
            ((InternalNode*)rightSibling)->setLeftSibling(newNode);
          this->setRightSibling(newNode);
          newNode->insert(maxchild);
          if(internalSize%2)
          {
            while(count>(internalSize/2)+1)
            {
              newNode->insert(children[count-1]);
              count--;
            }
          } //odd
          else
          {
            while(count>(internalSize/2))
            {
              newNode->insert(children[count-1]);
              count--;
            }
          } //even
          return newNode;
        }//split 
      }
    } //not full, search middleint pos=0;
  } //internal fulled
  return NULL;
} // InternalNode::insert()

void InternalNode::insert(BTreeNode *oldRoot, BTreeNode *node2)
{ 
  keys[0] = oldRoot->getMinimum();
  keys[1] = node2->getMinimum();
  children[0] = oldRoot;
  children[1] = node2;
  count=2;
} // InternalNode::insert()

void InternalNode::insert(BTreeNode *newNode) // from a sibling
{
  newNode->setParent(this);
  if(count==0)
  {
    keys[0]=newNode->getMinimum();
    children[0]=newNode;
    count++;
  }
  else
  {
    keys[count]=newNode->getMinimum();
    children[count]=newNode;
    for(int pos=count; pos>0; pos--)
    {
      if(keys[pos]<keys[pos-1])
      {
        keys[pos]=keys[pos-1];
        children[pos]=children[pos-1];
        keys[pos-1]=newNode->getMinimum();
        children[pos-1]=newNode;
      }
    }
    count++;
  }    
} // InternalNode::insert()

void InternalNode::print(Queue <BTreeNode*> &queue)
{
  int i;

  cout << "Internal: ";
  for (i = 0; i < count; i++)
    cout << keys[i] << ' ';
  cout << endl;

  for(i = 0; i < count; i++)
    queue.enqueue(children[i]);

} // InternalNode::print()


