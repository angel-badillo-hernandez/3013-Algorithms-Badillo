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

void LoadAnimals(List &L, string file_name)
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

List FindAnimals(List L, string substring)
{
    List matches;
    size_t found; // size_t is an integer position of
                  // found item. -1 if its not found.

    if (substring == "")
    {
        return matches;
    }
    for (int i = 0; i < L.size(); i++)
    {                                 // loop through array
        found = L[i].find(substring); // check for substr match
        if (found != string::npos && found == 0)
        {                            // if found >= 0 (its found then)
            matches.push_back(L[i]); // add to matches
        }
    }
    return matches;
}

int main()
{
    char k;           // holder for character being typed
    string word = ""; // var to concatenate letters to
    List animals;     // array of animal names
    List matches;     // any matches found in vector of animals
    int loc;          // location of substring to change its color
    int numMatches;

    ofstream fout("temp.txt");

    Timer T;   // create a timer
    T.Start(); // start it

    LoadAnimals(animals, "animal_names.txt");

    T.End(); // end the current timer

    // print out how long it took to load the animals file
    cout << T.Seconds() << " seconds to read in and print json" << endl;
    cout << T.MilliSeconds() << " milli to read in and print json" << endl;

    cout << "Type keys and watch what happens. Type capital Z to quit." << endl;

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

        T.Start();
        // Find any animals in the array that partially match
        // our substr word
        matches = FindAnimals(animals, word);
        T.End();

        if ((int)k != 32)
        { // if k is not a space print it

            cout << T.Seconds() << " seconds to get matches." << endl;
            cout << "Keypressed: " << k << " = " << (int)k << endl;
            cout << "Current Substr: " << word << endl;
            cout << matches.size() << " possible match(es).\n";
            cout << "Animals Found: ";

            if (matches.size() > 10)
            numMatches = 10;
            else
            numMatches = matches.size();

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
            cout << endl
                 << endl;
        }
    }
    return 0;
}