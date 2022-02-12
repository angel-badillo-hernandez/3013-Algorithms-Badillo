## P02 - Processing in linear time
### Angel Badillo
### Description:

Simulation of performing operations on a trie.
Times how long it takes to load the file data to the trie.
Times how long it takes get partial matches from a trie.
Gets chars by "getching" and creates substrings to use for finding
partial matches. Minor note, Milliseconds() works because I edited Prof. Griffin's
"timer.hpp" file.


### Files

|   #   | File                                 | Description                       |
| :---: | ------------------------------------ | --------------------------------- |
|   1   | [main.cpp](main.cpp)                 | Main driver of program            |
|   2   | [Trie.hpp](Trie.hpp)                 | Header for Trie Class             |
|   3   | [mygetch.hpp](mygetch.hpp)           | Header for "Getch"                |
|   4   | [termcolor.hpp](termcolor.hpp)       | Header for color text in terminal |
|   5   | [timer.hpp](timer.hpp)               | Header for Timers                 |
|   6   | [dictionary.txt](dictionary.txt)     | File to test program              |
|   7   | [animal_names.txt](animal_names.txt) | Smaller file to test program      |



### Instructions

- Just compile and run it using example below. The input file is hardcoded, since <br>
  directions said to use [dictionary.txt](dictionary.txt), and did not specify otherwise.

- Example Command:
  - g++ main.cpp -o main
  - ./main