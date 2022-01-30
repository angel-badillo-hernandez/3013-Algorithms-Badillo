/**************************************************************************************
*
*  Author:           Angel Badillo Hernandez  / @It-Is-Legend27
*  Email:            badilloa022402@gmail.com / abadillo0224@my.msutexas.edu
*  Label:            P01
*  Title:            Resizing the Stack
*  Course:           CMPS-3013-201
*  Semester:         Spring 2022
*
*  Description:
*        Implementation of an array-based stack.
*
*  Usage:
*        g++ main.cpp -o main
         ./main inputFileName GrowThreshold ShrinkThreshold GrowFactor ShrinkFactor
                      or
         ./main inputFileName
*
*  Files:            main.cpp
***************************************************************************************/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/**
 * ArrayStack
 *
 * Description:
 *      Array-based stack
 *
 * Public Methods:
 *      - See class below
 *
 * Usage:
 *      - See the main program
 *
 */
class ArrayStack
{
private:
  int *A;              // Pointer to array of int's
  int size;            // Current max stack size
  int top;             // Top of stack
  double growThres;    // Capacity to reach before growing
  double shrinkThres;  // Capacity to reach before shrinking
  double growFactor;   // Growth factor
  double shrinkFactor; // Shrink factor
  int resizeCount;     // Number of times stack was resized
public:
  /**
   * Public: ArrayStack
   *
   * @brief Construct a new Array Stack object with no params
   *
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
   * Public: ArrayStack
   *
   * @brief Construct a new Array Stack object using size param
   *
   * @param s
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

  /**
   * Public: ~ArrayStack
   *
   * @brief Destroy the Array Stack object
   *
   */
  ~ArrayStack()
  {
    delete[] A;
  }

  /**
   * Public: SetGrowThres
   *
   * @brief Set the Grow Thres object
   *
   * @param gT double, capacity to reach before growing stack
   */
  void SetGrowThres(double gT) { growThres = gT; }

  /**
   * Public: SetShrinkThres
   *
   * @brief Set the Shrink Thres object
   *
   * @param sT double, capacity to reach before shrink stack
   */
  void SetShrinkThres(double sT) { shrinkThres = sT; }

  /**
   * Public: SetGrowFactor
   *
   * @brief Set the Grow Factor object
   *
   * @param gF double, factor by which to increase current size
   */
  void SetGrowFactor(double gF) { growFactor = gF; }

  /**
   * Public: SetShrinkFactor
   *
   * @brief Set the Shrink Factor object
   *
   * @param sF double, factor by which to decrease current size
   */
  void SetShrinkFactor(double sF) { shrinkFactor = sF; }

  /**
   * Public: GetGrowThres
   *
   * @brief Get the Grow Thres object
   *
   * @return double
   */
  double GetGrowThres() { return growThres; }

  /**
   * Public: GetShrinkThres
   *
   * @brief Get the Shrink Thres object
   *
   * @return double
   */
  double GetShrinkThres() { return shrinkThres; }

  /**
   * Public: GetGrowFactor
   *
   * @brief Get the Grow Factor object
   *
   * @return double
   */
  double GetGrowFactor() { return growFactor; }

  /**
   * Public: GetShrinkFactor
   *
   * @brief Get the Shrink Factor object
   *
   * @return double
   */
  double GetShrinkFactor() { return shrinkFactor; }

  /**
   * Public: GetSize
   *
   * @brief Get the Size object
   *
   * @return int
   */
  int GetSize() { return size; }

  /**
   * Public: GetResizeCount
   *
   * @brief Get the Resize Count object
   *
   * @return int
   */
  int GetResizeCount() { return resizeCount; }

  /**
   * Public: Empty
   *
   * @brief Tests if stack is empty
   *
   * @return true if empty, false otherwise
   */
  bool Empty()
  {
    return (top <= -1);
  }

  /**
   * Public: Full
   *
   * @brief Tests if stack is full
   *
   * @return true if full, false otherwise
   */
  bool Full()
  {
    return (top >= size - 1);
  }

  /**
   * Public: Peek
   *
   * @brief Returns top value without altering the stack
   *
   * @return int
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
   * Public: Pop
   *
   * @brief Returns top value and removes it from stack, also resizes stack if
   *        it reaches the capacity to shrink
   *
   * @return int
   */
  int Pop()
  {
    int temp;

    if (!Empty())
    {
      temp = A[top];
      top--;
      CheckResize();
      return temp;
    }

    return -99; // some sentinel value
                // not a good solution
  }

  /**
   * Public: Print
   *
   * @brief Prints stack to standard out
   *
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
   * Public: Push
   *
   * @brief Adds an item to top of stack
   *
   * @param x int, value to be stored
   *
   * @return true if operation is successful, false otherwise
   */
  bool Push(int x)
  {
    // Stack will never get full so no need to check
    A[++top] = x;
    CheckResize();
    return true;
  }

