#pragma once

#include <iostream>
#include <fstream>
#include <array>
#include <vector>

using namespace std;

/**
 * Node Class
 * @brief Simple templated Node class for use in templated doubly linked list (List).
 *
 * @tparam T any type
 */
class Node
{
public:
    string word{string()}; // Data value
    Node *next{nullptr};   // Points to next node on list

    /**
     * Node
     * @brief Construct a new Node object.
     *
     */
    Node() {}

    /**
     * Node
     * @brief Construct a new Node object with params.
     *
     * @param _data word to store in Node
     * @param _prev pointer to previous Node
     * @param _next pointer to next Node
     */
    Node(string _data, Node *_next = nullptr)
    {
        this->word = _data;
        this->next = _next;
    }
};

/**
 * List Class
 * @brief Templated Doubly Linked List that makes use of subscript [] operator
 *        stream insertion << operator, and other array / vector-like methods.
 *
 */
class List
{
private:
    Node *front{nullptr}; // Head of the list
    Node *back{nullptr};  // Tail of the list
    size_t list_size{0};  // Size of list

public:
    /**
     * List
     *
     * @brief Construct a new empty List object.
     *
     */
    List() {}

    /**
     * List
     * @brief Construct a new List object by copying another.
     *
     * @param other List of type T.
     */
    List(const List &other)
    {
        Node *temp = other.front;
        while (temp)
        {
            this->push_back(temp->word);
            temp = temp->next;
        }
    }

    /**
     * ~List
     * @brief Destroy the List object
     *
     */
    ~List()
    {
        this->clear();
    }

