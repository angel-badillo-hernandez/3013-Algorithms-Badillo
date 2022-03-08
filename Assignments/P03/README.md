## P02 - Processing in Trie Tree Time
### Angel Badillo
### Description:

Simulation of performing operations on a Trie.
Times how long it takes to load the file data to the Trie.
Times how long it takes get partial matches from a Trie.
Gets chars by "getching" and creates substrings to use for finding
partial matches. Minor note, Milliseconds() works because I edited Prof. Griffin's
"timer.hpp" file.


### Files

|   #   | File                             | Description                       |
| :---: | -------------------------------- | --------------------------------- |
|   1   | [main.cpp](main.cpp)             | Main driver of program            |
|   2   | [Trie.hpp](Trie.hpp)             | Header for Trie Class             |
|   3   | [mygetch.hpp](mygetch.hpp)       | Header for "Getch"                |
|   4   | [termcolor.hpp](termcolor.hpp)   | Header for color text in terminal |
|   5   | [timer.hpp](timer.hpp)           | Header for Timers                 |
|   6   | [dictionary.txt](dictionary.txt) | File to test program              |
|   7   | [out1.png](out1.png)             | Screenshot of the output          |
|   8   | [out2.png](out2.png)             | Screenshot of the output          |
|   9   | [out3.png](out3.png)             | Screenshot of the output          |
|  10   | [out4.png](out4.png)             | Screenshot of the output          |



### Instructions

- Just compile and run it using example below. The input file is hardcoded, since <br>
  directions said to use [dictionary.txt](dictionary.txt), and did not specify otherwise.

- Example Command:
  - g++ main.cpp -o main
  - ./main