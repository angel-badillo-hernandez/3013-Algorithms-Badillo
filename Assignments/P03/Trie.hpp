#pragma once
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <initializer_list>
// https://www.techiedelight.com/memory-efficient-trie-implementation-using-map-insert-search-delete/
using namespace std;

class Trie
{
private:
    struct Node
    {
        
        bool isLeaf{false}; // Flag for marking strings

        unordered_map<char, Node *> node_map; // Map to Child Nodes

        /**
         * public: Node
         * @brief Construct a new empty Node object.
         * 
         */
        Node();

        /**
         * public: ~Node
         * @brief Destroy the Node object. Recursively deallocates every child
         *        Node, and their child Nodes, and so on.
         * 
         */
        ~Node();

        /**
         * public: has_child
         * @brief Tests if the Node has children.
         * 
         * @return true if has children, false otherwise.
         */
        bool has_child();
    };

    Node *root{nullptr}; // Root of the Trie

    size_t trie_size{0}; // Size of Trie

    /**
     * private: remove
     * @brief Recursive private method that removes a string from the Trie.
     * 
     * @param curr current position in the Trie.
     * @param str string to remove from Trie.
     * @return true when a Node is to be deleted, false otherwise. 
     */
    bool remove(Node *&curr, const string &str);
    
    /**
     * private: find_all
     * @brief Recursive private method for searching for prefix-based matches
     *        using a key, then storing any matches.
     * 
     * @param curr current position in the Trie. 
     * @param key substring use for finding prefix-based matches in the Trie.
     * @param results vector containing all prefix_based matches.
     */
    void find_all(Node *&curr, const string &key, vector<string> &results);

    /**
     * private: copy_by_char
     * @brief Recursive method for copying strings from another instance of a
     *        Trie, starting at the root, then travels through the Trie, copying any
     *        string to "this" instance of a Trie.
     * 
     * @param curr 
     * @param key 
     */
    void copy_by_char(Node *&curr, const string &key);

    /**
     * private: get_root
     * @brief Returns a pointer to the root of the Trie.
     * 
     * @return Node*, pointer to root.
     */
    Node* get_root()const;

public:

    /**
     * public: Trie
     * @brief Construct a new empty Trie object.
     * 
     */
    Trie();

    /**
     * public: Trie
     * @brief Construct a new Trie object by copying from another instance.
     * 
     * @param other Trie to copy from. 
     */
    Trie(const Trie &other);

    /**
     * public: Trie
     * @brief Construct a new Trie object using an intializer list of strings.
     * 
     * @param S intializer list of strings to insert into Trie.
     */
    Trie(initializer_list<string> S);

    /**
     * public: ~Trie
     * @brief Destroy the Trie object. Recursively deallocates every Node in
     *        the Trie.
     * 
     */
    ~Trie();

    /**
     * public: clear
     * @brief Clears the Trie object.
     * 
     */
    void clear();

    /**
     * public: empty
     * @brief Tests if the Trie is empty, tests with root, not size of Trie.
     * 
     * @return true if empty, false otherwise.
     */
    bool empty()const;

    /**
     * public: size
     * @brief Returns the size of the Trie.
     * 
     * @return size_t, size of Trie. 
     */
    size_t size() const;

    /**
     * public: remove
     * @brief Removes a string from a Trie.
     * 
     * @param str string to remove from Trie.
     */
    void remove(const string &str);

    /**
     * @brief Searches for prefix-based partial matches using a key, stores
     *        matches in a vector of strings, then returns the vector.
     * 
     * @param key substring used to search for prefix_based partial matches.
     * @return vector<string>, all prefix_based partial matches.
     */
    vector<string> find_all(string key);

    void find_all(string key, vector<string> &results);

    void insert(string str);

    void insert(initializer_list<string> S);

    bool search(string str);
};

Trie::Node::Node() {}

Trie::Node::~Node()
{
    // Recursively deletes the Node*'s in this object's Node::node_map.
    for (pair<const char, Node *> &it : this->node_map)
        delete it.second;
}

bool Trie::Node::has_child()
{
    // Iterate through this object's Node::node_map.
    for (const pair<char, Node *> it : this->node_map)
        if (it.second != nullptr) // If second item in pair is not nullptr, then has children
            return true;
    return false;
}

inline Trie::Trie() {}

inline Trie::Trie(const Trie &other)
{
    if(other.empty())
    {
        return;
    }
    Node* curr = other.root->node_map.begin()->second;
    for (const pair<char, Node *> it : other.root->node_map)
    {
        string key(1, it.first);
        copy_by_char(curr, key);
    }
}

inline Trie::Trie(initializer_list<string> S)
{
    // Inserts every string to Trie
    for (const string str : S)
    {
        this->insert(S);
    }
}

