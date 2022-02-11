/**************************************************************************************
*
*  Author:           Angel Badillo Hernandez  / @It-Is-Legend27
*  Email:            badilloa022402@gmail.com / abadillo0224@my.msutexas.edu
*  Label:            P02
*  Title:            Processing in Linear Time
*  Course:           CMPS-3013-201
*  Semester:         Spring 2022
*
*  Description:
*        Simulation of performing operations on a singely linked list.
         Times how long it takes to load the file data to the list.
         Times how long it takes get partial matches from a list.
         Gets chars by "getching" and creates substrings to use for finding
         partial matches. Minor note, Milliseconds() works because I edited Prof. Griffin's
         "timer.hpp" file.
*
*  Usage:
*        g++ main.cpp -o main
         ./main
*
*  Files:            main.cpp
                     List.hpp
                     timer.hpp
                     mygetch.hpp
                     termcolor.hpp
                     dictionary.txt
***************************************************************************************/
#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <initializer_list>

using namespace std;

/**
 * Class WordNode
 *
 * Description: A simple node class that holds a string and a WordNode pointer.
 *              For use in singely linked list.
 *
 * Public_Methods:
 *          WordNode()
 *          WordNode(string _data, WordNode* _next)
 *
 * Private_Methods:
 *      - N/A
 *
 * Usage:
 *      For use in List class defined below.
 *      - WordNode* back = new WordNode("A"); // Second arg defaults to nullptr
 *      - WordNode* front = new WordNode("B", back);
 */
class WordNode
{
public:
    string word{string()};   // Data value. A "word".
    WordNode *next{nullptr}; // Points to next node on list.

    /**
     * public: WordNode
     * @brief Construct a new WordNode object.
     *
     */
    WordNode();

    /**
     * public: WordNode()
     * @brief Construct a new WordNode object with params.
     *
     * @param _data string value to in the WordNode .
     * @param _next WordNode pointer link to next item in list.
     */
    WordNode(string _data, WordNode *_next);
};

/**
 * public: WordNode
 * @brief Construct a new WordNode object.
 *
 */
inline WordNode::WordNode() {}

/**
 * public: WordNode()
 * @brief Construct a new WordNode object with params.
 *
 * @param _data string value to in the WordNode .
 * @param _next WordNode pointer link to next item in list.
 */
inline WordNode::WordNode(string _data, WordNode *_next = nullptr) : word{_data}, next{next} {}

/**
 * Class WordNode
 *
 * Description: A "simple" singely linked list class with common methods, and
 *              some interesting ones, such as subscript operator[], stream
 *              insertion operator<<, and more.
 *
 * Public_Methods:
 *                List()
 *                List(intializer_list<string> S)
 *                List(const List& other)
 *                ~List()
 *         void   resize(size_t _size, string _data)
 *         bool   empty()
 *         void   fill(string _data)
 *         void   clear()
 *         void   push_front(string _data)
 *         void   push_front(const List &other)
 *         void   push_back(string _data)
 *         void   push_back(const List &other)
 *      string&   at(size_t n)
 *      string&   at(size_t n) const
 *         void   pop_front()
 *         void   pop_back()
 *         void   erase(size_t n)
 *         void   remove(string _value)
 * const size_t   find(string _value)
 *         void   print(ostream &os)
 *       size_t   size() const
 *       size_t   max_size() const
 *         void   swap(List &other)
 *       friend   ostream &operator<<(ostream &os, const List &L)
 *      string&   operator[](size_t n)
 *      string&   operator[](size_t n) const
 *        List&   operator=(const List &rhs)
 *         List   operator=(const initializer_list<string> S)
 *
 * Private_Methods:
 *    WordNode*   prev_node(WordNode *ptr)
 *
 * Usage:
 *      - List L;           // Creates empty list
 *      - L.resize(10);     // Resizes list with default values
 *      - L.push_back("A"); // Pushes a value to the back of the list
 *      - L.push_front(""); // Pushes a value to the front of the list
 *      - L.pop_back();     // Removes a value from the back of the list
 *      - L.pop_front();    // Removes a value from the front of the list
 *      - L[0] = "Hi";      // Returns read/write reference to specific element
 *      - L.at(1) = "?";    // ``
 *      - int i = L.size(); // Returns size of the list
 *      - cout << L;        // Prints list
 *      - L.print(cout)     // ``
 *      - L.clear();        // Clears list
 */
