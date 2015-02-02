#include "HeapItem.h"

HeapItem::HeapItem()
{
  m_iKey=0;
  m_dData = 0.0;
}
HeapItem::HeapItem(int key, double data)
{
     m_iKey = key;
     m_dData = data;
}
HeapItem::~HeapItem()
{
}

int HeapItem::getKey()
{
     return m_iKey;
}

void HeapItem::setKey(int key)
{
     m_iKey = key;
}

double HeapItem::getData()
{
     return m_dData;
}

void HeapItem::setData(double data)
{
     m_dData = data;
}
