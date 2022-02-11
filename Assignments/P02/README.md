## P02 - Processing in linear time
### Angel Badillo
### Description:

Simulation of performing operations on a singely linked list.
Times how long it takes to load the file data to the list.
Times how long it takes get partial matches from a list.
Gets chars by "getching" and creates substrings to use for finding
partial matches. Minor note, Milliseconds() works because I edited Prof. Griffin's
"timer.hpp" file.


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

- Just compile and run it using example below. The input file is hardcoded, since <br>
  directions said to use [dictionary.txt](dictionary.txt), and did not specify otherwise.

- Example Command:
  - g++ main.cpp -o main
  - ./main