class List
{
private:
    WordNode *front{nullptr}; // Head of the list
    WordNode *back{nullptr};  // Tail of the list
    size_t list_size{0};      // Size of list

    /**
     * private: prev_node
     * @brief Returns a pointer to a WordNode one position before the one
     *        passed in.
     *
     * @param ptr A pointer to a WordNode.
     * @return WordNode*
     */
    WordNode *prev_node(WordNode *ptr);
public:
    /**
     * public: List
     * @brief Construct a new List object.
     *
     */
    List();

    /**
     * public: List
     * @brief Construct a new List object using an std::initalizer_list<string>.
     *
     * @param S An intializer list containing strings.
     */
    List(initializer_list<string> S);

    /**
     * public: List
     * @brief Construct a new List object using another List object.
     *
     * @param other A list to copy from.
     */
    List(const List &other);

    /**
     * public: ~List
     * @brief Destroy the List object.
     *
     */
    ~List();

    /**
     * public: resize
     * @brief Resizes the List. Removes or adds WordNodes as needed.
     *
     * @param _size the new size of the List.
     * @param _data value to use for possible new WordNodes.
     */
    void resize(size_t _size, string _data);

    /**
     * public: empty
     * @brief Tests if the List is empty.
     *
     * @return true if empty, false otherwise.
     */
    bool empty();

    /**
     * public: fill
     * @brief Fills the list with specified value. Only reassigns data of existing WordNodes.
     *
     * @param _data value to fill list with.
     */
    void fill(string _data);

    /**
     * public: clear
     * @brief Clears the list. Makes it completely empty.
     *
     */
    void clear();

    /**
     * public: push_front
     * @brief Push a new value to the front of the List.
     *
     * @param _data new value to prepend to List.
     */
    void push_front(string _data);

    /**
     * public: push_front
     * @brief Pushes an entire other list to the front of this List.
     *
     * @param other other list to prepend to this List.
     */
    void push_front(const List &other);

    /**
     * public: push_back
     * @brief Push a new value to the back of the List.
     *
     * @param _data a new value to append to List.
     */
    void push_back(string _data);

    /**
     * public: push_back
     * @brief Pushes an entire other list to the front of this List.
     *
     * @param other other list to append to List.
     */
    void push_back(const List &other);

    /**
     * public: at
     * @brief Returns a read/write reference to specified position in the
     *        List.
     *
     * @param n position of element (WordNode) to access.
     * @return string&
     */
    string &at(size_t n);

    /**
     * public: at
     * @brief Returns a constant read only reference to specified position in
     *        the List.
     *
     * @param n  position of element (WordNode) to access.
     * @return string&
     */
    string &at(size_t n) const;

    /**
     * public: pop_front
     * @brief Remove the first item in the List. Does not return value.
     *
     */
    void pop_front();

    /**
     * public: pop_back
     * @brief Removes the last item in the List. Does not return value.
     *
     */
    void pop_back();

    /**
     * public: erase
     * @brief Erases a specific element (WordNode) from the List.
     *
     * @param n position of element (WordNode) to remove.
     */
    void erase(size_t n);

    /**
     * public: remove
     * @brief Removes all instances of specified value from the List.
     *
     * @param _value value to remove from List.
     */
    void remove(string _value);

    /**
     * public: find
     * @brief Searches for the first instance of a specified value in the List
     *        and returns the index.
     *
     * @param _value value being searched for.
     * @return const size_t
     */
    size_t find(string _value);

    /**
     * public: print
     * @brief Prints the List to an output stream (cout by default).
     *
     * @param os an output stream.
     */
    void print(ostream &os);

    /**
     * public: size
     * @brief Returns size of the List.
     *
     * @return size_t
     */
    size_t size() const;

    /**
     * public: max_size
     * @brief Returns max possible size of a List that this implementation allows.
     *
     * @return size_t
     */
    size_t max_size() const;

    /**
     * public: swap
     * @brief Swaps this List with another. Utilizes std::swap function.
     *
     * @param other other List to swap with this List.
     */
    void swap(List &other);

