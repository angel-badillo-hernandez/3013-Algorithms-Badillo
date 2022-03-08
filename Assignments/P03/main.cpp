/**************************************************************************************
*
*  Author:           Angel Badillo Hernandez  / @It-Is-Legend27
*  Email:            badilloa022402@gmail.com / abadillo0224@my.msutexas.edu
*  Label:            P03
*  Title:            Processing in Trie Tree Time
*  Course:           CMPS-3013-201
*  Semester:         Spring 2022
*
*  Description:
*        Simulation of performing operations on a Trie Tree.
         Times how long it takes to load the file data to the Trie.
         Times how long it takes get partial matches from a Trie.
         Gets chars by "getching" and creates substrings to use for finding
         partial matches. Minor note, Milliseconds() works because I edited Prof. Griffin's
         "timer.hpp" file. Another note, I used this source for getting the basis of
         an unordered_map based Trie, but most of the code in Trie.hpp is largely my own.
         https://www.techiedelight.com/memory-efficient-trie-implementation-using-map-insert-search-delete/
*
*  Usage:
*        g++ main.cpp -o main
         ./main
*
*  Files:            main.cpp
                     Trie.hpp
                     timer.hpp
                     mygetch.hpp
                     termcolor.hpp
                     dictionary.txt
***************************************************************************************/
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include "Trie.hpp"
#include "mygetch.hpp"
#include "termcolor.hpp"
#include "timer.hpp"

// Shortcuts for changing terminal colors
#define RED termcolor::red
#define BLUE termcolor::blue
#define YELLOW termcolor::yellow
#define GREEN termcolor::green
#define MAGENTA termcolor::magenta
#define GREY termcolor::grey

using namespace std;

/**
 * load_trie
 * @brief Opens an input file and reads in the data to the Trie.
 *        Makes every string fully lower case while inserting to Trie.
 * 
 * @param tree Trie to store data in.
 * @param file_name input file name.
 */
void load_trie(Trie &tree, string file_name);

int main()
{
    char k;                 // holder for character being typed
    string word = "";       // var to concatenate letters to
    Trie dictionary;        // Trie of words
    vector<string> matches; // any matches found in vector of dictionary
    int loc;                // location of substring to change its color
    int numMatches;         // loop control variable for printing matches

    // Program Header
    cout << GREEN << string(90, '#')
         << "\nProgram 2 - Processing in Trie Tree Time\nCMPS 3013\nAngel Badillo Hernandez\n"
         << string(90, '#') << '\n'
         << termcolor::reset;

    Timer T;   // create a timer
    T.Start(); // start it

    load_trie(dictionary, "dictionary.txt");

    T.End(); // end the current timer

    // print out how long it took to load the animals file
    cout << YELLOW << T.Seconds() << termcolor::reset << " seconds to read in data from dictionary.txt\n";
    cout << BLUE << T.MilliSeconds() << termcolor::reset << " milliseconds to read in data from dictionary.txt\n";

    cout << "Type keys and watch what happens. Type capital Z to quit." << '\n';

    // While capital Z is not typed keep looping
    while ((k = getch()) != 'Z')
    {

        // Tests for a backspace and if pressed deletes
        // last letter from "word".
        if ((int)k == 127)
        {
            if (word.size() > 0)
            {
                word = word.substr(0, word.size() - 1);
            }
        }
        else
        {
            // Make sure a letter was pressed and only letter
            if (!isalpha(k))
            {
                cout << "Letters only!" << endl;
                continue;
            }

            // We know its a letter, lets make sure its lowercase.
            // Any letter with ascii value < 97 is capital so we
            // lower it.
            if ((int)k < 97)
            {
                k += 32;
            }
            word += k; // append char to word
        }

        T.Start(); // Start timer for finding matches

        // Find any strings in the array that partially match
        // our substr word
        dictionary.find_all(word, matches);

        T.End(); // End timer for finding matches

        if ((int)k != 32)
        { // if k is not a space print it

            cout << YELLOW << T.Seconds() << termcolor::reset << " seconds to get matches.\n";
            cout << BLUE << T.MilliSeconds() << termcolor::reset << " milliseconds to get matches\n";
            cout << "Keypressed: " << BLUE << k << " = " << (int)k << termcolor::reset << '\n';
            cout << "Current Substring: " << RED << word << termcolor::reset << '\n';
            cout << matches.size() << " possible match(es).\n"
                 << GREEN;

            // If more than 10 matches, only show first 10, else use total amount
            numMatches = matches.size() > 10 ? 10 : matches.size();

            // This prints out 10 found matches
            for (int i = 0; i < numMatches; i++)
            {
                // find the substring in the word
                loc = matches[i].find(word);
                // if its found
                if (loc != string::npos)
                {
                    // print one letter at a time turning on red or green
                    //  depending on if the matching subtring is being printed
                    for (int j = 0; j < matches[i].size(); j++)
                    {
                        // if we are printing the substring turn it red
                        if (j >= loc && j <= loc + word.size() - 1)
                        {
                            cout << MAGENTA;
                        }
                        else
                        {
                            cout << GREEN;
                        }
                        cout << matches[i][j];
                    }
                    cout << GREEN;
                }
                cout << " ";
            }
            cout << termcolor::reset << "\n\n";
        }
    }
    cout << GREEN << string(90, '#') << termcolor::reset << '\n'; // Footer just to show program ended
    return 0;
}

/**
 * load_trie
 * @brief Opens an input file and reads in the data to the Trie.
 *        Makes every string fully lower case while inserting to Trie.
 * 
 * @param tree Trie to store data in.
 * @param file_name input file name.
 */
void load_trie(Trie &tree, string file_name)
{
    ifstream fin; // file to get animal names
    string x;
    fin.open(file_name); // open file for reading

    while (fin >> x)
    {
        for (char &c : x)
        {
            c = tolower(c); // Change char to lowercase (if possible)
        }
        tree.insert(x); // Insert formatted string
    }
    fin.close();
}
