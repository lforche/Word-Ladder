#pragma once
// YOU MAY NOT #include ANYTHING OTHER THAN THRESE THREE STL CLASSES
#include <vector>
#include <list>
#include <string>
#include <set>

//
// WordLadder.h Defines an interface for games that construct word ladders.
// See https://en.wikipedia.org/wiki/Word_ladder for a definition and history.
// 
// Word ladders are constructed in the context of some predefined list of valid words. We will refer to
// this word list as the lexicon. An implementing class of this header must provide a way to explicitly
// set the lexicon. This will typically be done in the constructor.
// 
// For the purposes of this interface and all implementing classes, a string is a word if and only if it 
// appears in the current lexicon. In the documentation of each instance method, the use of 'string' means 
// that the referenced string does not have to be a word, while the use of 'word' implies that the
// referenced string must be a word.
// 
// Originally written as a Java project by Dean Hentrix (dh@auburn.edu)
// 
// Converted to a C++ project by Larry Thomas, University of Toledo (Larry.Thomas@UToledo.edu) 4/18/2020
// 

using namespace std;

/* This is the WordLadder.h file for Lab 4 where a word ladder is created by using a breadth-first search.
   Name: Lindsey Forche
   Class: EECS 2510-001 Spring 2020 (Non-linear Data Structures)
   Due Date: 4/27/2020 
   In this file, there is a variety of the public and private methods. The private methods are defined. 
   FindInVector finds the index of a string in a vector by iterating through the vector and comparing the 
   desired string with the string in each location of the vector. isWord makes sure that the string given
   by the user is a word in the lexicon by iterating through set<string> lexicon and checking each string 
   against the word I am checking. isWordLadder makes sure that each of the words in the ladder are 
   only 1 hamming distance apart by iterating through the ladder and checking the hamming distance of the
   current string and the next string. If it is not 1, then it is not a valid word ladder. getNeighbors
   iterates the lexicon and gets the hamming distance of the word that I want the neighbors of and the 
   words in the lexicon. If the hamming distance is 1, then that word is a neighbor of my current word.
   getHammingDistance checks that the two strings are the same length, then checks how many character 
   differences there are between the two strings. The number of character differences is the hamming distance
   between the two words. */

class WordLadder
{
public:

    //---------------------------------------------------------------------------------------------
    // Constructor to set up the game -- basically consists of just loading the lexicon (dictionary)
    // 
    // In order to help with efficiency, we keep only the words with the specified length
    // 
    // This is the constructor of the program
    // It opens the file in binary, uses >> to read in string words, then continues
    // until the end of the file, and it only keeps the words that are the length specified 
    // by the user. 
    // 
    // input parameters: lexiconFileName and desired length of words to be kept
    //
    WordLadder(string lexiconFileName, int len);

    //---------------------------------------------------------------------------------------------
    // Returns a minimum-length word ladder from start to end. If multiple minimum-length
    // word ladders exist, no guarantee is made regarding which one is returned. If no word
    // ladder exists, this method returns an empty list.
    //
    // Breadth-first search is used to implement this method.
    //
    // input parameter: the starting word and the ending word
    // returns  a minimum length word ladder from start to end
    //
    vector<string> getMinLadder(string start, string end);

    //---------------------------------------------------------------------------------------------
    // Used to display the result, whether empty, or a valid WordLadder
    // iterates through a vector to return the contents or returns no solution
    //
    // input parameter: vector<string> sequence
    //
    void displayResult(vector<string> sequence);

private:

    set<string> lexicon;    // The dictionary

    //---------------------------------------------------------------------------------------------
    // Returns the location within the vector of the given string; returns -1 if not found
    //
    // FindInVector finds the index of a string in a vector by iterating through the vector and comparing the 
    // desired string with the string in each location of the vector.
    int findInVector(vector<string> vec, string str)
    {
        for (int i = 0; i < vec.size(); i++) // iterate through the vector
        {
            if (vec[i] == str)
                return i; // return i if the string is in the vector
        }
        return -1; // return -1 if the string is not in the vector
    }

    //---------------------------------------------------------------------------------------------
    // Checks to see if the given string is a word.
    // 
    // str      the string to check
    // returns  true if str is a word, false otherwise
    // 
    // isWord makes sure that the string given by the user is a word in the lexicon by iterating through set<string> lexiconand checking each string
    // against the word I am checking.
    bool isWord(string str) //checks if word is in lexicon
    {
        set<string> :: iterator itr;
        for (itr = lexicon.begin(); itr != lexicon.end(); itr++) // iterate through the lexicon to check if the desired word is in the dictionary
        {
            if (*itr == str)
                return true; // return true if the word is in the lexicon
        }
        return false; // return false if the word was not found in the lexicon
    }

    //---------------------------------------------------------------------------------------------
    // Checks to see if the given sequence of strings is a valid word ladder.
    //
    // sequence   the given sequence of strings
    // returns    true if the given sequence is a valid word ladder, false otherwise
    //
    // isWordLadder makes sure that each of the words in the ladder are only 1 hamming distance apart by iterating through the ladder and checking the hamming distance of the
    // current string and the next string.If it is not 1, then it is not a valid word ladder.
    bool isWordLadder(vector<string> sequence)
    {
        for (int i = 0; i < sequence.size(); i++) // iterate through the entire vector
        {
            if (i < sequence.size() - 1) // check the contents before last word in the vector because each comparison checks the current word with the next word
            {
                if (getHammingDistance(sequence[i], sequence[i + 1]) != 1)
                    return false; // return false if the hamming distance is not 1
            }
        }
        return true; // return true if the hamming distance for everything is 1
    }

    //---------------------------------------------------------------------------------------------
    // Returns all the words that have a Hamming distance of one relative to the given word.
    //
    // word:     the given word
    // returns:  the neighbors of the given word
    //
    // getNeighbors iterates the lexicon and gets the hamming distance of the word that I want the neighbors ofand the
    // words in the lexicon.If the hamming distance is 1, then that word is a neighbor of my current word.
    set<string> getNeighbors(string word)
    {
        set<string> neighbors; // create a set that will hold the neighbors
        set<string> :: iterator itr;
        for (itr = lexicon.begin(); itr != lexicon.end(); itr++) // iterate through the set
        {
            if (getHammingDistance(word, *itr) == 1)
                neighbors.insert(*itr); // insert the current word in the lexicon that has a hamming distance of 1
        }
        return neighbors; // return the set of neighbors
    }

    //---------------------------------------------------------------------------------------------
    // Returns the Hamming distance between two strings, str1 and str2. The Hamming distance between two
    // strings of equal length is defined as the number of positions at which the corresponding symbols
    // are different. The Hamming distance is undefined if the strings have different lengths, and this
    // method must return -1 in that case. See https://en.wikipedia.org/wiki/Hamming_distance for more
    //
    // str1    the first string
    // str2    the second string
    // returns the Hamming distance between str1 and str2 if they are the same length, -1 otherwise
    //
    // getHammingDistance checks that the two strings are the same length, then checks how many character
    // differences there are between the two strings.The number of character differences is the hamming distance
    // between the two words.
    int getHammingDistance(string str1, string str2)
    {
        int hammingDistance = 0;
        if (str1.length() == str2.length()) // compare the lengths
        {
            for (int i = 0; i < str1.length(); i++)
            {
                if (str1[i] != str2[i]) // increment the hamming distance with every character difference
                    hammingDistance++;
            }  
            return hammingDistance; // return the hamming distance when all of the character differences are accounted for
        }
        else
            return -1; // return -1 if the length of the two words are different
    }

};