    /**
     * public: operator<<
     * @brief Inserts List to an output stream for printing.
     *
     * @param os output stream.
     * @param L List to print.
     * @return ostream&
     */
    friend ostream &operator<<(ostream &os, const List &L);

    /**
     * @brief Treats List similarly to an array. Returns read/write reference
     *        to a specific element (WordNode).
     *
     * @param n position of element to access (WordNode).
     * @return string&
     */
    string &operator[](size_t n);

    /**
     * @brief Treats List similarly to an const array. Returns const read only
     *        reference to a specific element (WordNode).
     *
     * @param n position of element to access (WordNode).
     * @return string&
     */
    string &operator[](size_t n) const;

    /**
     * @brief Allows initialization of a List using another without worry of shallow copy.
     *        Returns a deep copy.
     *
     * @param rhs List on right-hand side of assignment statement.
     * @return List&
     */
    List &operator=(const List &rhs);

    /**
     * @brief Allows intialization of a List using std::intializater_list<string>.
     *
     * @param S an intializer list of strings.
     * @return List
     */
    List operator=(const initializer_list<string> S);
};

/**
 * public: List
 * @brief Construct a new List object.
 *
 */
inline List::List() {}

/**
 * private: prev_node
 * @brief Returns a pointer to a WordNode one position before the one
 *        passed in.
 *
 * @param ptr A pointer to a WordNode.
 * @return WordNode*
 */
inline WordNode *List::prev_node(WordNode *ptr)
{
    WordNode *prev = front;
    for (size_t i = 0; i < list_size; i++)
    {
        if (prev->next == back)
        {
            return prev;
        }
        prev = prev->next;
    }
    return nullptr;
}

/**
 * public: List
 * @brief Construct a new List object using an std::initalizer_list<string>.
 *
 * @param S An intializer list containing strings.
 */
inline List::List(initializer_list<string> L)
{
    for (string x : L)
    {
        this->push_back(x);
    }
}

/**
 * public: List
 * @brief Construct a new List object using another List object.
 *
 * @param other A list to copy from.
 */
inline List::List(const List &other)
{
    WordNode *temp = other.front;
    while (temp)
    {
        this->push_back(temp->word);
        temp = temp->next;
    }
}

/**
 * public: ~List
 * @brief Destroy the List object.
 *
 */
inline List::~List()
{
    this->clear();
}

/**
 * public: resize
 * @brief Resizes the List. Removes or adds WordNodes as needed.
 *
 * @param _size the new size of the List.
 * @param _data value to use for possible new WordNodes.
 */
inline void List::resize(size_t _size, string _data = string())
{
    if (this->list_size == _size || (int)_size < 0) // If same size, or invalid value, no resize needed
    {
        return;
    }
    else if (this->list_size > _size) // If new size is smaller, remove values
    {
        size_t removeAmount = this->list_size - _size;
        for (size_t i = 0; i < removeAmount; i++)
            this->pop_back();
    }
    else if (list_size < _size) // If new size is greater, add default values
    {
        size_t removeAmount = _size - this->list_size;
        for (size_t i = 0; i < removeAmount; i++)
            this->push_back(_data);
    }
}

/**
 * public: empty
 * @brief Tests if the List is empty.
 *
 * @return true if empty, false otherwise.
 */
inline bool List::empty()
{
    return this->list_size == 0;
}

/**
 * public: fill
 * @brief Fills the list with specified value. Only reassigns data of existing WordNodes.
 *
 * @param _data value to fill list with.
 */
inline void List::fill(string _data)
{
    if (!(this->empty())) // If not empty
    {
        WordNode *travel = this->front; // travel points to front

        while (travel) // Travels until travel == nullptr
        {
            travel->word = _data;  // Replace value
            travel = travel->next; // Move to next node
        }
    }
}

/**
 * public: clear
 * @brief Clears the list. Makes it completely empty.
 *
 */
inline void List::clear()
{
    while (!(this->empty()))
        this->pop_back();
}

/**
 * public: push_front
 * @brief Push a new value to the front of the List.
 *
 * @param _data new value to prepend to List.
 */
