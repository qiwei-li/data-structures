#ifndef cpuH
#define cpuH

#include "CPURunner.h"

class CPU
{
public:
  CPU();
  int state;
  int arrSize;
  int tempAddr1;
  int mybuffer1, mybuffer2, index1, index2, index3;  
  int lastloop;
  typedef struct cacheline
  {
    cacheline():tag(0),value(0),isFull(0),isDirty(0){ }
    unsigned tag;
    unsigned value;
    bool isFull;
    bool isDirty;
  } cacheline;
  cacheline *arr;
  void operation(OpCode &opCode, Instruction &instruction, int &buffer);
};
#endif
