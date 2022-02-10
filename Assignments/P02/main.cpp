#include <iostream>
#include <fstream>
#include <string>
#include "List.hpp"
using namespace std;

int main()
{
  List L;
  L.resize(10, "string");

  L = {"1", "2", "3"};

  cout << L;
}
