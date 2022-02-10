#pragma once

#include <iostream>
#include <fstream>
#include <array>
#include <vector>

using namespace std;

class Node
{
public:
    string word{string()}; // Data value
    Node *next{nullptr};   // Points to next node on list

    Node() {}

    Node(string _data, Node *_next = nullptr) : word{_data}, next{next} {}
};

class List
{
private:
    Node *front{nullptr}; // Head of the list
    Node *back{nullptr};  // Tail of the list
    size_t list_size{0};  // Size of list
protected:
    Node *getPrev(Node *ptr)
    {
        Node *prev = front;
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

public:
    List() {}

    List(initializer_list<string> S)
    {
        for (string x : S)
        {
            this->push_back(x);
        }
    }

    List(const List &other)
    {
        Node *temp = other.front;
        while (temp)
        {
            this->push_back(temp->word);
            temp = temp->next;
        }
    }

    ~List()
    {
        this->clear();
    }

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

    bool empty()
    {
        return this->list_size == 0;
    }

    void fill(string _data);

    void clear();

    void push_front(string _data);

    void push_front(const List &other);

    void push_back(string _data);

    void push_back(const List &other);

    string &at(size_t n);

    string &at(size_t n) const;

    void pop_front();

    void pop_back();

    void erase(size_t n);

    void remove(string _value);

    const size_t find(string _value);

    void print(ostream &os);

    size_t size() const;

    size_t max_size() const;

    void swap(List &other);

    friend ostream &operator<<(ostream &os, const List &L);

    string &operator[](size_t n);

    string &operator[](size_t n) const;

    List &operator=(const List &rhs);

    inline List operator=(const initializer_list<string> S);
};

inline void List::fill(string _data)
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

inline void List::clear()
{
    while (!(this->empty()))
        this->pop_back();
}

inline void List::push_front(string _data)
{
    if (this->empty()) // If empty list
    {
        this->front = this->back = new Node(_data); // 1 item, so front & back are same
    }
    else if (list_size == 1) // If one item
    {
        this->front = new Node(_data, this->back);
    }
    else
    {
        this->front = new Node(_data, this->front); // New front->next points to old front
    }
    this->list_size++;
}

inline void List::push_front(const List &other)
{
    for (size_t i = other.list_size - 1; i >= 0; i++)
    {
        this->push_front(other[i]);
    }
}

inline void List::push_back(string _data)
{
    if (this->empty())
    {
        this->front = this->back = new Node(_data); // 1 item, so front & back are same
    }
    else if (this->list_size == 1)
    {
        this->back = new Node(_data);
        this->front->next = this->back;
    }
    else
    {
        Node *prev = this->back;      // Prev Node to new back Node
        this->back = new Node(_data); // New back Node
        prev->next = this->back;      // Prev Node linked to new back
    }
    this->list_size++;
}

inline void List::push_back(const List &other)
{
    for (size_t i = 0; i < other.list_size; i++)
    {
        this->push_back(other[i]);
    }
}

inline string &List::at(size_t n)
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

inline string &List::at(size_t n) const
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
        Node *trash = front;
        front = front->next;
        delete trash;
        this->list_size--;
    }
}

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
        Node *prev = getPrev(this->back); // Get prev Node
        delete this->back;
        this->back = prev;          // Update back
        this->back->next = nullptr; // Update back->next
        this->list_size--;
    }
}

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

inline void List::remove(string _value)
{
    size_t i = this->find(_value); // Get index of first occurence of _value

    while (i != (size_t)-1) // While index i is valid
    {
        this->erase(i);
        i = this->find(_value);
    }
}

inline const size_t List::find(string _value)
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

inline void List::print(ostream &os = cout)
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

inline size_t List::size() const
{
    return this->list_size;
}

inline size_t List::max_size() const
{
    return INT32_MAX;
}

inline void List::swap(List &other)
{
    std::swap<List>((*this), other);
}

inline ostream &operator<<(ostream &os, const List &L)
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

inline string &List::operator[](size_t n)
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

inline List &List::operator=(const List &rhs)
{
    if (this != &rhs)
    {
        this->clear();
        this->push_back(rhs);
    }
    return *this;
}

inline List List::operator=(const initializer_list<string> S)
{
    this->clear();

    for(string x : S)
    {
        this->push_back(x);
    }
    return *this;
}