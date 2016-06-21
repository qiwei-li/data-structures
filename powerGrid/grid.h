#ifndef gridH
#define gridH
#define INF 999999999

#include <iostream>
#include "PowerMain.h"

using namespace std;

class Grid
{

public:
  int heapBegin;
  int heapEnd;
  int tempB;;
  unsigned tempD;
  int itself;
  int parent;
  int left;
  int right;
  int blockNum; 
  unsigned prevDist;
  int count;
  int minB;
  unsigned minD;
  bool done;
  typedef struct vertex
  {
    vertex():dv(INF),myPos(-1),previous(-1),isFinal(0){ }
    unsigned dv;
    int myPos;
    int previous;
    bool isFinal;
  } vertex;
  vertex *djtable;
  
  typedef struct heap
  {
    heap():heapB(0),heapD(0){}
    int heapB;
    unsigned heapD;
  } heap;
  heap *myheap;
  Grid(int gridSize, const Block *blocks, int previous[]);
  
  void put(const Block *blocks, vertex *djtable, int &blockNum, unsigned &prevDist, int &gridSize, heap *myheap, int &tempB, unsigned &tempD, int &itself);

  void search(int &count, vertex *djtable, int &blockNum, unsigned &prevDist, int &heapBegin, int &heapEnd); 
}; // class Grid

#endif
