// Author: Qiwei Li
#ifndef gridH
#define gridH
#define INF 999999999

#include <iostream>
#include "PowerMain.h"

using namespace std;

class Grid
{

public:
  int blockNum; 
  unsigned prevDist;
  int finalCount;
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

  vertex *heap;
  Grid(int gridSize, const Block *blocks, int previous[]);
  

  void put(const Block *blocks, vertex *heap, int &blockNum, unsigned &prevDist, int &gridSize);
 
  void search(vertex *heap, int &minB, unsigned &minD, int &gridSize);
}; // class Grid

#endif
