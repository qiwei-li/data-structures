// Author: Sean Davis
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

int main()
{
  int gridSize, block, seed, adjacent, numAdjacents, i, adjacents[5];
  char filename[80];

  do {
    cout  << "Grid size (20 - 1000000): ";
    cin >> gridSize;
  }
  while(gridSize < 20 || gridSize > 1000000);


  cout << "Seed: ";
  cin >> seed;

  sprintf(filename, "Power-%d-%d.txt", gridSize, seed);
  ofstream outf(filename);
  srand(seed);

  outf << gridSize << endl;
  char *connected = new char[gridSize];
  //char connected[20];
  memset(connected, 0, gridSize);
  
  for(i = 0; i < 10; i++)
    connected[i] = 1;
  
  int nextLevelLower = 10, nextLevelSize = 20, nextLevelCount = 0;
  
  if(nextLevelLower + nextLevelSize >= gridSize)
     nextLevelSize = gridSize - nextLevelLower;
  
  for(block = 0; block < gridSize; block++)
  {
    //cout << block << endl;

    if(block == nextLevelLower)
    {
      nextLevelLower += nextLevelSize;
      nextLevelSize *=2;
      if(nextLevelLower + nextLevelSize >= gridSize)
        nextLevelSize = gridSize - nextLevelLower;
      nextLevelCount = 0;
    }
    
    numAdjacents = rand() % 3 + 3;  // 3 - 5
    outf  << block << " " << numAdjacents << " ";
    
    for(i = 0; i < 2 && nextLevelCount < nextLevelSize; i++)
    {
      do
      {
         if(nextLevelSize > 0)
          adjacent = rand() % nextLevelSize + nextLevelLower;
        else
          adjacent = rand() % gridSize;
      }  while(connected[adjacent] > 0);
     
      nextLevelCount++;
      adjacents[i] = adjacent;
      connected[adjacent]++;
      outf << adjacent << " " << rand() % 100 + 1 << " ";  // loss is 1 - 100
    }  // for first two adjacents; 

    for( ; i < numAdjacents; i++)
    {
      bool OK;
      
      do
      {
        OK = true;
        if(nextLevelSize > 0)
          adjacent = rand() % nextLevelSize + nextLevelLower;
        else
          adjacent = rand() % gridSize;
        
        if(adjacent == block)  // adjacent to yourself!
          OK = false;
        else 
          for(int j = 0; j < i; j++)
            if(adjacents[j] == adjacent)
              OK = false;
      }  while(!OK);
     
      adjacents[i] = adjacent;
      if(connected[adjacent] == 0)
        nextLevelCount++;
      connected[adjacent]++;
      outf << adjacent << " " << rand() % 100 + 1 << " ";  // loss is 1 - 100
    }  // for later  adjacents; 
     
    outf << endl;
  } // for block

  outf.close();
  return 0;
}

