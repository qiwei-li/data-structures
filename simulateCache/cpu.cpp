#include "cpu.h"

CPU::CPU()
{
  arrSize=5323;
  state=0; tempAddr1=0; mybuffer1=0; mybuffer2=0; 
  index1=0; index2=0; index3=0;
  lastloop=0;
  arr = new cacheline [arrSize];
} // CPU()


void CPU::operation(OpCode &opCode, Instruction &instruction, int &buffer)
{
  switch (opCode)
  {
    case ADD  :
      state = 1;
      index1 = instruction.addr1 % arrSize;
      if(arr[index1].isFull == 0)
      { opCode = LOAD; break;}
      else if(arr[index1].tag == instruction.addr1)
      { mybuffer1 = arr[index1].value; state = 2;}
      else //conflict for addr1
      {
        if(arr[index1].isDirty == 0)
        { opCode = LOAD; break;}
        else
        {
          tempAddr1 = instruction.addr1;
          instruction.addr1 = arr[index1].tag;
          buffer = arr[index1].value;
          opCode = STORE; 
          break;
        }
      } 
        
      index2 = instruction.addr2 % arrSize;
      instruction.addr1 = instruction.addr2;
      if(arr[index2].isFull == 0)
      { opCode = LOAD; break;}
      else if(arr[index2].tag == instruction.addr2)
      { mybuffer2 = arr[index2].value; state = 3;}
      else //conflict for addr2
      {
        if(arr[index2].isDirty == 0)
        { opCode = LOAD; break;}
        else
        { 
          tempAddr1 = instruction.addr1;
          instruction.addr1 = arr[index2].tag;
          buffer = arr[index2].value; 
          opCode = STORE; 
          break;
        }
      }

      index3 = instruction.addr3 % arrSize;
      instruction.addr1 = instruction.addr3;
      if(arr[index3].isFull == 0)
      {
        arr[index3].isFull = 1;
        arr[index3].isDirty = 1;
        arr[index3].tag = instruction.addr3;
        arr[index3].value = mybuffer1 + mybuffer2;
      }
      else if(arr[index3].tag == instruction.addr3)
      {
        arr[index3].isDirty = 1;
        arr[index3].value = mybuffer1 + mybuffer2;
      }
      else //conflict for addr3
      {
        if(arr[index3].isDirty == 0)
        { opCode = LOAD; break; }
        else
        { 
          tempAddr1 = instruction.addr1;
          instruction.addr1 = arr[index3].tag;
          buffer = arr[index3].value;
          opCode = STORE; 
          break;       
        }
      }
      opCode = ADD;
      break; // *addr3 = *addr1 + *addr2
    
    case LOAD :  
      if( state == 1)
      {
        arr[index1].isFull = 1;
        arr[index1].isDirty = 0;
        arr[index1].tag = instruction.addr1;
        arr[index1].value = buffer;
        mybuffer1 = buffer;

        state = 2;
        instruction.addr1 = instruction.addr2;
        index2 = instruction.addr2 % arrSize;
        if(arr[index2].isFull == 0)
        { opCode = LOAD; break;}
        else if(arr[index2].tag == instruction.addr2)
        {
          mybuffer2 = arr[index2].value;
          state = 3;
        }
        else //conflict for addr2
        {
          if(arr[index2].isDirty == 0)
          { opCode = LOAD; break;}
          else
          { 
            tempAddr1 = instruction.addr1;
            instruction.addr1 = arr[index2].tag;
            buffer = arr[index2].value;
            opCode = STORE; 
            break;
          }
        }
        
        index3 = instruction.addr3 % arrSize;
        instruction.addr1 = instruction.addr3;
        if(arr[index3].isFull == 0)
        {
          arr[index3].isFull = 1;
          arr[index3].isDirty = 1;
          arr[index3].tag = instruction.addr3;
          arr[index3].value = mybuffer1 + mybuffer2;
          opCode = ADD;
          break;
        }
        else if(arr[index3].tag == instruction.addr3)
        {
          arr[index3].isDirty = 1;
          arr[index3].value = mybuffer1 + mybuffer2;
        }
        else //conflict for addr3
        {
          if(arr[index3].isDirty == 0)
          { opCode = LOAD; break; }
          else
          { 
            tempAddr1 = instruction.addr1;
            instruction.addr1 = arr[index3].tag;
            buffer = arr[index3].value; 
            opCode = STORE; 
            break; 
          }
        }
        opCode = ADD;
        break;
      }

      if(state == 2)
      {
        arr[index2].isFull = 1;
        arr[index2].isDirty = 0;
        arr[index2].tag = instruction.addr2;
        arr[index2].value = buffer;
        mybuffer2 = buffer;
       
        state = 3;
        index3 = instruction.addr3 % arrSize;
        instruction.addr1 = instruction.addr3;
        if(arr[index3].isFull == 0)
        {
          arr[index3].isFull = 1;
          arr[index3].isDirty = 1;
          arr[index3].tag = instruction.addr3;
          arr[index3].value = mybuffer1 + mybuffer2;
        }
        else if(arr[index3].tag == instruction.addr3)
        {
          arr[index3].isDirty = 1;
          arr[index3].value = mybuffer1 + mybuffer2;
        }
        else //conflict for addr3
        {
          if(arr[index3].isDirty == 0)
          { opCode = LOAD; break; }
          else
          { 
            tempAddr1 = instruction.addr1;
            instruction.addr1 = arr[index3].tag;
            buffer = arr[index3].value; 
            opCode = STORE; 
            break; 
          }
        }
        opCode = ADD;
        break;
      }
 
      if(state == 3)
      {
        arr[index3].isFull = 1;
        arr[index3].isDirty = 1;
        arr[index3].tag = instruction.addr3;
        arr[index3].value = mybuffer1+mybuffer2;
        opCode = ADD; break; 
       }// buffer contains int requested from RAM
    
    case STORE:  
      if(state == 1)
      { 
        instruction.addr1 = tempAddr1; 
        opCode = LOAD; 
        break; 
      }

      if(state == 2)
      { opCode = LOAD; instruction.addr1 = instruction.addr2; break; }
 
      if(state == 3)
      { opCode = LOAD; instruction.addr1 = instruction.addr3; break; }      

      if(state == 4)
      {
        lastloop=lastloop+1; 
        while(lastloop < arrSize)
        {
          if(arr[lastloop].isDirty != 0)
          {
            instruction.addr1 = arr[lastloop].tag;
            buffer = arr[lastloop].value;
            arr[lastloop].isDirty=0;
            break;
          }
          else
            lastloop++;
        }
        if(lastloop>=arrSize)
          { opCode=DONE; break;}
      }
      break; // Sent by RAM after a STORE
    
    case DONE :
      state = 4;
      while(lastloop < arrSize)
      {
        if(arr[lastloop].isDirty != 0)
        {
          instruction.addr1 = arr[lastloop].tag;
          buffer = arr[lastloop].value;
          opCode = STORE;
          break;
        }
        else
        {
          lastloop++;
        }
      }
      break;  //  All ADDs in file have been sent.  Time to STORE dirty cache.
  } // switch
} // operation()



