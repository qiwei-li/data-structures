#include <cstdlib>
#include <iostream>
#include <fstream>
#include "StackLi.h"
#include "QueueAr.h"

using namespace std;
typedef Queue<short>* Qptr;

int main(int argc, char *argv[])
{
  short value;

  Qptr myQptr =  new Queue<short> (atoi(argv[2])); 	
  Qptr outQptr = new Queue<short> (atoi(argv[2]));
  StackLi<Qptr> mystack;
  
  ifstream myfile(argv[1]);
  while(myfile >> value)
  {
    if(!myQptr->isFull())
    {
      myQptr->enqueue(value);       
    }  
    else
    {
      mystack.push(myQptr);
      myQptr = new Queue<short> (atoi(argv[2]));
      myQptr->enqueue(value);
    }  
  }
   
  if(!myQptr->isEmpty())
  {
   mystack.push(myQptr);
  }
 
  while(!mystack.isEmpty())
  {
    outQptr = mystack.top();
    mystack.pop();
    while(!outQptr->isEmpty())
    {  
      cout << outQptr->dequeue() << " ";
    }
  }
  cout << endl; 
}

                    
