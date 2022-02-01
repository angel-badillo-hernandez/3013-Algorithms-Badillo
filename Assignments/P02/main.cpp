#include <iostream>
#include <fstream>
#include <string>
#include "List.hpp"
using namespace std;

int main()
{
  ifstream infile;
  List L;
  infile.open("dictionary.txt");
  string val;
  
  while(infile >> val)
  {
    L.pushRear(val);
  }
  
  return 0;
}
