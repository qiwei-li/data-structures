#ifndef CPURUNNER_H
#define CPURUNNER_H

typedef enum{
  ADD, LOAD, STORE, DONE
} OpCode;

typedef struct
{
  unsigned addr1;
  unsigned addr2;
  unsigned addr3;
} Instruction;

#endif

