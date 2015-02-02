#include "CPUTimer.h"
#include <fstream>
#include "LinkedList.h"
#include "StackAr.h"
#include "StackLi.h"
#include "QueueAr.h"
#include "SkipList.h"
#include "BinarySearchTree.h"
#include "AvlTree.h"
#include "SplayTree.h"
#include "BTree.h"
#include "SeparateChaining.h"
#include "QuadraticProbing.h"
#include "BinaryHeap.h"
#include "CursorList2.h"
#include "QuadraticProbingPtr.h"
using namespace std;

CPUTimer ct;
vector<CursorNode<int> > cursorSpace(1000001);

int getChoice(int *size, int *M, int *L)
{
  int choice;
  do{
    cout << "\n      ADT Menu\n0. Quit\n1.  LinkedList\n";
    cout << "2.  CursorList\n3.  StackAr\n";
    cout << "4.  StackLi\n5.  QueueAr\n6.  Skip List\n";
    cout << "7.  Binary Search Tree\n8.  AVL Tree\n";
    cout << "9.  Splay Tree\n10. BTree\n11. Separate Chaining Hash\n";
    cout << "12. Quadratic Probing Hash\n13. Binary Heap\n";
    cout << "14. Quadratic Probing Pointer Hash\n";
    cout << "Your choice >> ";
    cin >> choice;
    if(choice < 0 || choice > 16)
      cout << "Your choice is not between 1 and 16.\nPlease try again.\n";
  } while (choice < 0 || choice > 16);

  if(choice == 10)
  {
    cout << "Please enter M for the BTree >> ";
    cin >> *M;
    cout << "Please enter L for the BTree >> ";
    cin >> *L;
  }

  if(choice == 11 || choice == 12 || choice == 14)
  {
  	cout << "Please enter the size of the hash table >> ";
    cin >> *size;
  }

  return choice;
} // getChoice()


void RunList(char *filename)
{
  List <int> list;
  ListItr <int> listItr = list.zeroth();
  ifstream inf(filename);
  char command, s[512];
  int i;

  inf.getline(s,512);

  while(inf >> command)
  {
    inf >> i;
    if (command == 'i')
    	list.insert(i,listItr);
		else
			list.remove(i);
  } //while
} // RunList()


void RunCursorList(char *filename)
{
  CursorList <int> list(cursorSpace);
  CursorListItr <int> listItr = list.zeroth();
  ifstream inf(filename);
  char command, s[512];
  int i;

  inf.getline(s,512);

  while(inf >> command)
  {
    inf >> i;
    if (command == 'i')
      list.insert(i,listItr);
    else
      list.remove(i);
  } //while

} // RunCursorList()



void RunStackAr(char *filename)
{
  StackAr <int> stack(1000001);
  ifstream inf(filename);
  char command, s[512];
  int i;

  inf.getline(s,512);

  while(inf >> command)
  {
    inf >> i;
    if (command == 'i')
    	stack.push(i);
		else
			stack.pop();
  } //while

} // RunStackAr()



void RunStackLi(char *filename)
{
  StackLi <int> stack;
  ifstream inf(filename);
  char command, s[512];
  int i;

  inf.getline(s,512);

  while(inf >> command)
  {
    inf >> i;
    if (command == 'i')
    	stack.push(i);
		else
			stack.pop();
  } //while
}  // RunStackLi()


void RunQueueAr(char *filename)
{
  Queue <int> queue(1000001);
  ifstream inf(filename);
  char command, s[512];
  int i;

  inf.getline(s,512);

 while(inf >> command)
  {
    inf >> i;
    if (command == 'i')
    	queue.enqueue(i);
		else
			queue.dequeue();
  } //while
} // RunQueueAr()



void RunSkipList(char *filename)
{
  SkipList <int> list(0, 250001);
  ifstream inf(filename);
  char command, s[512];
  int i;

  inf.getline(s,512);

  while(inf >> command)
  {
    inf >> i;
    if (command == 'i')
        list.insert(i);
                else
                        list.deleteNode(i);
  } //while
} // RunList()


