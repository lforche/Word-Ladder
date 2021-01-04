#include <iostream>
#include <string>
#include <fstream> 
#include <vector>
#include <string>
#include <set>
#include <list>
#include "WordLadder.h"
using namespace std;

/* This is the WordLadder.cpp file for Lab 4 where a word ladder is created by using a breadth-first search.
   Name: Lindsey Forche
   Class: EECS 2510-001 Spring 2020 (Non-linear Data Structures)
   Due Date: 4/27/2020 
   In this file there are a few methods. There is the constructor, which reads in a file and adds words of a specific 
   length to the lexicon. There is a getMidLadder method, which uses breadth-first search and finds the shortest word ladder
   for the given start and end word and specific file. There is a display ladder method, which iterates through the ladder
   and displays it to the user.*/

WordLadder::WordLadder(string lexiconFileName, int len)
{
    // This is the constructor of the program
    // It opens the file in binary, uses >> to read in string words, then continues
    // until the end of the file, and it only keeps the words that are the length specified 
    // by the user. 
    // 
    // input parameters: lexiconFileName and desired length of words to be kept
    //
    ifstream inFile;
    string word;

    inFile.open(lexiconFileName, ios::binary); // Open file using binary to not lose any information
    
    if (!inFile.is_open())
    {
        cout << "Error: Unable to open file" << endl;
        exit(0);
    }

    inFile >> word; // Priming read
    // Until the end of file bit is hit, the words that are the right size
    // in the file should be read and inserted into the lexicon
    while (!inFile.eof())
    {
        if (word.length() == len)
            lexicon.insert(word);
        inFile >> word; // Set up for next iteration
    }
    inFile.close(); // Close the file
}
vector<string> WordLadder::getMinLadder(string start, string end)
{
    // Returns a minimum-length word ladder from start to end. If multiple minimum-length
    // word ladders exist, no guarantee is made regarding which one is returned. If no word
    // ladder exists, this method returns an empty list.
    //
    // Breadth-first search is used to implement this method.
    //
    // input parameter: the starting word and the ending word
    // returns  a minimum length word ladder from start to end
    //
    vector<string> ladder;
    vector<string> wordSeen;
    vector<string> predecessors;
    list<string> queue;
    // check if the start and end word are words in the dictionary
    // if they are not, then return an empty ladder
    if (isWord(start) == false)
        return ladder;
    if (isWord(end) == false)
        return ladder;
    // Start by adding the start word to the queue, which is a list, and the words seen,
    // which is a vector, and then add "" (empty string) to predecessors, which is a vector as well
    queue.push_back(start);
    wordSeen.push_back(start);
    predecessors.push_back("");
    // Until the queue is empty, keep searching for the path to the desired end word
    while (queue.size() != NULL)
    {
        // First check what the value of the front of the queue is then remove the front value
        // Then get the neighbors of this value by calling the get neighbors method
        // Finally, for every neighbor, check whether we have seen it or not, and either add 
        // it to the queue and words seen and its predecessor to the predecessor vector if we have 
        // not seen the neighbor value or if it is the desired end word and we haven't seen it,
        // then work backwords from this neighbor back to its predecessor all the way to the 
        // start word and add those values to the ladder as you go
        string qFront = queue.front();
        queue.pop_front();
        set<string> neighbors = getNeighbors(qFront);
        set<string> :: iterator itr; // Iterator to be able to go through the set of neighbors strings
        // Used the iterator to start at the beginning of the neighbors set and iterate to the end
        for (itr = neighbors.begin(); itr != neighbors.end(); itr++)
        {
            // If the value was not found in the words seen vector, then one needs to check whether
            // it is the last word or whether it just needs to be added to the queue and continued through
            // the set of neighbors
            if (findInVector(wordSeen, *itr) == -1) 
            {
                // If this neighbor is the desired end word, then this word needs to be added to the words seen vector
                // and the ladder. Then the qfront value needs to be added to the predecessors vector
                if (*itr == end)
                {
                    wordSeen.push_back(*itr); 
                    predecessors.push_back(qFront);
                    ladder.push_back(*itr);
                    // Until the start word is found at the back of the ladder, keep adding the predecessor 
                    // of each word (start with the desired end word, add the predecessor, then its predecessor, and so on)
                    while (ladder.back() != start)
                    {
                        // find location of the last word in the ladder in the words seen vector
                        int nextPredecssorLocation = findInVector(wordSeen, ladder.back());
                        for (int i = 0; i < predecessors.size(); i++)
                        {
                            // if the location in the predecessor vector is the same as the location of the last word
                            // in the ladder in the words seen vector
                            if (i == nextPredecssorLocation) 
                                ladder.push_back(predecessors[i]); // add predecessor of the word at the back of the ladder
                        }
                    }
                    return ladder; // return the ladder 
                }
                // If the neighbor is not the desired end word, then just add this neighbor to the queue
                // and add qfront and the neighbor to the words seen
                // Then find the location of qfront in the words seen vector to then use this index value to 
                // find its predecessor in the predecessor vector
                // Add the predecessor of qfront and qfront to the predecessor vector
                else
                { 
                    queue.push_back(*itr);
                    wordSeen.push_back(qFront);
                    wordSeen.push_back(*itr);
                    // find location of qfront in the words seen vector
                    int qFrontLocation = findInVector(wordSeen, qFront);
                    for (int i = 0; i < predecessors.size(); i++)
                    {
                        // if the location in the predecessor vector is the same as the location of qfront
                        // in the words seen vector
                        if (i == qFrontLocation)
                            predecessors.push_back(predecessors[i]); // add predecessor of the qfront
                    }
                    predecessors.push_back(qFront); // add qfront
                }
            }
        }
    }
    return ladder; // return an empty ladder
}

void WordLadder::displayResult(vector<string> sequence)
{
    // Used to display the result, whether empty, or a valid WordLadder
    // iterates through a vector to return the contents or returns no solution
    //
    // input parameter: vector<string> sequence
    //
    // Check if word ladder is valid
    // If it is not a valid ladder, then exit
    if (isWordLadder(sequence) == false)
        return;
    // First check the size of the wordladder
    // so you can use this value to get the total number of steps done (which is one less than the size of the wordladder)
    // also use the size of the wordladder to list the contents of the ladder since the contents were added in reverse order initially
    int wordLadderSize = sequence.size();
    int numberOfSteps = wordLadderSize - 1;
    // if the word ladder is not empty, then list the contents of the ladder in reverse order
    if (wordLadderSize > 1)
    {
        cout << "A Shortest Word Ladder (" << numberOfSteps << " steps) is: ";
        for (int i = 0; i < wordLadderSize; i++)
        {
            cout << sequence.back() << " "; // return the value at the back of the ladder
            sequence.pop_back(); // then remove it
        }
        cout << endl;
        return; // exit
    }
    // if the word ladder is empty, then say that and exit
    else
    {
        cout << "Word Ladder is empty - No Solution" << endl;
        return; // exit
    }
}
