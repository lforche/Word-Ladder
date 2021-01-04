#include <iostream>
#include <string>
#include <fstream> 
#include <vector>
#include <string>
#include <set>
#include <list>
#include <time.h>
#include <locale>
#include "WordLadder.h"
using namespace std;

/* This is the Main.cpp file for Lab 4 where a word ladder is created by using a breadth-first search.
   Name: Lindsey Forche
   Class: EECS 2510-001 Spring 2020 (Non-linear Data Structures)
   Due Date: 4/27/2020 
   It uses the command line to get the file name, first word, and last word to create a word ladder from.
   It makes sure the first and last word are the same size, puts the words to uppercase, calls the constructor and
   getMinLadder and display methods to create and display the word ladder.*/

int main(int argc, char* argv[])
{
    // This is the main class for the program
    // It uses the command line to get its information, says error statements if there is something missing or too much of something,
    // calls the constructor to open a file and create a dictionary of words of the desired length, then uses BFS to get the min ladder and display it in a good way
    if (argc == 4) // first check for four commands from the command line
    {
        string program = argv[0];
        string fileName = argv[1];
        string firstWord = argv[2];
        string lastWord = argv[3];

        if (firstWord.length() != lastWord.length()) // if the length of the first and last word are not the same, then an error statement is made then exit
        {
            cout << "Error: The first and last word are not the same length." << endl;
            return 0;
        }
        // since the length of the first word is the same as the last word if the program didn't exit, 
        // then use the length of the first word as the desired length of words in the dictionary
        int length = firstWord.length(); 
        // call the constructor with the file name provided by the user and the length of the first word given
        // The constructor will read in the file and create a dictionary of the words with the desired length
        WordLadder wl(fileName, length);
        // Make the first word all uppercase
        for (int i = 0; i < firstWord.length(); i++)
        {
            if (firstWord[i] >= 'a' && firstWord[i] <= 'z')
                firstWord[i] = firstWord[i] - 32;
        }
        // Make the last word all uppercase
        for (int i = 0; i < lastWord.length(); i++)
        {
            if (lastWord[i] >= 'a' && lastWord[i] <= 'z')
                lastWord[i] = lastWord[i] - 32;
        }
        // Get the min ladder
        vector<string> wordLadder = wl.getMinLadder(firstWord, lastWord);
        // Display the min ladder
        wl.displayResult(wordLadder);
        return 0; // exit
    }
    else 
    {
        if (argc < 4) // if there are less than 4 commands, then there are too few of commands
            cout << "Error: There are too few of commands." << endl;
        else // otherwise there are too many commands
            cout << "Error: There are too many commands." << endl;
        return 0; // exit
    }
}



