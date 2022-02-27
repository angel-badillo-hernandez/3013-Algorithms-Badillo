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

    size_t trie_size{0};

    bool remove(Node *&curr, string key);

    void find_all(Node *&curr, string key, vector<string> &results);

public:
    Trie();

    ~Trie();

    bool empty();

    size_t size();

    void remove(string key);

    vector<string> find_all(string key);

    void insert(string str);

    bool search(string str);
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
            trie_size--;
            return true;
        }

        // if the current node is a leaf node and has children
        else
        {
            // mark the current node as a non-leaf node (DON'T DELETE IT)
            curr->isLeaf = false;

            // don't delete its parent nodes
            trie_size--;
            return false;
        }
    }

    return false;
}

void Trie::find_all(Node *&curr, string key, vector<string> &results)
{
    // If true, they the key is a valid string
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

size_t Trie::size() { return trie_size; }

void Trie::remove(string key)
{ 
    remove(root, key);
}

vector<string> Trie::find_all(string key)
{
    Node *curr = root;
    vector<string> results;
    bool isValidKey = false;

    for (string::iterator it = key.begin(); it != key.end(); it++)
    {
        if (curr->map.find(*it) == curr->map.end())
        {
            isValidKey = false;
            it = key.end() - 1;
        }
        else
        {
            isValidKey = true;
            curr = curr->map[*it];
        }
    }

    if (isValidKey)
        find_all(curr, key, results);

    return results;
}

void Trie::insert(string str)
{
    if (this->empty())
        root = new Node;

    Node *curr = root;

    for (const char &i : str)
    {
        if (curr->map.find(i) == curr->map.end())
            curr->map[i] = new Node;

        curr = curr->map[i];
    }

    // increment size if existing
    if(curr->isLeaf == false)
    trie_size++;

    curr->isLeaf = true;
}

bool Trie::search(string str)
{
    if (this->empty())
        return false;

    Node *curr = root;

    for (const char &i : str)
    {
        if(curr->map.find(i) == curr->map.end())
        return false;
        else
        curr = curr->map[i];
    }

    // return true if the current node is a leaf and the
    // end of the string is reached
    return curr->isLeaf;
}