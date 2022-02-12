#include <iostream>
#include "Trie.hpp"

using namespace std;

// C++ implementation of Trie data structure
int main()
{
    Trie tree;

    tree.insert("fortnite");
    cout << tree.search("fortnite");
 
    return 0;
}