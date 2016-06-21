#include "grid.h"

Grid::Grid(int gridSize, const Block *blocks, int previous[])
{
  heapBegin = 0; heapEnd = 0;
  tempB = 0; tempD = 0;
  parent = 0; left = 0; right = 0;
  blockNum = 0; 
  prevDist = 0;
  count=0;
  minB=INF, minD=INF;
  done=0;
  djtable = new vertex[gridSize]; 
  myheap = new heap[5*gridSize];

  for(blockNum=0; blockNum<10; blockNum++)
  {
    djtable[blockNum].isFinal=1;
    djtable[blockNum].myPos=blockNum;
    djtable[blockNum].dv=0;
    djtable[blockNum].previous=0; 
    put(blocks, djtable, blockNum, prevDist, gridSize, myheap, tempB, tempD, itself);  
  }
  blockNum=9;  
  while(done==0)
  {
    search(count,djtable, blockNum, prevDist, heapBegin, heapEnd);
    if(blockNum==(INF-1))
      break;
    else
    {
      put(blocks, djtable, blockNum, prevDist, gridSize, myheap, tempB, tempD, itself);
    }
  }
 
  for(blockNum=10; blockNum<gridSize; blockNum++)
  {
    previous[blockNum]=djtable[blockNum].previous;
  }
} // Grid()

void Grid::put(const Block *blocks, vertex *djtable, int &blockNum, unsigned &prevDist, int &gridSize, heap *myheap, int &tempB, unsigned &tempD, int &itself)
{
  for(int i=0; i<blocks[blockNum].edgeCount; i++)
  {
    if(djtable[(blocks[blockNum].adjBlocks[i])].dv > (blocks[blockNum].losses[i]+prevDist))
    {
      djtable[(blocks[blockNum].adjBlocks[i])].myPos = blocks[blockNum].adjBlocks[i];
      djtable[(blocks[blockNum].adjBlocks[i])].dv = (blocks[blockNum].losses[i]+prevDist);
      djtable[(blocks[blockNum].adjBlocks[i])].previous = blockNum;
      myheap[heapEnd].heapB = blocks[blockNum].adjBlocks[i];
      myheap[heapEnd].heapD = (blocks[blockNum].losses[i]+prevDist);
      heapEnd++;
      itself = heapEnd-1;
      while(myheap[itself].heapD < myheap[(itself-1)/2].heapD)
      {
        tempB = myheap[(itself-1)/2].heapB;
        tempD = myheap[(itself-1)/2].heapD;
        myheap[(itself-1)/2].heapB = myheap[itself].heapB;
        myheap[(itself-1)/2].heapD = myheap[itself].heapD;
        myheap[itself].heapB = tempB;
        myheap[itself].heapD = tempD;
        itself = (itself-1)/2;
      }
    }
  }
}

void Grid::search(int &count, vertex *djtable, int &blockNum, unsigned &prevDist, int &heapBegin, int &heapEnd)
{
  blockNum=INF-1; prevDist=INF-1;
  while(heapEnd>0)
  {  
    blockNum=myheap[heapBegin].heapB; 
    prevDist=myheap[heapBegin].heapD;
    myheap[heapBegin].heapB = myheap[heapEnd-1].heapB;
    myheap[heapBegin].heapD = myheap[heapEnd-1].heapD;
    heapEnd--;
    itself = 0;
    while(itself*2+1 <  heapEnd)
    {
      if(myheap[itself].heapD>myheap[itself*2+1].heapD||myheap[itself].heapD>myheap[itself*2+2].heapD)
      {
        if(myheap[itself*2+1].heapD < myheap[itself*2+2].heapD)
        {
          tempB = myheap[itself*2+1].heapB;
          tempD = myheap[itself*2+1].heapD;
          myheap[itself*2+1].heapB = myheap[itself].heapB;
          myheap[itself*2+1].heapD = myheap[itself].heapD;
          myheap[itself].heapB = tempB;
          myheap[itself].heapD = tempD;
          itself = itself*2+1;
        }
        else
        {
          tempB = myheap[itself*2+2].heapB;
          tempD = myheap[itself*2+2].heapD;
          myheap[itself*2+2].heapB = myheap[itself].heapB;
          myheap[itself*2+2].heapD = myheap[itself].heapD;
          myheap[itself].heapB = tempB;
          myheap[itself].heapD = tempD;
          itself = itself*2+2;
        }
      }
      else
        break;
    } //P down

    if(djtable[blockNum].isFinal==0)
    {
      djtable[blockNum].isFinal=1;
      break;
    }
  }
  
  if(blockNum==INF)
    done=1;
}
