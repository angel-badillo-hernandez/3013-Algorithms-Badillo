#include "mygetch.hpp"
//#include "termcolor.hpp"
#include "timer.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include "List.hpp"

using namespace std;

// #define RED termcolor::red
// #define BLUE termcolor::blue
// #define YELLOW termcolor::yellow
// #define GREEN termcolor::green
// #define MAGENTA termcolor::magenta
// #define GREY termcolor::grey

/**
 * public: load_list
 * @brief Takes a List by reference, and populates it with data from an input
 *        file.
 * 
 * @param L An empty list to populate with values.
 * @param file_name The name of the file to be used.
 * @return void
 */
void load_list(List &L, string file_name);

/**
 * public: get_matches
 * @brief Clears a List and populates it with values from another List, but 
 *        only values that partially/wholey match (prefix matches) the specified substring.
 *        Ignores empty strings.
 * 
 * @param L A List filled with string values.
 * @param matches An List to populate with matches from List L.
 * @param substring A substring to be used for finding matches.
 * @return void
 */
void get_matches(const List &L, List &matches, string substring);

int main()
{
    char k;           // holder for character being typed
    string word = ""; // var to concatenate letters to
    List animals;     // array of animal names
    List matches;     // any matches found in vector of animals
    int loc;          // location of substring to change its color
    int numMatches;   // loop control variable for printing matches
    
    Timer T;   // create a timer
    T.Start(); // start it

    load_list(animals, "animal_names.txt");

    T.End(); // end the current timer

    // print out how long it took to load the animals file
    cout << T.Seconds() << " seconds to read in data from dictionary.txt\n";
    cout << T.MilliSeconds() << " milliseconds to read in data from dictionary.txt\n";

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
        get_matches(animals, matches, word);
        
        T.End(); // End timer for finding matches

        if ((int)k != 32)
        { // if k is not a space print it

            cout << T.Seconds() << " seconds to get matches.\n";
            cout << T.MilliSeconds() << " milliseconds to get matches\n";
            cout << "Key pressed: " << k << " = " << (int)k << '\n';
            cout << "Current Substring: " << word << '\n';
            cout << matches.size() << " possible match(es).\n";

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
                        }
                        else
                        {
                        }
                        cout << matches[i][j];
                    }
                }
                cout << " ";
            }
            cout << "\n\n";
        }
    }
    return 0;
}

/**
 * public: load_list
 * @brief Takes a List by reference, and populates it with data from an input
 *        file.
 * 
 * @param L An empty list to populate with values.
 * @param file_name The name of the file to be used.
 * @return void
 */
void load_list(List &L, string file_name)
{
    ifstream fin; // file to get animal names
    string x;
    fin.open(file_name); // open file for reading

    while (fin >> x)
    {
        for (auto &c : x)
        {
            c = tolower(c);
        }
        L.push_back(x);
    }
    fin.close();
}

/**
 * public: get_matches
 * @brief Clears a List and populates it with values from another List, but 
 *        only values that partially/wholey match (prefix matches) the specified substring.
 *        Ignores empty strings.
 * 
 * @param L A List filled with string values.
 * @param matches An List to populate with matches from List L.
 * @param substring A substring to be used for finding matches.
 * @return void
 */
void get_matches(const List &L, List &matches, string substring)
{
    size_t found; // size_t is an integer position of
                  // found item. -1 if its not found.

    matches.clear(); // It is quicker to directly clear and repopulate this list

    if (substring == "") // If empty string, don't bother searching
    {
        return;
    }
    for (int i = 0; i < L.size(); i++) // loop through List
    {
        found = L[i].find(substring); // check for substr match
        if (found == 0)               // if found = 0
        {
            matches.push_back(L[i]); // add to matches
        }
    }
}