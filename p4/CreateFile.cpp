#include <iostream>
#include<fstream>
#include<cstdlib>
#include<cstdio>

#define INSTR_PER_PROCESS 100000
#define NUMBER_OF_PROCESSES 10

using namespace std;

void randomProcess(ofstream &outf, int num_instructions)
{
  unsigned short address;

  for(int i = 0; i < num_instructions; i++)
  {
    for(int j = 0; j < 3; j++)
    {
      address = rand() & 0xFFFF;
      outf.write((char*) & address, sizeof(unsigned short));
    }  // for each address within an instruction
  } // for each instruction
} // randomProcess



void setStartingAddresses(ofstream &outf)
{
  unsigned short processes = NUMBER_OF_PROCESSES;
  outf.write((char*) &processes, sizeof(unsigned short));
  unsigned startingAddress = ((rand() & 0xFFFF) * (rand() & 0xFFFF)) & 0xFFFFFFC;
  for(int i = 0; i < NUMBER_OF_PROCESSES; i++)
  {
    outf.write((char*) &startingAddress, sizeof(unsigned));
    startingAddress += (rand() & 0xFFFC) + 0x100000;
    // processes separated by at least one million bytes
  }  // for each process
} // setStartingAddresses()

void localityProcess(ofstream &outf, int num_instructions)
{
  unsigned short address, currentAddress = rand() & 0xFFFF;

  for(int i = 0; i < num_instructions; i++)
  {
    for(int j = 0; j < 3; j++)
    {
      address = currentAddress + (rand() &  0x3FF);  // 1024 location window
      outf.write((char*) &address, sizeof(unsigned short));
    } // for each address in instruction

    currentAddress += 2;  // move generally forward
  } // for each instruction

} // randomProcess

int main()
{
  int seed;
  unsigned process_instructions, total, instructions = 0;
  char filename[80], process;

  cout << "Total number of instructions> ";
  cin >> total;
  cout << "Seed> ";
  cin >> seed;
  srand(seed);
  sprintf(filename, "cpu-%d-%d.dat", total, seed);
  ofstream outf(filename, ios::binary);
  outf.write((char*) &total, sizeof(int));
  setStartingAddresses(outf);

  while(instructions < total)
  {
    process_instructions = (rand() & 0xff) + INSTR_PER_PROCESS;
    if(process_instructions  + instructions > total)
      process_instructions = total - instructions;
    process = (char)(rand() % NUMBER_OF_PROCESSES);
    outf.write(&process, sizeof(char));
    outf.write((char*) &process_instructions, sizeof(unsigned));
    if(process == 0)
      randomProcess(outf, process_instructions);
    else
      localityProcess(outf, process_instructions);

    instructions += process_instructions;
  } // while more instructions to be written

  outf.close();
  return 0;
}
//---------------------------------------------------------------------------
