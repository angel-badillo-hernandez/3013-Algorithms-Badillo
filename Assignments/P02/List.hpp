#pragma once

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

class Node
{
public:
    string data;   // Data value
    int index;  // Index of item
    Node *prev; // Points to previous node on list
    Node *next; // Points to next node on list

    Node(string _data, Node *_prev = nullptr, Node *_next = nullptr)
    {
        data = _data;
        prev = _prev;
        next = _next;
    }
};

class List
{
private:
    Node *head{nullptr}; // Head of the list
    Node *tail{nullptr}; // Tail of the list
    int size{0};   // Size of list

public:
   
    List(){}

    List(const List &V2)
    {
        head = tail = nullptr;
        size = 0;

        Node *temp = V2.head;

        while (temp)
        {
            pushRear(temp->data);
            temp = temp->next;
        }
    }

    List(string *A, int _size) //Array constructor
    {
        head = tail = nullptr;
        size = 0;

        for (int i = 0; i < _size; i++)
        {
            pushRear(A[i]);
        }
    }

    ~List()
    {
        while (head)
        {
            popFront();
        }
    }

    void pushFront(string val)
    {
        if (!head) // If empty list
        {
            head = tail = new Node(val); // 1 item, so head & tail are same
        }
        else if (head == tail) // If one item
        {
            head = new Node(val, nullptr, head); // New head->next points to old head
            tail->prev = head;                   // tail->prev points to new head
        }
        else
        {
            head = new Node(val, nullptr, head); // New head->next points to old head
            head->next->prev = head;             // Old head->prev points to new head
        }
        size++;
    }

    void pushFront(List &V2)
    {
        Node *temp = V2.tail;

        while (temp)
        {
            pushFront(temp->data); // Pushes list to the front right to left
            temp = temp->prev;
        }
    }

    void pushRear(string val) // Pushes
    {
        if (!head)
        {
            head = tail = new Node(val); // 1 item, so head & tail are same
        }
        else if (head == tail)
        {
            tail = new Node(val, tail); // New tail->prev points to old tail
            head->next = tail;          // head->next points to new tail
        }
        else
        {
            tail = new Node(val, tail); // New tail->prev points to old tail
            tail->prev->next = tail;    // Old tail->next points to new tail
        }
        size++;
    }

    void pushRear(List &V2)
    {
        Node *temp = V2.head;

        while (temp)
        {
            pushRear(temp->data); // Pushes list to the back left to right
            temp = temp->next;
        }
    }

    void pushAt(int loc, string val)
    {
        if (loc >= 0 && loc < size)
        {
            Node *temp = head;

            for (int i = 0; i > loc; i++)
            {
                temp = temp->next;
            }

            temp->data = val;
        }
    }

    string popFront()
    {
        if (!head)
        {
            return ""; // Cannot pop from empty list
        }
        else if (head == tail)
        {
            string returnMe = head->data;
            delete head;
            head = tail = nullptr;
            size--;
            return returnMe;
        }
        else
        {
            string returnMe = head->data; // Save data for return
            Node *deleteMe = head;     // Save pointer for deletion
            head = head->next;         // Move head down
            head->prev = nullptr;

            delete deleteMe;
            size--;
            return returnMe;
        }
    }

    string popRear()
    {
        if (!tail) // Cannot pop from empty list
        {
            return "";
        }
        else if (head == tail) // When only one item in list
        {
            string returnMe = tail->data;
            delete tail;
            head = tail = nullptr;
            size--;
            return returnMe;
        }
        else
        {
            string returnMe = tail->data; // Save data for return
            Node *deleteMe = tail;     // Save pointer for deletion
            tail = tail->prev;         // Move tail up
            tail->next = nullptr;      // Double linked list ends in nullptr

            delete deleteMe;
            size--;
            return returnMe;
        }
    }

    
    string popAt(int loc)
    {
        if (!head) // Cannot pop from empty list
        {
            return "";
        }
        else if (loc < 0 || loc > size - 1) // Cannot access out of bounds
        {
            return "";
        }
        else if (loc == 0) // loc is frontmost item
        {
            return popFront();
        }
        else if (loc == size - 1) // loc is rearmost item
        {
            return popRear();
        }
        else // Travels through until it reaches index
        {
            Node *temp = head;
            for (int i = 0; i < loc; i++)
            {
                temp = temp->next;
            }
            string returnMe = temp->data;
            temp->prev->next = temp->next; // Links temp->prev Node to temp->next Node
            temp->next->prev = temp->prev; // and vice-versa
            delete temp;

            return returnMe;
        }
    }

    int find(string val)
    {
        Node *temp = head;
        int i = 0;

        while (temp)
        {
            if (val == temp->data) // If found, return index
            {
                return i;
            }
            else // Move to next node
            {
                temp = temp->next;
                i++;
            }
        }
        return -1; // Returns -1 if not found
    }

    void print()
    {
        if (head) // If head exists
        {
            Node *travel = head; // travel points to head

            cout << "[";

            while (travel) // Travels until travel == nullptr
            {
                cout << travel->data; // Print data from node
                if (travel->next)
                {
                    cout << ", ";
                }
                travel = travel->next; // Move to next node
            }
            cout << ']' << endl;
        }
    }

    void print(ofstream &outfile)
    {
        if (head) // If head exists
        {
            Node *travel = head; // travel points to head

            outfile << "[";

            while (travel) // Travels until travel == nullptr
            {
                outfile << travel->data; // Print data from node
                if (travel->next)
                {
                    outfile << ", ";
                }
                travel = travel->next; // Move to next node
            }
            outfile << ']' << endl;
        }
    }

    int getSize()
    {
        return size;
    }

    friend ostream &operator<<(ostream &os, const List &V)
    {
        os << fixed << setprecision(2);

        Node *temp = V.head;
        os << "[ ";
        while (temp)
        {
            os << temp->data;
            if (temp->next)
            {
                os << ", ";
            }
            temp = temp->next;
        }
        os << " ]";
        return os;
    }

    friend ofstream &operator<<(ofstream &of, const List &V)
    {
        of << fixed << setprecision(2);

        Node *temp = V.head;
        of << "[ ";
        while (temp)
        {
            of << temp->data;
            if (temp->next)
            {
                of << ", ";
            }
            temp = temp->next;
        }
        of << " ]";
        return of;
    }

    string &operator[](int index)
    {
        if (index < 0 || index >= size)
        {
            exit(0);
        }
        else
        {
            Node *temp = head;
            for (int i = 0; i < index; i++)
            {
                temp = temp->next;
            }
            return temp->data;
        }
    }

    List &operator=(const List &rhs)
    {
        if (this != &rhs)
        {
            this->~List();
            List other(rhs);
            this->pushRear(other);
        }
        return *this;
    }
};
