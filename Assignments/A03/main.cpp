/*****************************************************************************
*
*  Author:           Angel Badillo Hernandez  / @It-Is-Legend27
*  Email:            badilloa022402@gmail.com / abadillo0224@my.msutexas.edu
*  Label:            A03
*  Title:            Commenting Code
*  Course:           CMPS-3013-201
*  Semester:         Spring 2022
*
*  Description:
*        Simple Linked-List. The assignment is to comment this code.
*
*  Usage:
*        g++ main.cpp -o main
         g++ ./main
*
*  Files:            main.cpp
*****************************************************************************/

#include <iostream>

using namespace std;

int A[100]; // Array of integers, 100 elements

/**
 * Node
 *
 * Description:
 *      This struct stores an integer and a Node pointer. Meant to be used for Linked Lists.
 *
 * Public Methods:
 *                          Node()
 *                          Node(int n)
 *
 * Private Methods:
 *      None.
 *
 * Usage:
 *
 *      Node() head;                                // Create instance of Node like this
 *      Node(3) temp;                               // or this.
 */
struct Node
{

    int x;
    Node *next;

    /**
     * Public : Node
     *
     * @brief Construct a new Node object with default values.
     *
     * @param None
     *
     * @return Nothing.
     */
    Node()
    {
        x = -1;
        next = NULL;
    }

    /**
     * Public : Node
     *
     * @brief Construct a new Node object with a given value.
     *
     * @param n An integer.
     *
     * @return Nothing.
     */
    Node(int n)
    {
        x = n;
        next = NULL;
    }
};

/**
 * List
 *
 * Description:
 *      This class is a Linked List. It is comprised of a series of Nodes
 *      that are linked to each other.
 *
 * Public Methods:
 *                          List()
 *      void                Push(int val)
 *      void                Insert(int val)
 *      void                PrintTail()
 *      string              Print()
 *      int                 Pop()
 *      List                operator+(const List& rhs)
 *      int                 operator[](int index)
 *      ostream&            operator<<(ostream& os, List L)
 *
 * Private Methods:
 *      None.
 *
 * Usage:
 *
 *      List L();                               // Create instance of List.
 *      L.Push(1);                              // Push a new Node to the end of the list.
 *      L.Insert(2);                            // Inserts a new Node to the front of the list.
 *      int x = L.Pop();                        // Removes Node from List and returns it.
 *      L.PrintTail();                          // Prints tail of the list.
 *      string y = L.Print();                   // Returns a string containing contents of the list.
 *      cout << L;                              // Prints list
 *      int z = L[0];                           // Returns value of the Node at specified position of the list.
 *      List P = L + L;                         // Returns a new List containing contents of both lists.
 */
class List
{
private:
    Node *Head; // Beginning of the list
    Node *Tail; // End of the list
    int Size;   // Number of Nodes in the list

public:
    /**
     * Public : List
     *
     * @brief Construct a new empty List object.
     *
     * @param None
     *
     * @return Nothing.
     *
     */
    List()
    {
        Head = Tail = NULL;
        Size = 0;
    }

    /**
     * Public : Push
     *
     * @brief Appends an integer to the list.
     *
     * @param val An integer to be stored.
     *
     * @return Nothing.
     */
    void Push(int val)
    {
        // allocate new memory and init node
        Node *Temp = new Node(val);

        if (!Head && !Tail)
        {
            Head = Tail = Temp;
        }
        else
        {
            Tail->next = Temp;
            Tail = Temp;
        }
        Size++;
    }

    /**
     * Public : Insert
     *
     * @brief Prepends an integer to the list.
     *
     * @param val An integer to be stored.
     *
     * @return Nothing.
     */
    void Insert(int val)
    {
        // allocate new memory and init node
        Node *Temp = new Node(val);

        // figure out where it goes in the list

        Temp->next = Head;
        Head = Temp;
        if (!Tail)
        {
            Tail = Head;
        }
        Size++;
    }

    /**
     * Public : PrintTail
     *
     * @brief Prints the last integer in the list to standard output.
     *
     * @param None
     *
     * @return Nothing.
     */
    void PrintTail()
    {
        cout << Tail->x << endl;
    }

    /**
     * Public : Print
     *
     * @brief "Prints" the contents of the list to a string object.
     *
     * @param None
     *
     * @return string containing contents of the list.
     */
    string Print()
    {
        Node *Temp = Head;
        string list;

        while (Temp != NULL)
        {
            list += to_string(Temp->x) + "->";
            Temp = Temp->next;
        }

        return list;
    }

    /**
     * Public : Pop
     *
     * @warning Method not implemented.
     *
     * @brief Removes an item from the list, and returns it.
     *
     * @param None
     *
     * @return int value that was removed from list.
     */
    int Pop()
    {
        Size--;
        return 0;
    }

    /**
     * Public : operator+
     *
     * @brief Allows two lists to be appended to a new list.
     *
     * @param Rhs A const List object by reference.
     *
     * @return List containing the contents of two lists added together.
     */
    List operator+(const List &Rhs)
    {
        // Create a new list that will contain both when done
        List NewList;

        // Get a reference to beginning of local list
        Node *Temp = Head;

        // Loop through local list and Push values onto new list
        while (Temp != NULL)
        {
            NewList.Push(Temp->x);
            Temp = Temp->next;
        }

        // Get a reference to head of Rhs
        Temp = Rhs.Head;

        // Same as above, loop and push
        while (Temp != NULL)
        {
            NewList.Push(Temp->x);
            Temp = Temp->next;
        }

        // Return new concatenated version of lists
        return NewList;
    }

    /**
     * Public : operator[]
     *
     * @brief Returns the value of an item in the list at a given index.
     *
     * @param index An integer, the position of the item in the list.
     *
     * @return int containing the value of the item being seached for.
     */
    int operator[](int index)
    {
        Node *Temp = Head;

        if (index >= Size)
        {
            cout << "Index out of bounds, exiting";
            exit(0);
        }
        else
        {

            for (int i = 0; i < index; i++)
            {
                Temp = Temp->next;
            }
            return Temp->x;
        }
    }

    /**
     * Public : operator<<
     *
     * @brief Prints the contents of the list to standard output.
     *
     * @param os An ostream object, by reference.
     *
     * @param L  A List object, by reference.
     *
     * @return ostream& containing the contents of the list.
     */
    friend ostream &operator<<(ostream &os, const List &L)
    {
        os << L.Print();
        return os;
    }
};

int main(int argc, char **argv)
{
    List L1; // An empty list
    List L2; // Another empty list

    // Pushes integers 0-24 to the list L1
    for (int i = 0; i < 25; i++)
    {
        L1.Push(i);
    }

    // Pushes integers 50-100 to list L2
    for (int i = 50; i < 100; i++)
    {
        L2.Push(i);
    }

    // cout << L1 << endl;
    
    L1.PrintTail();        // Prints tail of L1
    L2.PrintTail();        // Prints tail of L2

    List L3 = L1 + L2;     // Concatenates L1 and L2 to a new list L3
    cout << L3 << endl;    // Prints the contents of L3

    cout << L3[5] << endl; // Prints the 6th item in L3

    return 0;
}