inline Trie::~Trie() { delete root; }

inline void Trie::clear() { delete root; }

inline bool Trie::empty()const { return root == nullptr; }

inline size_t Trie::size() const { return trie_size; }

bool Trie::remove(Node *&curr, const string &str)
{

    // return if Trie is empty
    if (curr == nullptr)
    {
        return false;
    }

    // if the end of the key is not reached
    if (str.length())
    {
        // recur for the node corresponding to the next character in the key
        // and if it returns true, delete the current node (if it is non-leaf)
        if (curr != nullptr && curr->node_map.find(str[0]) != curr->node_map.end() &&
            remove(curr->node_map[str[0]], str.substr(1)) && curr->isLeaf == false)
        {
            if (!(curr->has_child()))
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
    if (str.length() == 0 && curr->isLeaf)
    {
        // if the current node is a leaf node and doesn't have any children
        if (!(curr->has_child()))
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

void Trie::find_all(Node *&curr, const string &key, vector<string> &results)
{
    // If true, they the key is a valid string.
    if (curr->isLeaf)
        results.push_back(key);

    // Iterate through current curr->node_map to recursively find prefix-based partial matches.
    for (pair<const char, Node *> &it : curr->node_map)
    {
        if (it.second) // If second item is not nullptr, find all matches with first item appended to key.
        {
            find_all(it.second, key + it.first, results);
        }
    }
}

void Trie::copy_by_char(Node *&curr, const string &key)
{
    // If true, they the key is a valid string.
    if (curr->isLeaf)
        this->insert(key);

    // Iterate through current curr->node_map to recursively find all words starting with the specified char
    for (pair<const char, Node *> &it : curr->node_map)
    {
        if (it.second) // If second item is not nullptr, find all matches with first item appended to key.
        {
            copy_by_char(it.second, key + it.first);
        }
    }
}

Trie::Node* Trie::get_root()const
{
    Node* curr = root;
    return curr;
}

inline void Trie::remove(const string &str)
{
    // Calls recursive private remove method.
    remove(root, str);
}

vector<string> Trie::find_all(string key)
{
    Node *curr = root;
    vector<string> results;
    bool isValidPath = false;

    // Uses key as a path to traverse through map, if path exists.
    for (string::iterator it = key.begin(); it != key.end(); it++)
    {
        if (curr->node_map.find(*it) == curr->node_map.end())
        {
            isValidPath = false;
            it = key.end() - 1; // Terminates loop
        }
        else
        {
            isValidPath = true;
            curr = curr->node_map.at(*it); // Move curr to next position
        }
    }

    // If the path exists, find all prefix-based partial matches.
    if (isValidPath)
        find_all(curr, key, results);

    return results;
}

void Trie::find_all(string key, vector<string> &results)
{
    Node *curr = root;
    results.clear();
    bool isValidPath = false;

    // Uses key as a path to traverse through map, if path exists.
    for (string::iterator it = key.begin(); it != key.end(); it++)
    {
        if (curr->node_map.find(*it) == curr->node_map.end())
        {
            isValidPath = false;
            it = key.end() - 1; // Terminate loop
        }
        else
        {
            isValidPath = true;
            curr = curr->node_map.at(*it); // Move curr to next position
        }
    }

    // If the path exists, find all prefix-based partial matches.
    if (isValidPath)
        find_all(curr, key, results);
}

inline void Trie::insert(string str)
{
    if (this->empty()) // If Trie is empty, create a new Node
        root = new Node;

    Node *curr = root;

    // Traverse through map, and insert new pair<char Node*> into map if necessary
    for (const char i : str)
    {
        if (curr->node_map.find(i) == curr->node_map.end())         // If pair doesn't exist
            curr->node_map.insert(pair<char, Node *>(i, new Node)); // Create a new one

        curr = curr->node_map.at(i);
    }

    // Increment size if string did not already exist
    if (curr->isLeaf == false)
        trie_size++;

    curr->isLeaf = true; // Mark as valid string
}

inline void Trie::insert(initializer_list<string> S)
{
    // Inserts every string in list to the Trie
    for (const string str : S)
    {
        this->insert(str);
    }
}

bool Trie::search(string str)
{
    if (this->empty()) // If Trie is empty, string doesn't exist
        return false;

    Node *curr = root;

    // Traverse through map using string as a path
    for (const char &i : str)
    {
        if (curr->node_map.find(i) == curr->node_map.end()) // If char does not exist
            return false;                                   // string is not in Trie.
        else                                                // Otherwise, move curr to next position.
            curr = curr->node_map.at(i);
    }

    // returns true if the current node is a leaf and the
    // end of the string is reached
    return curr->isLeaf;
}