  /**
   * Public: GrowContainer
   *
   * @brief Enlarges the container by the growFactor
   *
   */
  void GrowContainer()
  {
    int newSize = size * growFactor; // increase size of original
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

  /**
   * Public: ShrinkContainer
   *
   * @brief Reduces the container by the shrinkFactor
   *
   */
  void ShrinkContainer()
  {
    int newSize = size * shrinkFactor; // decrease size of original
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

protected:
  /**
   * Protected: CheckResize
   *
   * @brief Checks the current capacity of the container, then determines
   *        whether to grow, shrink, or not alter the container
   *
   */
  void CheckResize()
  {
    // Capacity of how full stack is (0.0-1.0)
    double capacity = (double)(top + 1) / (double)size;

    // If past or at thres, grow
    if (capacity >= growThres)
      GrowContainer();
    // If below or at thres & newSize is at or equal to 10, shrink
    else if ((capacity <= shrinkThres) && (size * shrinkFactor >= 10))
      ShrinkContainer();
    // Does not alter container
    else
      return;
  }
};

/**
 * EmptyFile
 *
 * @brief Tests if file is empty by looking ahead (without advancing) in the
 *        stream and testing whether or not it results in
 *        ifstream::traits_type::eof() (end of file).
 *
 * @param infile ifstream object by reference
 *
 * @return true if empty, false otherwise.
 */
bool EmptyFile(ifstream &infile) { return infile.peek() == ifstream::traits_type::eof(); }

int main(int argc, char **argv)
{
  ArrayStack S;    // Array-based stack of integers
  ifstream infile; // Input file stream
  int maxSize = 0; // Maximum size reached of the stack
  int opCount = 0; // Total number of operations performed on the stack
  int val;         // Value to be read in from file

  // Program Header
  cout << string(90, '#') << "\nProgram 1 - Resizing the Stack\nCMPS 3013\nAngel Badillo Hernandez\n\n";

  // Determines when default values need to be used, or to end program if file
  // is not specified, or too many arguments
  switch (argc)
  {
  case 6: // If there is a 6th arg, fallthrough
    S.SetShrinkFactor(stod(argv[5]));
    [[fallthrough]];
  case 5: // If there is a 5th arg, fallthrough
    S.SetGrowFactor(stod(argv[4]));
    [[fallthrough]];
  case 4: // If there is a 4th arg, fallthrough
    S.SetShrinkThres(stod(argv[3]));
    [[fallthrough]];
  case 3: // If there is a 3rd arg, break from switch
    S.SetGrowThres(stod(argv[2]));
    break;
  case 2: // Uses all default values
    break;
  case 1: // No input file
    cout << "No file specified.\nTry " << argv[0] << " inputFileName\nor\n"
         << argv[0] << " inputFileName GrowThreshold ShrinkThreshold GrowFactor ShrinkFactor\n"
         << string(90, '#') << '\n';
    return 1;
    break;
  default: // Too many arguments
    cout << "Too many arguments.\nTry " << argv[0] << " inputFileName\nor\n"
         << argv[0] << " inputFileName GrowThreshold ShrinkThreshold GrowFactor ShrinkFactor\n"
         << string(90, '#') << '\n';
    return 1;
    break;
  }

  infile.open(argv[1]);             // Attempts to open file
  if (EmptyFile(infile) || !infile) // If empty or not opened, end program
  {
    cout << "Input file is not valid!\n"
         << string(90, '#') << '\n';
    return 1;
  }

  while (infile >> val) // While able to read in, loop through the whole file
  {
    if (val % 2 == 0)   // If even, push this value to stack
    {
      S.Push(val);
      opCount++;
    }
    else               // If odd, pop a value from stack
    {
      if (!S.Empty())  // Prevent pop if empty stack, but will count operation
      {
        S.Pop();
      }
      opCount++;
    }

    if (maxSize < S.GetSize()) // Stores current size if greater than maxSize
    {
      maxSize = S.GetSize();
    }
  }

  // Prints results of all the ops to standard output
  cout << "Config Params:\nFullThreshold: " << S.GetGrowThres() << "\nShrinkThreshold: " << S.GetShrinkThres()
       << "\nGrow Ratio: " << S.GetGrowFactor() << "\nShrink Ratio: " << S.GetShrinkFactor() << "\n\nProcessed "
       << opCount << " commands.\n\nMax Stack Size: " << maxSize << "\nEnd Stack Size: " << S.GetSize()
       << "\nStack Resized: " << S.GetResizeCount() << " times.\n"
       << string(90, '#') << '\n';

  infile.close();
  return 0;
}