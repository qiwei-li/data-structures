//Authors: Qiwei Li, Jiaping Zhang
#include <cstdlib>
#include <iostream>
#include <fstream>
#include "StackLi.h"

using namespace std;

int main(int argc, char *argv[])
{
  StackLi<char> mystack;
  StackLi<int> myline;
  char arr[256];
  int line_num = 1;

  ifstream myfile(argv[1]);
  while(myfile.getline(arr, sizeof(myfile)))
  {
    for(int i=0; i<256; ++i)
    {
      if(arr[i]=='\0')
        break;
      else if(arr[i]=='[' || arr[i]=='{' || arr[i]=='(' || (arr[i]=='/' && arr[i+1]=='*'))
      {
        mystack.push(arr[i]);
        myline.push(line_num);
      }
      else if(arr[i]==']' || arr[i]=='}' || arr[i]==')' || (arr[i]=='*' && arr[i+1]=='/'))
      {
        if(mystack.isEmpty())
        {
          if(arr[i]=='*')
          {
            cout << "Unmatched */ on line #"   << line_num << "\n";
            exit(0);
          }
          {
            cout << "Unmatched " << arr[i] << " on line #" << line_num << "\n";
            exit(0);
          }
        }
        else if(arr[i]==']')
        {
          if(mystack.topAndPop() != '[')
          {
            cout << "Unmatched " << arr[i] << " on line #" << line_num << "\n";
            myline.pop();
            exit(0);
          }
        }
        else if(arr[i]=='}')
        {
          if(mystack.topAndPop() != '{')
          {
            cout << "Unmatched " << arr[i] << " on line #" << line_num << "\n";
            myline.pop();
            exit(0);
          }
        }
        else if(arr[i]==')')
        {
          if(mystack.topAndPop() != '(')
          {
            cout << "Unmatched " << arr[i] << " on line #" << line_num << "\n";
            myline.pop();
            exit(0);          
          }
        }
        else //need to ignore comments here
        { 
          if(mystack.topAndPop() != '/')
          {
            myline.pop();
            while(!mystack.isEmpty())
            {
              if(mystack.topAndPop()== '/')
              {
                myline.pop();
                break;
              }
              else
                myline.pop();
            }
            if(mystack.isEmpty())
            {
              cout << "Unmatched */ on line #" << line_num << "\n";
              exit(0);
            }
          }
        }
      }//end the else ifright bracket    
    } //end of iteriating arr 0-256
  line_num++;  
  }
  if(!mystack.isEmpty())
  {
    if(mystack.top()=='/')
    {
      cout << "Unmatched /*  on line #" << myline.topAndPop() << "\n";
      exit(0);    
    }
    else
    {
      cout << "Unmatched " << mystack.topAndPop() << " on line #" << myline.topAndPop() << "\n";
      exit(0);
    }
  }
  else
  {
   cout << "OK\n";
   exit(0);
  }
}
