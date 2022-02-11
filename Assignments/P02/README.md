## P02 - Processing in linear time
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

|   #   | File                                 | Description                       |
| :---: | ------------------------------------ | --------------------------------- |
|   1   | [main.cpp](main.cpp)                 | Main driver of program            |
|   2   | [List.hpp](List.hpp)                 | Header for Linked-List Class      |
|   3   | [mygetch.hpp](mygetch.hpp)           | Header for "Getch"                |
|   4   | [termcolor.hpp](termcolor.hpp)       | Header for color text in terminal |
|   5   | [timer.hpp](timer.hpp)               | Header for Timers                 |
|   6   | [dictionary.txt](dictionary.txt)     | File to test program              |
|   7   | [animal_names.txt](animal_names.txt) | Smaller file to test program      |
|   8   | [out1.jpg](out1.jpg)                 | Screenshot of the output          |
|   9   | [out2.jpg](out2.jpg)                 | Screenshot of the output          |
|  10   | [out3.jpg](out3.jpg)                 | Screenshot of the output          |
|  11   | [out4.jpg](out4.jpg)                 | Screenshot of the output          |


### Instructions

- Just compile and run it using example below. Have an input file with <br>
  with odd and even integers for use in the program.

- Example Command:
  - g++ main.cpp -o main
  - ./main inputFileName <br>
  or
  - ./main inputFileName GrowThreshold ShrinkThreshold GrowFactor ShrinkFactor