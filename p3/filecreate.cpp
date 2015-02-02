#include <cstdlib>
#include <fstream>
#include <iostream>

using namespace std;

int main()
{

   cout << "File creation program \n";
   ofstream outf("File1L.dat");
   outf << "Has a series of 1000000 insertions in order from 0 to 1000000\n";
   for(int i = 0; i < 1000000; i++)
   	outf << "i" << i << " ";
   outf.close();

   outf.open("File2L.dat");
   outf << "Has a series of 500000 insertions in order from 0 to 4999999 followed by 500000 deletions 0 to 4999999\n";
   for(int i = 0; i < 500000; i++)
   	outf << "i" << i << " ";
   for(int i = 0; i < 500000; i++)
   	outf << "d" << i << " ";
   outf.close();

   outf.open("File3L.dat");
   outf << "Has a series of 500000 insertions in order from 0 to 499999 followed by 500000 deletions 499999 to 0\n";
   for(int i = 0; i < 500000; i++)
        outf << "i" << i << " ";
   for(int i = 499999; i >= 0; i--)
        outf << "d" << i << " ";
   outf.close();

   outf.open("File4L.dat");
   outf << "Has a series of 500000 random, unique insertions from 0 to 499999 followed by 500000 random, unique deletions\n";
   srand(1);
   int *nums = new int[500000];
   for(int i = 0; i < 500000; i++)
     nums[i] = i;

   for(int i = 500000; i > 0; i--)
   {
     int pos = rand() % i; 
     outf << "i" << nums[pos] << " ";
     nums[pos] = nums[i - 1];
   } // for i

   for(int i = 0; i < 500000; i++)
     nums[i] = i;

   for(int i = 500000; i > 0; i--)
   {
     int pos = rand() % i;
     outf << "d" << nums[pos] << " ";
     nums[pos] = nums[i - 1];
   } // for i

   outf.close();

  outf.open("File5L.dat");
   outf << "Has a series of 500000 random, unique insertions from 0 to 499999 followdy by 500000 deletions 0 to 500000\n";
   srand(1);
   for(int i = 0; i < 500000; i++)
     nums[i] = i;

   for(int i = 500000; i > 0; i--)
   {
     int pos = rand() % i;
     outf << "i" << nums[pos] << " ";
     nums[pos] = nums[i - 1];
   } // for i

   for(int i = 0; i < 500000; i++)
        outf << "d" << i << " ";

   outf.close();
  return 0;
}


