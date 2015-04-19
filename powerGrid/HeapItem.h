#ifndef HEAPITEM_H
#define HEAPITEM_H

class HeapItem
{
     private:
          int m_iKey;                              // Heap item priority key
          double m_dData;                         // Dummy data value

     public:
          HeapItem();                              // Default constructor
          HeapItem(int key, double data);     // Constructor
          ~HeapItem();                         // Destructor
          int getKey();                         // Return item priority
          void setKey(int key);               // Set the priority key value
          double getData();                    // Return data item
          void setData(double data);          // Set the data item value
};

#endif
