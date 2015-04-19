//Qiwei Li
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "CPUTimer.h"
#include "LinkedList.h"
#include "CursorList.h"
#include "StackAr.h"
#include "StackLi.h"
#include "QueueAr.h"
#include "SkipList.h"
#include "vector.h"
vector<CursorNode <int> > cursorSpace(250000);
using namespace std;

  int getChoice()
{
  int choice;
  cout << endl;
  cout << "      ADT Menu" << endl;
  cout << "0. Quit" <<endl;
  cout << "1. LinkedList" << endl;
  cout << "2. CursorList" << endl;
  cout << "3. StackAr" << endl;
  cout << "4. StackLi" << endl;
  cout << "5. QueueAr" << endl;
  cout << "6. SkipList" << endl;
  cout << "Your choice >> ";
  cin  >> choice;
  if (choice>0)
       return choice;
  else
      { cout<<"CPU time: 0" << endl;exit(0);}
}

void RunList(char *filename)
{
  List <int> list;
  ListItr <int> listItr = list.zeroth();
  ifstream inf(filename);
  char command, s[512];
  int value;
  inf.getline(s,512);
  while (inf >> command >> value)
 {
   if (command == 'i')
        list.insert(value, listItr);
   else
        list.remove(value);
 }
}

void RunCursorList(char *filename)
{       
  CursorList <int> list(cursorSpace);
  CursorListItr <int> listItr = list.zeroth();
  ifstream inf(filename);
  char command, s[512];
  int value;
  inf.getline(s,512);
  while (inf >> command >> value)
 {
   if (command == 'i')
        list.insert(value, listItr);
   else
        list.remove(value);
 }
}

void RunStackAr(char *filename)
{
  StackAr <int> stackar(250000);
  ifstream inf(filename);
  char command, s[512];
  int value;
  inf.getline(s,512);
  while (inf >> command >> value)
 {
   if (command == 'i')
        stackar.push(value);
   else
        stackar.pop();
 }
}

void RunStackLi(char *filename)
{
  StackLi <int> stackli;
  ifstream inf(filename);
  char command, s[512];
  int value;
  inf.getline(s,512);
  while (inf >> command >> value)
 {
   if (command == 'i')
        stackli.push(value);
   else
        stackli.pop();
 }
}

void RunQueueAr(char *filename)
{ 
  Queue <int> queue(250000);
  ifstream inf(filename);
  char command, s[512];
  int value;
  inf.getline(s,512);
  while (inf >> command >> value)
 {
   if (command == 'i')
        queue.enqueue(value);
   else
        queue.dequeue();
 }
}

void RunSkipList(char *filename)
{
  int Not_found=0;
  SkipList <int> skiplist(-1, 250000);
  ifstream inf(filename);
  char command, s[512];
  int value;
  inf.getline(s,512);
  while (inf >> command >> value)
 {
   if (command == 'i')
        skiplist.insert(value);
   else
        skiplist.deleteNode(value);
 }
}

int main()
{
  char filename[100];
  cout << "Filename >> ";
  cin >> filename;
  int choice;  
  CPUTimer ct;
 
  do
  {
     choice = getChoice();
     ct.reset();
     switch(choice)
     {
	case 1: RunList(filename); break;
	case 2: RunCursorList(filename); break;
	case 3: RunStackAr(filename); break; 
	case 4: RunStackLi(filename); break;
 	case 5: RunQueueAr(filename); break;
	case 6: RunSkipList(filename); break;
      }
	cout << "CPU time: " << ct.cur_CPUTime() << endl;	
  } while (choice > 0);
  
  if (choice ==0)
  {
    cout << "Your choice >> 0" << endl;
    cout << "CPU time: 0" << endl;
  } 
  else
     cout << endl;
}






