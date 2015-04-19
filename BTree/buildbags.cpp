#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;
int main()
{
   char filename[80];
   cout << "Filename: ";
   cin  >> filename;
   
   ofstream outf(filename);

    outf << 30  << ' ';
    outf << 55  << ' ';
    outf << 70  << ' ';
    outf << 80  << ' ';
    outf << 75  << ' ';
    outf << 77  << ' ';
    outf << 76  << ' ';

   outf.close();





}
