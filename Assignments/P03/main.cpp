#include <iostream>
#include <string>
#include <fstream>
#include "Trie.hpp"

using namespace std;

// C++ implementation of Trie data structure
int main()
{
    Trie tree;
    string x;

    ifstream infile("dictionary.txt");

    while (infile >> x)
    {
        tree.insert(x);
    }
    
    cout << tree.search("llama");
    return 0;
}