void RunBST(char *filename)
{
  BinarySearchTree <int> tree(-1);
  ifstream inf(filename);
  char command, s[512];
  int i;

  inf.getline(s,512);

 while(inf >> command)
  {
    inf >> i;
    if (command == 'i')
    	tree.insert(i);
		else
			tree.remove(i);
  } //while
} // RunBST()

void RunAVL(char *filename)
{
  AvlTree <int> tree(-1);
  ifstream inf(filename);
  char command, s[512];
  int i;

  inf.getline(s,512);

 while(inf >> command)
  {
    inf >> i;
    if (command == 'i')
    	tree.insert(i);
		else
			tree.remove(i);
  } //while
} // RunAVL()


void RunSplay(char *filename)
{
  SplayTree <int> tree(-1);
  ifstream inf(filename);
  char command, s[512];
  int i;

  inf.getline(s,512);

 while(inf >> command)
  {
    inf >> i;
    if (command == 'i')
    	tree.insert(i);
		else
			tree.remove(i);
  } //while
} // RunSplay()


void RunBTree(char *filename, int M, int L)
{
  BTree tree(M, L);
  ifstream inf(filename);
  char command, s[512];
  int i;

  inf.getline(s,512);

 while(inf >> command)
  {
    inf >> i;
    if (command == 'i')
    	tree.insert(i);
		else
			tree.remove(i);
  } //while
} // RunBTree()


void RunSeparateChaining(char *filename, int size)
{
  ChainingHashTable <int> hashTable(-1, size);
  ct.reset();
  ifstream inf(filename);
  char command, s[512];
  int i;

  inf.getline(s,512);

 while(inf >> command)
  {
    inf >> i;
    if (command == 'i')
    	hashTable.insert(i);
		else
			hashTable.remove(i);
  } //while
} // RunSeparateChaining()


void RunQuadraticProbing(char *filename, int size)
{
  QuadraticHashTable <int> hashTable(-1, size);
  ct.reset();
  ifstream inf(filename);
  char command, s[512];
  int i;

  inf.getline(s,512);

 while(inf >> command)
  {
    inf >> i;
    if (command == 'i')
    	hashTable.insert(i);
		else
			hashTable.remove(i);
  } //while
} // RunQuadraticProbing

void RunBinaryHeap(char *filename)
{
	BinaryHeap <int> heap(1000001);
  ifstream inf(filename);
  char command, s[512];
  int i;

  inf.getline(s,512);

 while(inf >> command)
  {
    inf >> i;
    if (command == 'i')
    	heap.insert(i);
		else
			heap.deleteMin();
  } //while
} // RunBinaryHeap()


void RunQuadraticProbingPtr(char *filename, int size)
{
  QuadraticPtrHashTable <int> hashTable(-1, size);
  ct.reset();
  ifstream inf(filename);
  char command, s[512];
  int i;

  inf.getline(s,512);

 while(inf >> command)
  {
    inf >> i;
    if (command == 'i')
      hashTable.insert(i);
    else
      hashTable.remove(i);
  } //while
} // RunQuadraticProbing


int main(){
  char filename[80];
  int choice, size, M, L;


  cout << "Filename >> ";
  cin >> filename;

  do
  {
    choice = getChoice(&size, &M, &L);
    ct.reset();

    switch (choice)
    {
      case 1: RunList(filename); break;
      case 2: RunCursorList(filename); break;
      case 3: RunStackAr(filename); break;
      case 4: RunStackLi(filename); break;
      case 5: RunQueueAr(filename); break;
      case 6: RunSkipList(filename); break;
      case 7: RunBST(filename); break;
      case 8: RunAVL(filename); break;
      case 9: RunSplay(filename); break;
      case 10: RunBTree(filename, M, L); break;
      case 11: RunSeparateChaining(filename, size); break;
      case 12: RunQuadraticProbing(filename, size); break;
      case 13: RunBinaryHeap(filename); break;
      case 14: RunQuadraticProbingPtr(filename, size); break;
    }

    cout << "CPU time: " << ct.cur_CPUTime() << endl;
  } while(choice > 0);

  return 0;
}  // main()

