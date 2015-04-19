// Author: Qiwei Li

#include "grid.h"

Grid::Grid(int gridSize, const Block *blocks, int previous[])
{
  blockNum = 0; 
  prevDist = 0;
  finalCount=0;
  minB=INF, minD=INF;
  done=0;
  heap = new vertex [gridSize]; 

  for(blockNum=0; blockNum<10; blockNum++)
  {
    heap[blockNum].isFinal=1;
    heap[blockNum].myPos=blockNum;
    heap[blockNum].dv=0;
    heap[blockNum].previous=0; 
    put(blocks, heap, blockNum, prevDist, gridSize);  
  }
  
  while(done==0)
  {
    search(heap, minB, minD, gridSize);
    put(blocks, heap, blockNum, prevDist, gridSize);
  }
  
  for(blockNum=10; blockNum<gridSize; blockNum++)
  {
    previous[blockNum]=heap[blockNum].previous;
  }
} // Grid()

void Grid::put(const Block *blocks, vertex *heap, int &blockNum, unsigned &prevDist, int &gridSize)
{
  for(int i=0; i<blocks[blockNum].edgeCount; i++)
  {
    if(heap[(blocks[blockNum].adjBlocks[i])].dv > (blocks[blockNum].losses[i]+prevDist))
    {
      heap[(blocks[blockNum].adjBlocks[i])].myPos = blocks[blockNum].adjBlocks[i];
      heap[(blocks[blockNum].adjBlocks[i])].dv = (blocks[blockNum].losses[i]+prevDist);
      heap[(blocks[blockNum].adjBlocks[i])].previous = blockNum;
    }
  }
}  
void Grid::search(vertex *heap, int &minB, unsigned &minD, int &gridSize )
{
  minB=INF; minD=INF;
  for(int j=0; j<gridSize; j++)
  {
    if(heap[j].isFinal==0  && heap[j].dv < minD)
    {
      minD = heap[j].dv;
      minB = heap[j].myPos;
    }
  }
  if(minD==INF)
    done=1;
  else
  {
    heap[minB].isFinal=1;
    blockNum=minB;
    prevDist=minD;
  }
}


