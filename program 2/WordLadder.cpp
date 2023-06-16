#include "WordLadder.h"
#include <fstream>
#include <iostream>
#include <queue>

WordLadder::WordLadder(const string &file)
{
    /* Passes in the name of a file that contains a dictionary of 5-letter words.
       Fills the list (dict) with the words within this file.
       If the file does not open for any reason or if any word within the file
       does not have exactly 5 characters, this function should output an
       error message and return.
    */
    ifstream inFS(file);
    if (!inFS.is_open())
    {
        cout << "Error opening " << file << endl;
        return;
    }

    string input;
    while (getline(inFS, input))
    {
        if (!input.empty())
        {
            if (input.size() != 5)
            {
                cout << "Word is not 5 letters long" << endl;
                return;
            }
            dict.push_back(input);
        }
    }
    inFS.close();
}

void WordLadder::outputLadder(const string &start, const string &end, const string &outputFile)
{
    /* Passes in two 5-letter words and the name of an output file.
       Outputs to this file a word ladder that starts from the first word passed in
       and ends with the second word passed in.
       If either word passed in does not exist in the dictionary (dict),
       this function should output an error message and return.
       Otherwise, this function outputs to the file the word ladder it finds or outputs
       to the file, the message, "No Word Ladder Found."
    */
    ofstream outFS(outputFile);
    if (!outFS.is_open())
    {
        cout << "Error opening " << outputFile << endl;
        return;
    }

    if (start == end)
    {
        stack<string> words;
        words.push(start);
        outFS << words.top() << endl;
        outFS.close();
        return;
    }

    bool validStart = false;
    bool validEnd = false;
    for (list<string>::iterator it = dict.begin(); it != dict.end(); ++it) // checks if 1st or 2nd word are in dict
    {
        if (*it == start)
        {
            validStart = true;
        }
        if (*it == end)
        {
            validEnd = true;
        }
    }

    if (validStart == false)
    {
        cout << "First input not found" << endl;
        exit(1);
    }
    if (validEnd == false)
    {
        cout << "Last input not found" << endl;
        exit(1);
    }

    stack<string> ladder;
    queue<stack<string>> line;
    ladder.push(start);
    line.push(ladder);

    string topWord;
    stack<string> frontStack;
    while (!line.empty())
    {
        frontStack = line.front();
        topWord = frontStack.top();

        list<string>::iterator it = dict.begin();
        while(it != dict.end())
        { // checks list for 1 off words
            string word = *it;
            int difference = 0;
            for (unsigned i = 0; i < word.size(); ++i)
            {
                if (word.at(i) != topWord.at(i))
                {
                    difference++;
                }
            }
            if (difference == 1)
            { // makes new stack with new found word on top
                stack<string> newStack = frontStack;
                newStack.push(word);
                if (word == end)
                {
                    // output stack if end found
                    stack<string> reversedStack;
                    while (!newStack.empty()) // reverses stack to correct output
                    {
                        reversedStack.push(newStack.top());
                        newStack.pop();
                    }
                    while (!reversedStack.empty())
                    {
                        outFS << reversedStack.top() << endl;
                        reversedStack.pop();
                    }
                    outFS.close();
                    return;
                }
                else
                {
                    line.push(newStack);
                    it = dict.erase(it); // iterates
                }
            }
            else // seperates iterator with if statement 
            {
                it++;
            }
        }
        line.pop(); // removes front stack that has 1 less word
    }
    outFS << "No Word Ladder Found." << endl;
    outFS.close();
}
// create a Stack containing just the first word in the ladder
// enqueue this Stack on to a Queue of Stacks
// while this Queue of Stacks is not empty
// get the word on top of the front Stack of this Queue
// for each word in the dictionary
// if the word is off by just one letter from the top word
// create a new Stack that is a copy of the front Stack and push on this off-by-one word found
// if this off-by-one word is the end word of the ladder, this new Stack contains the entire word ladder. You are done!
// otherwise, enqueue this new Stack and remove this word from the dictionary
// dequeue this front stack
// if the Queue is empty and you didn't find the word ladder, a word ladder does not exist for these 2 words