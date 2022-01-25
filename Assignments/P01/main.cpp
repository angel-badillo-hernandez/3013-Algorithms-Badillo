/*****************************************************************************
*
*  Author:           Angel Badillo Hernandez  / @It-Is-Legend27
*  Email:            badilloa022402@gmail.com / abadillo0224@my.msutexas.edu
*  Label:            P01
*  Title:            Resizing the Stack
*  Course:           CMPS-3013-201
*  Semester:         Spring 2022
*
*  Description:
*        Implementation of an array based stack.
*
*  Usage:
*        g++ main.cpp -o main
         g++ ./main
*
*  Files:            main.cpp
*****************************************************************************/

#include <iostream>

using namespace std;

/**
 * ArrayStack
 *
 * Description:
 *      Array based stack
 *
 * Public Methods:
 *      - See class below
 *
 * Usage:
 *      - See main program
 *
 */
class ArrayStack
{
private:
  int *A;                    // pointer to array of int's
  int size{10};              // current max stack size
  int top{-1};               // top of stack
  float tooFullThres{1.0};   // Threshold for when to enlarge
  float tooEmptyThres{0.15}; // Threshold for when to shrink
  float enlargeThres{2.0};   // Enlarging ratio
  float reduceThres{0.5};    // Shrinking ratio

public:
  /**
   * ArrayStack
   *
   * Description:
   *      Constructor no params
   *
   * Params:
   *     - None
   *
   * Returns:
   *     - NULL
   */
  ArrayStack(): size(10), top(-1), tooFullThres(1.0), tooEmptyThres(0.15), enlargeThres(2.0), reduceThres(0.5)
  {
    A = new int[size];
    
  }

  /**
   * ArrayStack
   *
   * Description:
   *      Constructor size param
   *
   * Params:
   *     - int size
   *
   * Returns:
   *     - NULL
   */
  ArrayStack(int s, float fT, float eT, float grow, float shrink): size(s), tooFullThres(fT), tooEmptyThres(eT), enlargeThres(grow), reduceThres(shrink)
  {
    A = new int[s];
  }

  ArrayStack(int s, char** argv)
  {
    size = s;
    A = new int[s];
    top = -1;

    tooFullThres = stod(argv[1]);
    tooEmptyThres = stod(argv[2]);
    enlargeThres = stod(argv[3]);
    reduceThres = stod(argv[4]);
  }

  /**
   * Public bool: Empty
   *
   * Description:
   *      Stack empty?
   *
   * Params:
   *      NULL
   *
   * Returns:
   *      [bool] true = empty
   */
  bool Empty()
  {
    return (top <= -1);
  }


  void CheckResize()
  {
    if( float(top)/(size-1) >= tooFullThres)
    {
      ContainerGrow();
    }
    else if( float(top)/(size-1) <= tooEmptyThres)
    {
      ContainerShrink();
    }
    else
    {
      return;
    }
  }

  /**
   * Public bool: Full
   *
   * Description:
   *      Stack full?
   *
   * Params:
   *      NULL
   *
   * Returns:
   *      [bool] true = full
   */
  bool Full()
  {
    return (top >= size - 1);
  }

  /**
   * Public int: Peek
   *
   * Description:
   *      Returns top value without altering the stack
   *
   * Params:
   *      NULL
   *
   * Returns:
   *      [int] top value if any
   */
  int Peek()
  {
    if (!Empty())
    {
      return A[top];
    }

    return -99; // some sentinel value
                // not a good solution
  }

  /**
   * Public int: Pop
   *
   * Description:
   *      Returns top value and removes it from stack
   *
   * Params:
   *      NULL
   *
   * Returns:
   *      [int] top value if any
   */
  int Pop()
  {
    if (!Empty())
    {
      return A[top--];
    }

    return -99; // some sentinel value
                // not a good solution
  }

  /**
   * Public void: Print
   *
   * Description:
   *      Prints stack to standard out
   *
   * Params:
   *      NULL
   *
   * Returns:
   *      NULL
   */
  void Print()
  {
    for (int i = 0; i <= top; i++)
    {
      cout << A[i] << " ";
    }
    cout << endl;
  }

  /**
   * Public bool: Push
   *
   * Description:
   *      Adds an item to top of stack
   *
   * Params:
   *      [int] : item to be added
   *
   * Returns:
   *      [bool] ; success = true
   */
  bool Push(int x)
  {
    if (Full())
    {
      ContainerGrow();
    }
    if (!Full())
    {
      A[++top] = x;
      return true;
    }

    return false;
  }

  /**
   * Public void: ContainerGrow
   *
   * Description:
   *      Resizes the container for the stack by doubling
   *      its capacity
   *
   * Params:
   *      NULL
   *
   * Returns:
   *      NULL
   */
  void ContainerGrow()
  {
    int newSize = size * 2;    // double size of original
    int *B = new int[newSize]; // allocate new memory

    for (int i = 0; i < size; i++)
    { // copy values to new array
      B[i] = A[i];
    }

    delete[] A; // delete old array

    size = newSize; // save new size

    A = B; // reset array pointer
  }

  /**
   * Public void: ContainerShrink
   *
   * Description:
   *      Resizes the container for the stack by halving
   *      its capacity
   *
   * Params:
   *      NULL
   *
   * Returns:
   *      NULL
   */
  void ContainerShrink()
  {
    int newSize = size / 2;    // Halve the size of the original container
    int *B = new int[newSize]; // Allocate new memory

    for (int i = 0; i < newSize; i++)
    // Copy values to new array
      B[i] = A[i];

    delete[] A;     // Delete old array

    size = newSize; // Save new size

    A = B;          // Reset array pointer
  }
};


int main(int argc, char** argv)
{
  float i = stod(argv[2]);
  cout << i;
  ArrayStack s;
}