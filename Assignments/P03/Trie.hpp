#pragma once
// https://www.techiedelight.com/memory-efficient-trie-implementation-using-map-insert-search-delete/
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

// Data structure to store a Trie node
struct Node
{
    // true when the node is a leaf node
    bool isLeaf{false};

    // each node stores a map to its child nodes
    unordered_map<char, Node *> map{unordered_map<char, Node *>()};

    Node() {}

    ~Node()
    {
        for (pair<char, Node *> it : this->map)
        {
            delete it.second;
        }
    }

    // Returns true if the given node has any children
    bool haveChildren()
    {
        // don't use `(curr->map).size()` to check for children

        for (pair<char, Node *> it : this->map)
        {
            if (it.second != nullptr)
            {
                return true;
            }
        }

        return false;
    }
};

class Trie
{
private:
    Node *root{nullptr};

    bool remove(Node *&curr, string key)
    {

        // return if Trie is empty
        if (curr == nullptr)
        {
            return false;
        }

        // if the end of the key is not reached
        if (key.length())
        {
            // recur for the node corresponding to the next character in the key
            // and if it returns true, delete the current node (if it is non-leaf)

            if (curr != nullptr && curr->map.find(key[0]) != curr->map.end() &&
                remove(curr->map[key[0]], key.substr(1)) && curr->isLeaf == false)
            {
                if (!(curr->haveChildren()))
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

        // if the end of the key is reached
        if (key.length() == 0 && curr->isLeaf)
        {
            // if the current node is a leaf node and doesn't have any children
            if (!(curr->haveChildren()))
            {
                // delete the current node
                delete curr;
                curr = nullptr;

                // delete the non-leaf parent nodes
                return true;
            }

            // if the current node is a leaf node and has children
            else
            {
                // mark the current node as a non-leaf node (DON'T DELETE IT)
                curr->isLeaf = false;

                // don't delete its parent nodes
                return false;
            }
        }

        return false;
    }

    void find_all(Node *&curr, string key, vector<string> &results)
    {

        if (curr->isLeaf)
        {
            results.push_back(key);
        }

        for (pair<const char, Node *> &it : curr->map)
        {
            if (it.second)
            {
                find_all(it.second, key + it.first, results);
            }
        }
    }

public:
    Trie() {}
    ~Trie()
    {
        delete root;
    }

    bool remove(string key)
    {
        return remove(root, key);
    }
    
    vector<string> find_all(string key)
    {
        Node *curr = root;
        vector<string> results;

        for (char &i : key)
        {
            // go to next node
            curr = curr->map[i];
        }

        find_all(curr, key, results);
        return results;
    }

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