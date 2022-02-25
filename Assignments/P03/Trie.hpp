#pragma once
// https://www.techiedelight.com/memory-efficient-trie-implementation-using-map-insert-search-delete/
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

class Trie
{
private:
    struct Node
    {
        bool isLeaf{false}; // true when the node is a leaf node

        unordered_map<char, Node *> map{unordered_map<char, Node *>()}; // each node stores a map to its child nodes

        Node();

        ~Node();

        bool hasChildren();
    };

    Node *root{nullptr};

    bool remove(Node *&curr, string key);

    void find_all(Node *&curr, string key, vector<string> &results);

public:
    Trie();

    ~Trie();

    bool empty();

    bool remove(string key);

    vector<string> find_all(string key);

    void insert(string str);

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

Trie::Node::Node() {}

Trie::Node::~Node()
{
    for (pair<const char, Node *> &it : this->map)
        delete it.second;
}

bool Trie::Node::hasChildren()
{
    for (pair<const char, Node *> &it : this->map)
    {
        if (it.second != nullptr)
            return true;
    }
    return false;
}

bool Trie::remove(Node *&curr, string key)
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
            if (!(curr->hasChildren()))
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
        if (!(curr->hasChildren()))
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

void Trie::find_all(Node *&curr, string key, vector<string> &results)
{
    if (curr->isLeaf)
        results.push_back(key);

    for (pair<const char, Node *> &it : curr->map)
    {
        if (it.second)
        {
            find_all(it.second, key + it.first, results);
        }
    }
}

Trie::Trie() {}

Trie::~Trie() { delete root; }

bool Trie::empty() { return root == nullptr; }

bool Trie::remove(string key) { return remove(root, key); }

vector<string> Trie::find_all(string key)
{
    Node *curr = root;
    vector<string> results;

    for (char i : key)
    {
        curr = curr->map[i]; // go to next node
    }

    for(auto it = key.begin(); it != key.end(); it++)
    {
        
    }

    find_all(curr, key, results);
    return results;
}

void Trie::insert(string str)
{
    if (this->empty())
    {
        root = new Node;
    }

    // start from the root node
    Node *curr = root;

    for (const char &i : str)
    {
        if (curr->map.find(i) == curr->map.end())
            curr->map[i] = new Node;

        curr = curr->map[i];
    }

    // mark the current node as a leaf
    curr->isLeaf = true;
}