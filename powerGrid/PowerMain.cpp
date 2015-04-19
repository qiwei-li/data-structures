// Author: Sean Davis
#include <fstream>
#include <iostream>
#include "CPUTimer.h"
#include "grid.h"
using namespace std;
#include "PowerMain.h"

int checkConnections(int gridSize, const Block blocks[], int previous[])
{
  int j, totalLoss = 0, last, prev;
  
  for(int i = 0; i < 10; i++)
    previous[i] = -1;

  for(int i = 10; i < gridSize; i++)
    if(previous[i] < 0  || previous[i] >= gridSize)
      cout << "Block #" << i << " is not connected when it should be.\n";
  
  for(int i = 10; i < gridSize; i++)
  {
    last = i;
    
    for(prev = previous[last]; prev >= 0; prev = previous[last])
    {
      for(j = 0; 
        j < blocks[prev].edgeCount && blocks[prev].adjBlocks[j] != last; j++);
      
      if(j == blocks[prev].edgeCount)
      {
        cout << "Block #" << last << " not adjacent to its previous #"
          << prev << endl;
        break;
      } // if previous is not adjacent
      
      totalLoss += blocks[prev].losses[j];
      last = prev;
    } // for each previous in path to block
  }  // for each non-powerhouse block.
   
  return totalLoss;
}  // checkConnections())
 

Block* readFile(const char *filename, int *gridSize)
{
  ifstream inf(filename);
  int blockNum;
  inf >> *gridSize;
  Block *blocks = new Block[*gridSize];
  
  for(int i = 0; i < *gridSize; i++)
  {
    inf >> blockNum;
    inf >>  blocks[i].edgeCount;
    for(int edge = 0; edge < blocks[i].edgeCount; edge++)
        inf >> blocks[i].adjBlocks[edge] >> blocks[i].losses[edge];
  } // for each block
  
  return blocks;
}

int main(int argc, char* argv[])
{
  CPUTimer ct;
  int gridSize, loss;
  const Block *blocks = readFile(argv[1], &gridSize);
  int *previous = new int[gridSize];
  ct.reset();
  new Grid(gridSize, blocks, previous);
  double CPUTime = ct.cur_CPUTime();
  loss = checkConnections(gridSize, blocks, previous);
  cout << "CPU: " << CPUTime << " Loss: " << loss << endl;
  return 0;
}

