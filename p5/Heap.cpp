#pragma warning(disable:4996)

#include <iostream>
#include "Heap.h"

using namespace std;

Heap::Heap(int size)
{
     m_Elements = new HeapItem[size];
     m_iNumElements = 0;
     m_iHeapLength = size;
}

Heap::~Heap()
{
     delete[] m_Elements;
}

void Heap::ReheapDown(int root, int bottom)
{
     int maxChild;
     int rightChild;
     int leftChild;
     HeapItem temp;

     leftChild = root * 2 + 1;          // Get index of root's left child
     rightChild = root * 2 + 2;
     if(leftChild <= bottom)               
     {
          if(leftChild == bottom)          // If this root has no right child then 
          {
               maxChild = leftChild;     //     leftChild must hold max key
          }
          else
          {
          	if(m_Elements[leftChild].getKey() <= m_Elements[rightChild].getKey())
                    maxChild = rightChild;
               else
                    maxChild = leftChild;
          }
          if(m_Elements[root].getKey() < m_Elements[maxChild].getKey())
          {
            temp = m_Elements[root];
               m_Elements[root] = m_Elements[maxChild];
               m_Elements[maxChild] = temp;
     	  ReheapDown(maxChild, bottom);
          }
     }
}

void Heap::ReheapUp(int root, int bottom)
{
     int parent;
     HeapItem temp;

     if(bottom > root)
     {
          parent = (bottom -1) / 2;
          if(m_Elements[parent].getKey() < m_Elements[bottom].getKey())
          {
               
               temp = m_Elements[parent];
               m_Elements[parent] = m_Elements[bottom];
               m_Elements[bottom] = temp;
               ReheapUp(root, parent);
          }
     }
}

bool Heap::Enqueue(HeapItem *item)
{
     if(m_iNumElements < m_iHeapLength)
     {
          m_Elements[m_iNumElements] = *item; // Copy item into array
          ReheapUp(0, m_iNumElements);
          m_iNumElements++;
          return true;
     }
     return false;
}

bool Heap::Enqueue(int key, double data)
{
     bool retVal;
     HeapItem *temp = new HeapItem(key, data);
     retVal = Enqueue(temp);
     delete temp;  // Delete this dynamically created one
     return retVal;
}

HeapItem *Heap::Dequeue()
{
     HeapItem *temp = new HeapItem(m_Elements[0].getKey(), m_Elements[0].getData());
     m_iNumElements--;
     m_Elements[0] = m_Elements[m_iNumElements];
     ReheapDown(0, m_iNumElements - 1);
     if(m_iNumElements == 0)
         return NULL;
     else
         return temp;
}

int Heap::getNumElements()
{
     return m_iNumElements;
}

void Heap::printAll()
{
     for(int i=0; i<m_iNumElements; i++)
     {
          cout << "Heap element " << i << ". key=" << m_Elements[i].getKey() << "  data=" <<
               m_Elements[i].getData() << endl;
     }
}