inline void List::push_front(string _data)
{
    if (this->empty()) // If empty list
    {
        this->front = this->back = new WordNode(_data); // 1 item, so front & back are same
    }
    else if (list_size == 1) // If one item
    {
        this->front = new WordNode(_data, this->back);
    }
    else
    {
        this->front = new WordNode(_data, this->front); // New front->next points to old front
    }
    this->list_size++;
}

/**
 * public: push_front
 * @brief Pushes an entire other list to the front of this List.
 *
 * @param other other list to prepend to this List.
 */
inline void List::push_front(const List &other)
{
    for (size_t i = other.list_size - 1; i >= 0; i++)
    {
        this->push_front(other[i]);
    }
}

/**
 * public: push_back
 * @brief Push a new value to the back of the List.
 *
 * @param _data a new value to append to List.
 */
inline void List::push_back(string _data)
{
    if (this->empty())
    {
        this->front = this->back = new WordNode(_data); // 1 item, so front & back are same
    }
    else if (this->list_size == 1)
    {
        this->back = new WordNode(_data);
        this->front->next = this->back;
    }
    else
    {
        WordNode *prev = this->back;      // Prev WordNode to new back WordNode
        this->back = new WordNode(_data); // New back WordNode
        prev->next = this->back;          // Prev WordNode linked to new back
    }
    this->list_size++;
}

/**
 * public: push_back
 * @brief Pushes an entire other list to the front of this List.
 *
 * @param other other list to append to List.
 */
inline void List::push_back(const List &other)
{
    for (size_t i = 0; i < other.list_size; i++)
    {
        this->push_back(other[i]);
    }
}

/**
 * public: at
 * @brief Returns a read/write reference to specified position in the
 *        List.
 *
 * @param n position of element (WordNode) to access.
 * @return string&
 */
inline string &List::at(size_t n)
{
    if ((int)n < 0 || n >= this->list_size)
    {
        exit(1);
    }
    else
    {
        WordNode *temp = this->front;
        for (size_t i = 0; i < n; i++)
        {
            temp = temp->next;
        }
        return temp->word;
    }
}

/**
 * public: at
 * @brief Returns a constant read only reference to specified position in
 *        the List.
 *
 * @param n  position of element (WordNode) to access.
 * @return string&
 */
inline string &List::at(size_t n) const
{
    if ((int)n < 0 || n >= this->list_size)
    {
        exit(1);
    }
    else
    {
        WordNode *temp = this->front;
        for (size_t i = 0; i < n; i++)
        {
            temp = temp->next;
        }
        return temp->word;
    }
}

/**
 * public: pop_front
 * @brief Remove the first item in the List. Does not return value.
 *
 */
inline void List::pop_front()
{
    if (this->empty())
    {
        return; // Cannot pop from empty list
    }
    else if (this->list_size == 1)
    {
        delete this->front;
        this->front = this->back = nullptr;
        this->list_size--;
    }
    else
    {
        WordNode *trash = front;
        front = front->next;
        delete trash;
        this->list_size--;
    }
}

/**
 * public: pop_back
 * @brief Removes the last item in the List. Does not return value.
 *
 */
inline void List::pop_back()
{
    if (this->empty()) // Cannot pop from empty list
    {
        return;
    }
    else if (this->list_size == 1) // When only one item in list
    {
        delete this->back;
        this->front = this->back = nullptr;
        this->list_size--;
    }
    else
    {
        WordNode *prev = prev_node(this->back); // Get prev WordNode
        delete this->back;
        this->back = prev;          // Update back
        this->back->next = nullptr; // Update back->next
        this->list_size--;
    }
}

/**
 * public: erase
 * @brief Erases a specific element (WordNode) from the List.
 *
 * @param n position of element (WordNode) to remove.
 */
inline void List::erase(size_t n)
{
    if (this->empty()) // Cannot erase from empty list
    {
        return;
    }
    else if ((int)n < 0 || n >= this->list_size) // Cannot access out of bounds
    {
        return;
    }
    else if (n == 0) // n is frontmost item
    {
        this->pop_front();
    }
    else if (n == this->list_size - 1) // n is rearmost item
    {
        this->pop_back();
    }
    else // Travels through until it reaches index
    {
        WordNode *temp = this->front;
        WordNode *prev = nullptr;
        for (size_t i = 0; i < n; i++)
        {
            prev = temp;
            temp = temp->next;
        }
        prev->next = temp->next; // Links prev WordNode to temp->next WordNode
        delete temp;
        this->list_size--;
    }
}

