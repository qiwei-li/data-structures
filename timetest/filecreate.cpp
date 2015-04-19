#include <cstdlib>
#include <fstream>
#include <iostream>

using namespace std;

int main()
{

   cout << "File creation program \n";
   ofstream outf("File1.dat");
   outf << "Has a series of 250,000 insertions in order from 1 to 250000\n";

   for(int i = 1; i <= 250000; i++)
   	outf << "i" << i << " ";
   outf.close();

   outf.open("File2.dat");
   outf << "Has a series of 125,000 insertions in order from 1 to 125000 followed by 125,000 deletions 1 to 125000\n";

   for(int i = 1; i <= 125000; i++)
     outf << "i" << i << " ";
   for(int i = 1; i <= 125000; i++)
   	outf << "d" << i << " ";
   outf.close();

   outf.open("File3.dat");
   outf << "Has a series of 125,000 insertions in order from 1 to 125000 followed by 125,000 deletions 125000 to 1\n";

   for(int i = 1; i <= 125000; i++)
        outf << "i" << i << " ";
   for(int i = 125000; i >= 1; i--)
        outf << "d" << i << " ";
   outf.close();

   outf.open("File4.dat");
   outf << "Has a series of 125000 random, unique insertions from 1 to 125000 followed by 125000 random, unique deletions\n";
   srand(1);
   int *nums = new int[125000];
   for(int i = 1; i <= 125000; i++)
     nums[i - 1] = i;

   for(int i = 125000; i >= 1; i--)
   {
     int pos = rand() % i; 
     outf << "i" << nums[pos] << " ";
     nums[pos] = nums[i - 1];
   } // for i

   for(int i = 1; i <= 125000; i++)
     nums[i - 1] = i;

   for(int i = 125000; i >= 1; i--)
   {
     int pos = rand() % i;
     outf << "d" << nums[pos] << " ";
     nums[pos] = nums[i - 1];
   } // for i

   outf.close();

  outf.open("File5.dat");
   outf << "Has a series of 125,000 random, unique insertions from 1 to 125,000 followed by 1250000 deletions 1 to 125000\n";
   srand(1);
   for(int i = 1; i <= 125000; i++)
     nums[i - 1] = i;

   for(int i = 125000; i >= 1; i--)
   {
     int pos = rand() % i;
     outf << "i" << nums[pos] << " ";
     nums[pos] = nums[i - 1];
   } // for i

   for(int i = 1; i <= 125000; i++)
        outf << "d" << i << " ";

   outf.close();
  return 1;
}


