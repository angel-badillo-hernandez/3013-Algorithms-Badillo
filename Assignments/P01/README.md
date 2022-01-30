## P01 - Resizing the Stack
### Angel Badillo
### Description:

This program simulates the usage of an array-based stack that resizes
(enlarges or reduces) depending on if it passes certain thresholds.
It either uses default values or uses command line arguments to set
thresholds and resize factors. The program will read numbers from a file.
If the number is even, it pushes it to the stack, if odd, it pops a number
from the stack. Once the entire file has been read, the results of all the
operations will be printed to standard output.


### Files

|   #   | File                            | Description              |
| :---: | ------------------------------- | ------------------------ |
|   1   | [main.cpp](main.cpp)            | Main driver of program   |
|   2   | [nums_tests.dat](nums_test.dat) | File to test program     |
|   3   | [p01Output.jpg](p01Output.jpg)  | Screenshot of the output |
|   4   | [test.txt](test.txt)            | File to test program     |



### Instructions

- Just compile and run it using example below. Have an input file with <br>
  with odd and even integers for use in the program.

- Example Command:
  - g++ main.cpp -o main
  - ./main inputFileName <br>
  or
  - ./main inputFileName GrowThreshold ShrinkThreshold GrowFactor ShrinkFactor