/**
 * public: remove
 * @brief Removes all instances of specified value from the List.
 *
 * @param _value value to remove from List.
 */
inline void List::remove(string _value)
{
    size_t i = this->find(_value); // Get index of first occurence of _value

    while (i != (size_t)-1) // While index i is valid
    {
        this->erase(i);
        i = this->find(_value);
    }
}

/**
 * public: find
 * @brief Searches for the first instance of a specified value in the List
 *        and returns the index.
 *
 * @param _value value being searched for.
 * @return const size_t
 */
inline size_t List::find(string _value)
{
    WordNode *temp = this->front;
    size_t i = 0;

    while (temp)
    {
        if (_value == temp->word) // If found, return index
        {
            return i;
        }
        else // Move to next node
        {
            temp = temp->next;
            i++;
        }
    }
    return (size_t)-1; // Returns -1 if not found
}

/**
 * public: print
 * @brief Prints the List to an output stream (cout by default).
 *
 * @param os an output stream.
 */
inline void List::print(ostream &os = cout)
{
    if (!(this->empty())) // If not empty
    {
        WordNode *travel = this->front; // travel points to front

        os << "[";

        while (travel) // Travels until travel == nullptr
        {
            os << travel->word; // Print word from node
            if (travel->next)
            {
                os << ", ";
            }
            travel = travel->next; // Move to next node
        }
        os << ']';
    }
}

/**
 * public: size
 * @brief Returns size of the List.
 *
 * @return size_t
 */
inline size_t List::size() const
{
    return this->list_size;
}

/**
 * public: max_size
 * @brief Returns max possible size of a List that this implementation allows.
 *
 * @return size_t
 */
inline size_t List::max_size() const
{
    return INT32_MAX;
}

/**
 * public: swap
 * @brief Swaps this List with another. Utilizes std::swap function.
 *
 * @param other other List to swap with this List.
 */
inline void List::swap(List &other)
{
    std::swap<List>((*this), other);
}

/**
 * public: operator<<
 * @brief Inserts List to an output stream for printing.
 *
 * @param os output stream.
 * @param L List to print.
 * @return ostream&
 */
inline ostream &operator<<(ostream &os, const List &L)
{
    WordNode *temp = L.front;
    os << "[";
    while (temp)
    {
        os << temp->word;
        if (temp->next)
        {
            os << ", ";
        }
        temp = temp->next;
    }
    os << "]";
    return os;
}

/**
 * @brief Treats List similarly to an array. Returns read/write reference
 *        to a specific element (WordNode).
 *
 * @param n position of element to access (WordNode).
 * @return string&
 */
inline string &List::operator[](size_t n)
{
    if ((int)n < 0 || n >= this->list_size)
    {
        exit(1);
    }
    else
    {
        WordNode *temp = this->front;
        for (size_t i = 0; i < n; i++)
        {
            temp = temp->next;
        }
        return temp->word;
    }
}

/**
 * @brief Treats List similarly to an const array. Returns const read only
 *        reference to a specific element (WordNode).
 *
 * @param n position of element to access (WordNode).
 * @return string&
 */
inline string &List::operator[](size_t n) const
{
    if ((int)n < 0 || n >= this->list_size)
    {
        exit(1);
    }
    else
    {
        WordNode *temp = this->front;
        for (size_t i = 0; i < n; i++)
        {
            temp = temp->next;
        }
        return temp->word;
    }
}

/**
 * @brief Allows initialization of a List using another without worry of shallow copy.
 *        Returns a deep copy.
 *
 * @param rhs List on right-hand side of assignment statement.
 * @return List&
 */
inline List &List::operator=(const List &rhs)
{
    if (this != &rhs)
    {
        this->clear();
        this->push_back(rhs);
    }
    return *this;
}

/**
 * @brief Allows intialization of a List using std::intializater_list<string>.
 *
 * @param S an intializer list of strings.
 * @return List
 */
inline List List::operator=(const initializer_list<string> L)
{
    this->clear();

    for (string x : L)
    {
        this->push_back(x);
    }
    return *this;
}