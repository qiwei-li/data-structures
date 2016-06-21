//Authors: Qiwei Li, Jiaping Zhang
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
    cout<<"array reads: "<<arr<<"\n"; //test
    for(int i=0; i<256; ++i)
    {
      if(arr[i]=='\0')
        break;
      else if(arr[i]=='[' || arr[i]=='{' || arr[i]=='(' || (arr[i]=='/' && arr[i+1]=='*'))
      {
        cout<<"Detected: "<<arr[i]<<"\n"; //test
        mystack.push(arr[i]);
        myline.push(line_num);
        cout<<"Pushed. Char: "<<mystack.top()<<" Line: "<<myline.top()<<'\n'; //test
      }
      else if(arr[i]==']' || arr[i]==')' || arr[i]=='}' || (arr[i]=='*' && arr[i+1]=='/'))
      {
        cout<<"Detected: "<<arr[i]<<'\n'; //test
        if(mystack.isEmpty())
        {
          cout<<"Stack is empty.\n"; //test
          if(arr[i]=='*')
            cout << "Unmatched t*/ on line #"   << line_num << "\n";
          else
            cout << "Unmatched " << arr[i] << line_num << "\n";
        }
        else if(arr[i]==']')
        {
          cout<<"Detected: "<<arr[i]<<" Top is"<<mystack.top()<<"\n"; //test
          if(mystack.topAndPop() != '[')
          {
            cout<<"Not Cors\n"; //test
            cout << "Unmatched " << arr[i] << " on line #" << line_num << "\n";
            myline.pop();
          }
        }
        else if(arr[i]=='}')
        {
          cout<<"Detected: "<<arr[i]<<" Top is"<<mystack.top()<<"\n"; //test
          if(mystack.topAndPop() != '{')
          {
            cout<<"Not Cors\n";
            cout << "Unmatched " << arr[i] << " on line #" << line_num << "\n";
            myline.pop();
          }
        }
        else if(arr[i]==')')
        {
          cout<<"Detected: "<<arr[i]<<" Top is"<<mystack.top()<<"\n";
          if(mystack.topAndPop() != '(')
          {
            cout<<"Not Cors\n";
            cout << "Unmatched " << arr[i] << " on line #" << line_num << "\n";
            myline.pop();          
          }
        }
        else //need to ignore comments here
        { 
          cout<<"1.Detected: "<<arr[i]<<" Top is"<<mystack.top()<<"\n";
          if(mystack.topAndPop() != '/')
          {
            cout<<"top is not Cors\n";
            myline.pop();
            cout<<"Going prev\n";
            while(!mystack.isEmpty())
            {
              cout<<"mystack is not empty yet\n";
              cout<<"checking "<< arr[i]<<" Top is"<<mystack.top()<<"\n";
              if(mystack.topAndPop()== '/')
              {
                cout<<"find!\n";
                myline.pop();
                break;
              }
              else
                myline.pop();
            }
            if(mystack.isEmpty())
              cout << "empty! Unmatched tt*/ on line#" << line_num << "\n";
            else
              cout << "not empty yet\n";
          }
        }
      }//end the else ifright bracket
      else
      {
        cout<<"something dangerous\n"; 
      }    
    } //end of iteriating arr 0-256
  line_num++;  
  }
  cout<<"out of while\n";
  if(!mystack.isEmpty())
  {
    if(mystack.top()=='/')
      cout << "Unmatched t/* on line #" << myline.topAndPop() << "\n";
    else
      cout << "Unmatched " << mystack.topAndPop() << " on line #" << myline.topAndPop() << "\n";
  }
  else
   cout << "OK\n";
}
