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
#include <fstream>
#include <string>

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
  int *A;              // pointer to array of int's
  int size;            // current max stack size
  int top;             // top of stack
  double growThres;    // Capacity to reach before growing
  double shrinkThres;  // Capacity to reach before shrinking
  double growFactor;   // Growth factor
  double shrinkFactor; // Shrink factor
  int resizeCount;

  // top = number of items in the stack + 1
  // size = array size

  // size = 100
  // (top + 1) / size

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
  ArrayStack()
  {
    size = 10;
    A = new int[size];
    top = -1;
    growThres = 1.00;
    shrinkThres = 0.15;
    growFactor = 2.0;
    shrinkFactor = 0.5;
    resizeCount = 0;
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
  ArrayStack(int s)
  {
    size = s;
    A = new int[s];
    top = -1;
    growThres = 1.00;
    shrinkThres = 0.15;
    growFactor = 2.0;
    shrinkFactor = 0.5;
    resizeCount = 0;
  }

  void SetGrowThres(double gT) { growThres = gT; }

  void SetShrinkThres(double sT) { shrinkThres = sT; }

  void SetGrowFactor(double gF) { growFactor = gF; }

  void SetShrinkFactor(double sF) { shrinkFactor = sF; }

  double GetGrowThres() { return growThres; }

  double GetShrinkThres() { return shrinkThres; }

  double GetGrowFactor() { return growFactor; }

  double GetShrinkFactor() { return shrinkFactor; }

  int GetSize() {return size;}

  int GetResizeCount() {return resizeCount;}

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
    CheckResize();

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
    CheckResize();

    if (!Full())
    {
      A[++top] = x;

      return true;
    }

    return false;
  }

  /**
   * Public void: GrowContainer
   *
   * Description:
   *      GrowContainers the container for the stack by doubling
   *      its capacity
   *
   * Params:
   *      NULL
   *
   * Returns:
   *      NULL
   */
  void GrowContainer()
  {
    int newSize = size * growFactor; // double size of original
    int *B = new int[newSize];       // allocate new memory

    for (int i = 0; i < top; i++)
    { // copy values to new array
      B[i] = A[i];
    }

    delete[] A; // delete old array

    size = newSize; // save new size

    A = B; // reset array pointer

    resizeCount++;
  }

  void ShrinkContainer()
  {
    int newSize = size * shrinkFactor; // double size of original
    int *B = new int[newSize];         // allocate new memory

    for (int i = 0; i < top; i++)
    { // copy values to new array
      B[i] = A[i];
    }

    delete[] A; // delete old array

    size = newSize; // save new size

    A = B; // reset array pointer

    resizeCount++;
  }

  void CheckResize()
  {
    double capacity = (top + 1) / size;

    if (capacity >= growThres)
    {
      GrowContainer();
    }
    else if ((capacity <= shrinkThres) && (size*shrinkFactor > 10))
    {
      ShrinkContainer();
    }
    else
    {
      return;
    }
  }
};

int main(int argc, char **argv)
{
  ArrayStack S;
  ifstream infile;
  ofstream outfile;

  cout << string(90, '#') << "\nProgram 1 - Resizing the Stack\nCMPS 3013\nAngel Badillo Hernandez\n";

  switch (argc)
  {
  case 7:
    S.SetShrinkFactor(stod(argv[6]));
    [[fallthrough]];
  case 6:
    S.SetGrowFactor(stod(argv[5]));
    [[fallthrough]];
  case 5:
    S.SetShrinkThres(stod(argv[4]));
    [[fallthrough]];
  case 4:
    S.SetGrowThres(stod(argv[3]));
    break;
  case 3:
    break; // Default values
  case 2:
    [[fallthrough]];
  case 1:
    cout << "\nNo file(s) specified.\nTry " << argv[0] << " inputFileName outputFileName\nor\n"
         << argv[0] << " inputFileName outputFileName GrowThreshold ShrinkThreshold GrowFactor ShrinkFactor\n"
         << string(90, '#') << '\n';
    return 1;
    break;
  default:
    cout << "\nToo many arguments.\nTry " << argv[0] << " inputFileName outputFileName\nor\n"
         << argv[0] << " inputFileName outputFileName GrowThreshold ShrinkThreshold GrowFactor ShrinkFactor\n"
         << string(90, '#') << '\n';
    return 1;
    break;
  }

  infile.open(argv[1]);
  outfile.open(argv[2]);

  int maxSize = 0;
  int val;
  int opCount = 0;
  infile >> val;

  while(!infile.eof())
  {
    if(val%2==0)
    {
      S.Push(val);
      opCount++;
      infile >> val;
    }
    else
    {
      S.Pop();
      opCount++;
      infile >> val;
    }

    if(maxSize < S.GetSize())
    {
      maxSize = S.GetSize();
    }
  }

  infile.close();
  outfile.close();
  return 0;
}