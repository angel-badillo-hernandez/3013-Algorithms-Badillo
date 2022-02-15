#pragma once
// https://www.techiedelight.com/memory-efficient-trie-implementation-using-map-insert-search-delete/
#include <iostream>
#include <unordered_map>
using namespace std;

// Data structure to store a Trie node
struct Node
{
    // true when the node is a leaf node
    bool isLeaf{false};

    // each node stores a map to its child nodes
    unordered_map<char, Node *> map{unordered_map<char, Node *>()};

    Node() {}
};

class Trie
{
private:
    Node *root{nullptr};

    // Returns true if the given node has any children
    bool haveChildren(Node const *curr)
    {
        // don't use `(curr->map).size()` to check for children

        for (auto it : curr->map)
        {
            if (it.second != nullptr)
            {
                return true;
            }
        }

        return false;
    }

    // Recursive function to delete a string from a Trie
    bool deletion(Node *&curr, char *str)
    {
        // return if Trie is empty
        if (curr == nullptr)
        {
            return false;
        }

        // if the end of the string is not reached
        if (*str)
        {
            // recur for the node corresponding to the next character in
            // the string and if it returns true, delete the current node
            // (if it is non-leaf)
            if (curr != nullptr && curr->map.find(*str) != curr->map.end() &&
                deletion(curr->map[*str], str + 1) && curr->isLeaf == false)
            {
                if (!haveChildren(curr))
                {
                    delete curr;
                    curr = nullptr;
                    return true;
                }
                else
                {
                    return false;
                }
            }
        }

        // if the end of the string is reached
        if (*str == '\0' && curr->isLeaf)
        {
            // if the current node is a leaf node and doesn't have any children
            if (!haveChildren(curr))
            {
                delete curr; // delete the current node
                curr = nullptr;
                return true; // delete the non-leaf parent nodes
            }

            // if the current node is a leaf node and has children
            else
            {
                // mark the current node as a non-leaf node (DON'T DELETE IT)
                curr->isLeaf = false;
                return false; // don't delete its parent nodes
            }
        }

        return false;
    }

public:
    Trie() {}
    ~Trie() {}

    // Iterative function to insert a string into a Trie
    void insert(string str)
    {
        if (root == nullptr)
        {
            root = new Node;
        }

        // start from the root node
        Node *curr = root;

        for (char i : str)
        {
            if (curr->map.find(i) == curr->map.end())
            {
                curr->map[i] = new Node;
            }
            curr = curr->map[i];
        }

        // mark the current node as a leaf
        curr->isLeaf = true;
    }
    // Iterative function to search a string in a Trie. It returns true
    // if the string is found in the Trie; otherwise, it returns false.
    bool search(string str)
    {
        if (root == nullptr)
            return false;

        Node *curr = root;

        for (char i : str)
        {
            curr = curr->map[i];

            if (curr == nullptr)
                return false;
        }

        // return true if the current node is a leaf and the
        // end of the string is reached
        return curr->isLeaf;
    }
};