#include <iostream>
#include <string>
#include <fstream>
#include "Trie.hpp"

using namespace std;

void load_trie(Trie &tree, string file_name);

// C++ implementation of Trie data structure
int main()
{
    Trie tree;
    string k = "E";
    tree.insert({"E", "F", "H", "Eren", "El"});
    tree.remove(k);
    cout << k;
    
}

void load_trie(Trie &tree, string file_name)
{
    ifstream fin; // file to get animal names
    string x;
    fin.open(file_name); // open file for reading

    while (fin >> x)
    {
        for (char &c : x)
        {
            c = toupper(c);
        }
        tree.insert(x);
    }
    fin.close();
}
