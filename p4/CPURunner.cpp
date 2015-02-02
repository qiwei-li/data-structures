#include <iostream>
#include<fstream>
#include<cstdlib>
#include<cstdio>
#include <cstring>
#include "CPUTimer.h"
#include "cpu.h"
#include "CPURunner.h"
#include "mynew.h"

using namespace std;
extern int maxRAM;
extern int currentRAM;



Instruction* readFile(const char *filename, unsigned startingAddresses[],
  unsigned short *numProcesses, int *numInstructions, int **RAM,
  int **RAM2, int *compulsory)
{
  int count = 0, offset, *buffer2;
  char process;
  unsigned process_instructions;
  unsigned short address;
  bool *read, *written;


  ifstream inf(filename, ios::binary);
  inf.read((char*) numInstructions, sizeof(int));
  inf.read((char*) numProcesses, sizeof(unsigned short));
  int size = (*numProcesses + 1) * 250000;
  *RAM = new int[size];
  *RAM2 = buffer2 = new int[size];
  read = new bool[size];
  written = new bool[size];

  for(int i = 0; i < size; i++)
  {
    buffer2[i] = (*RAM)[i] = i;
    read[i] = written[i] = false;
  }

  for(int i = 0; i < *numProcesses; i++)
    inf.read((char*) &startingAddresses[i], sizeof(unsigned));


  offset = startingAddresses[0];

  Instruction *instructions = new Instruction[*numInstructions];
  while(count < *numInstructions)
  {
    inf.read(&process, sizeof(char));
    inf.read((char*) &process_instructions, sizeof(unsigned));
    for(unsigned i = 0; i < process_instructions; i++)
    {
      inf.read((char*) &address, sizeof(unsigned short));
      instructions[count].addr1 = startingAddresses[(int)process] + address * 4;
      inf.read((char*) &address, sizeof(unsigned short));
      instructions[count].addr2 = startingAddresses[(int)process] + address * 4;
      inf.read((char*) &address, sizeof(unsigned short));
      instructions[count].addr3 = startingAddresses[(int)process] + address * 4;
      buffer2[(instructions[count].addr3 - offset) / 4]
        =  buffer2[(instructions[count].addr2 - offset) / 4]
        +  buffer2[(instructions[count].addr1 - offset) / 4];
      read[(instructions[count].addr1 - offset) / 8] = true;
      read[(instructions[count].addr2 - offset) / 8] = true;
      written[(instructions[count].addr3 - offset) / 8] = true;
      count++;
    } // for each instruction
  }  // while more instructions

  inf.close();
  count = 0;
  for(int i = 0; i < size; i++)
  {
    if(read[i])
      count++;
    if(written[i])
      count++;
  } // for

  *compulsory = count;

  delete [] read;
  delete [] written;
  return instructions;
} // readFile()

void checkRAM(int *RAM, int *RAM2, int size, unsigned offset)
{
  for(int i = 0; i < size; i++)
    if( RAM[i] != RAM2[i] )
    {
      cout << "RAM at address " << 4 * i + offset << " (0x"
        << hex << 4 * i + offset << dec << ") should be "
        << RAM2[i] << " but is " << RAM[i] << endl;
      break;
    }
} // checkRAM()


int main(int argc, const char **argv)
{
  Instruction *instructions, instruction;
  unsigned startingAddresses[100], offset;
  unsigned short numProcesses;
  int numInstructions, compulsory, count = 0, *RAM, *RAM2, buffer;
  OpCode opCode;
  CPUTimer ct;

  instructions =  readFile(argv[1], startingAddresses, &numProcesses,
    &numInstructions, &RAM, &RAM2, &compulsory);
  offset = startingAddresses[0];
  initializeNew();
  maxRAM = currentRAM = 0;
  ct.reset();
  CPU *cpu = new CPU();

  for(int i = 0; i < numInstructions; i++)
  {
    opCode = ADD;
    instruction = instructions[i];
    cpu->operation(opCode, instruction, buffer);
    if(opCode != ADD)
      count--; // allow for free cycle during instruction execution

    while(opCode != ADD)
    {
      count++;
      if(opCode == LOAD)
        buffer = RAM[(instruction.addr1 - offset)  >> 2];
      else  // STORE
        RAM[(instruction.addr1 - offset) >> 2] = buffer;

      cpu->operation(opCode, instruction, buffer);
    } // while opCode != ADD
  } // for each instruction

  opCode = DONE;
  cpu->operation(opCode, instruction, buffer);
  while(opCode != DONE)
  {
    count++;
    if(opCode == LOAD)
        buffer = RAM[(instruction.addr1 - offset) >> 2];
    else  // STORE
      if(opCode == STORE) // STORE
        RAM[(instruction.addr1 - offset) >> 2] = buffer;
      else
      {
        cout << "Request for ADD after DONE.\n";
        return 1;
      }

    cpu->operation(opCode, instruction, buffer);
  } // while opCode != DONE

  cout << "CPU time: " << ct.cur_CPUTime() << " Count: " << count - compulsory
    << " Compulsory: " << compulsory << " RAM: " << maxRAM <<  endl;

  if(argv[2][0] == '1')
    checkRAM(RAM, RAM2, (numProcesses + 1) * 250000, offset);

  delete [] instructions;
  delete [] RAM;
  delete [] RAM2;
  delete cpu;
  return 0;
}

