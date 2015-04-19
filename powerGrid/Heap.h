fndef HEAP_H
#define HEAP_H

#include "HeapItem.h"

class Heap
{
     private:
          HeapItem     *m_Elements;                 // Pointer to dynamically allocated array
          int          m_iNumElements;              // Number of elements in the heap
          int          m_iHeapLength;               // Size of the array

     public:
          Heap(int size = 10);                     // Parameterized constructor
          ~Heap();                                 // Destructor
          void ReheapDown(int root, int bottom);   // Reheap after removing item
          void ReheapUp(int root, int bottom);     // Reheap after inserting item
          bool Enqueue(HeapItem *item);            // Add an item to the heap
          bool Enqueue(int key, double data);      // Add an item to the heap
          HeapItem *Dequeue();                     // Get item at the root
          int getNumElements();                    // Return number of elements in the heap
          void printAll();                         // Print all the elements in the heap
};

#endif