    /**
     * public: void resize
     * @brief Resizes the list, and pushes default values if needed.
     *
     * @param _size new size of the list.
     */
    void resize(size_t _size)
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
                this->push_back(string());
        }
    }

    /**
     * public: void resize
     * @brief Resizes the list, and pushes '_data' to new nodes if needed.
     *
     * @param _size new size of the list.
     * @param _data value to push in new nodes, if any.
     */
    void resize(size_t _size, string _data)
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
     * public: bool empty
     * @brief Tests if the list is empty.
     *
     * @return true if empty, false otherwise.
     */
    bool empty()
    {
        return this->list_size == 0;
    }

    /**
     * public: void fill
     * @brief Fills the list with '_data'.
     *
     * @param _data value to fill list with.
     */
    void fill(string _data)
    {
        if (!(this->empty())) // If not empty
        {
            Node *travel = this->front; // travel points to front

            while (travel) // Travels until travel == nullptr
            {
                travel->word = _data;  // Replace value
                travel = travel->next; // Move to next node
            }
        }
    }

    /**
     * public: void clear
     * @brief Clears the list. Makes it empty.
     *
     */
    void clear()
    {
        while (!(this->empty()))
            this->pop_back();
    }

    /**
     * public: void push_front
     * @brief Pushes a value to the front of the list.
     *
     * @param _data value to push to front of list.
     */
    void push_front(string _data)
    {
        if (this->empty()) // If empty list
        {
            this->front = this->back = new Node(_data); // 1 item, so front & back are same
        }
        else if (list_size == 1) // If one item
        {
            this->front = new Node(_data, this->front); // New front->next points to old front / back
        }
        else
        {
            this->front = new Node(_data, this->front); // New front->next points to old front
        }
        this->list_size++;
    }

    /**
     * public: void push_front
     * @brief Pushes an entire List to the front of this list.
     *
     * @param other other list to push to front of this one.
     */
    void push_front(const List &other)
    {
        for (size_t i = other.size() - 1; i >= 0; i++)
        {
            this->push_front(other[i]);
        }
    }

    /**
     * public: void push_back
     * @brief Pushes a value to the back of the list.
     *
     * @param _data value to push to back of the list.
     */
    void push_back(string _data)
    {
        if (this->empty())
        {
            this->front = this->back = new Node(_data); // 1 item, so front & back are same
        }
        else if (this->list_size == 1)
        {
            this->back = new Node(_data, this->back); // New back->prev points to old back
            this->front->next = this->back;           // front->next points to new back
        }
        else
        {
            this->back = new Node(_data, this->back); // New back->prev points to old back
            this->back->prev->next = this->back;      // Old back->next points to new back
        }
        this->list_size++;
    }

    /**
     * public: void push_back
     * @brief Pushes an entire List to the front of this list.
     *
     * @param other other list to push to front of this one.
     */
    void push_back(const List &other)
    {
        Node *temp = other.front;

        while (temp)
        {
            this->push_back(temp->word); // Pushes list to the back left to right
            temp = temp->next;
        }
    }

    /**
     * public: T& at
     * @brief Returns read/write reference to element 'n' in the list. Same as List::operator[].
     *
     * @param n position of element.
     * @return T& reference to element n.
     */
    string &at(size_t n)
    {
        if ((int)n < 0 || n >= this->list_size)
        {
            exit(1);
        }
        else
        {
            Node *temp = this->front;
            for (size_t i = 0; i < n; i++)
            {
                temp = temp->next;
            }
            return temp->word;
        }
    }

    const string &at(size_t n)const
    {
        
    }

    /**
     * public: void pop_front
     * @brief Removes element from front of the list. Does not return
     * the _dataue, however, so it must be retrieved before calling this
     * function, if desired.
     *
     */
    void pop_front()
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
            Node *deleteMe = this->front;    // Save pointer for deletion
            this->front = this->front->next; // Move front down
            this->front->prev = nullptr;
            delete deleteMe;
            this->list_size--;
        }
    }

    /**
     * public: void pop_back
     * @brief Removes element from back of the list. Does not return
     * the _dataue, however, so it must be retrieved before calling this
     * function, if desired.
     *
     */
    void pop_back()
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
            Node *deleteMe = this->back;   // Save pointer for deletion
            this->back = this->back->prev; // Move back up
            this->back->next = nullptr;    // Double linked list ends in nullptr
            delete deleteMe;
            this->list_size--;
        }
    }

    /**
     * public: void erase
     * @brief Removes element at position 'n' from the list.
     *
     * @param n position of the element to remove.
     */
    void erase(size_t n)
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
            Node *temp = this->front;
            Node *prev = nullptr;
            for (size_t i = 0; i < n; i++)
            {
                prev = temp;
                temp = temp->next;
            }
            prev->next = temp->next; // Links prev Node to temp->next Node
            delete temp;
            this->list_size--;
        }
    }

    /**
     * public: void remove
     * @brief Removes all values that match '_value' from the list.
     *
     * @param _value value to be removed from the list.
     */
    void remove(string _value)
    {
        size_t i = this->find(_value); // Get index of first occurence of _value

        while (i != (size_t)-1) // While index i is valid
        {
            this->erase(i);
            i = this->find(_value);
        }
    }

    /**
     * @brief Finds first occurence of '_value' in the list and returns its position.
     *
     * @param _value value to be searched for.
     * @return size_t - position where '_value' is located.
     */
    size_t find(string _value)
    {
        Node *temp = this->front;
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
     * public: void print
     * @brief Prints the entire list to an output stream. Prints to cout by
     *        default. Can print to ofstream as well.
     *
     */
    void print(ostream &os = cout)
    {
        if (!(this->empty())) // If not empty
        {
            Node *travel = this->front; // travel points to front

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
     * public: size_t size
     * @brief Returns the size of the list.
     *
     * @return size_t size of the list.
     */
    const size_t size()
    {
        return this->list_size;
    }

    /**
     * @brief Returns the maximum size possible (however it takes a lot of memory).
     *
     * @return size_t
     */
    const size_t max_size()
    {
        return INT32_MAX; //
    }

    /**
     * public: void swap
     * @brief Swaps the contents of this list, with another. Utilizes
     *        std::swap function.
     *
     * @param other other list to swap with this list.
     */
    void swap(List &other)
    {
        std::swap<List>((*this), other);
    }

    /**
     * public: ostream& operator<<
     * @brief Overloaded stream insertion << operator for printing list to
     *        an output stream. Works with ofstream as well.
     *
     * @param os output stream to insert list to.
     * @param L List of type T.
     * @return ostream& output stream by reference.
     */
    friend ostream &operator<<(ostream &os, const List &L)
    {
        Node *temp = L.front;
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
     * @brief Overloaded subscript [] operator. Used for accessing an element at
     *        position 'n' of the list. Returns read/write reference to that
     *        element. Same as List::at.
     *
     * @param n position of element.
     * @return T& reference to element n.
     */
    string &operator[](size_t n)
    {
        if ((int)n < 0 || n >= this->list_size)
        {
            exit(1);
        }
        else
        {
            Node *temp = this->front;
            for (size_t i = 0; i < n; i++)
            {
                temp = temp->next;
            }
            return temp->word;
        }
    }

    const string &operator[](size_t n) const
    {
        if ((int)n < 0 || n >= this->list_size)
        {
            exit(1);
        }
        else
        {
            Node *temp = this->front;
            for (size_t i = 0; i < n; i++)
            {
                temp = temp->next;
            }
            return temp->word;
        }
    }

    /**
     * @brief Overloaded assignment = operator. Used for assigning another
     *        list to the current one in such a way to prevent shallowing
     *        copying.
     *
     * @param rhs list on the right-hand side of assignment statement.
     * @return List<T>& list to assign to left-hand list of assignment statement.
     */
    List &operator=(const List &rhs)
    {
        if (this != &rhs)
        {
            this->clear();
            this->push_back(rhs);
        }
        return *this;
    }
};
