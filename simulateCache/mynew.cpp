#define _USE_OLD_RW_STL

#include <cstdlib> //needed for malloc
#include <iostream>
#include "mynew.h"
// #define SHOW_SIZE
// using namespace std;

int maxRAM = 0;
int currentRAM = 0;
int sizePos = -1;

void initializeNew()
{
  int *ptr = new int[5];
  if(ptr[-1] == 0)
    sizePos = -2;
  else
    sizePos = -1;
  delete [] ptr;
}

void* operator new(std::size_t size) throw (std::bad_alloc) //size is in bytes
{
	int* ptr = (int*) malloc(size);
  currentRAM += ptr[sizePos];

  if(currentRAM > maxRAM)
    maxRAM = currentRAM;

  return (void*) ptr;
}

void operator delete(void* to_delete) throw ()
{
  currentRAM -= ((int*) to_delete)[sizePos];
	free(to_delete);
}

void* operator new[] (size_t size) throw (std::bad_alloc) //size is in bytes
{
  int* ptr = (int*) malloc(size);
#ifdef SHOW_SIZE
  cout << "Requesting: " << size << " Getting: " << ptr[sizePos] << endl;
#endif
  currentRAM += ptr[sizePos];
  

  if(currentRAM > maxRAM)
    maxRAM = currentRAM;

  return (void*) ptr;
}

void operator delete[] (void* to_delete) throw ()
{
  currentRAM -= ((int*) to_delete)[sizePos];
	free(to_delete);
}


