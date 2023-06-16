#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "token.h"
#include "HashTable.h"

using namespace std;

vector<Token> inputData(vector<Token> tokens, string &input)
{
    for (unsigned i = 0; i < tokens.size(); i++)
    {
        if (tokens.at(i).getWord() == input)
        {
            tokens.at(i).addFrequency();
            return tokens;
        }
    }
    Token word = Token(input);
    tokens.push_back(word);
    return tokens;
}

void SelectionSort(vector<Token> &num)
{
    int i, j, first, temp;
    string tempstring;
    int numLength = num.size();
    for (i = numLength - 1; i > 0; i--)
    {
        first = 0;               // initialize to subscript of first element
        for (j = 1; j <= i; j++) // locate smallest between positions 1 and i.
        {
            if (num.at(j).getFrequency() < num.at(first).getFrequency())
                first = j;
        }
        temp = num.at(first).getFrequency(); // Swap smallest found with element in position i.
        num.at(first).setFrequency(num.at(i).getFrequency());
        num.at(i).setFrequency(temp);
        tempstring = num.at(first).getWord(); // Swap smallest found with element in position i.
        num.at(first).setWord(num.at(i).getWord());
        num.at(i).setWord(tempstring);
    }
    return;
}

int main()
{
    string file = "TESTING_mobydick.txt";
    ifstream inFS(file);
    if (!inFS.is_open())
    {
        cout << "Error opening " << file << endl;
        exit(1);
    }

    vector<Token> tokens;
    string input;
    while (inFS >> input)
    {
        tokens = inputData(tokens, input);
    }

    // cout << "Elements before sorting: " << endl;

    // cout << endl << endl;

    // cout << "Elements after sorting" << endl;
    SelectionSort(tokens);

    // for (unsigned i = 0; i < tokens.size(); i++)
    // {
    //     cout << tokens.at(i).getFrequency() << " " << tokens.at(i).getWord() << endl;
    // }

    inFS.close();

    HashTable encoder(tokens.size());

    for (unsigned i = 0; i < tokens.size(); i++)
    {
        encoder.insertEncoder(tokens.at(i).getWord(), i + 1);
    }

    // HashTable decoder(100);

    // for(unsigned i = 0; i < tokens.size(); i++)
    // {
    //     decoder.insertDecoder(tokens.at(i).getWord(), i+1);
    // }

    // string word;
    // cout << "Enter a word: " << endl;
    // cin >> word;

    // if (encoder.search(word))
    // {
    //     cout << "Code: " << encoder.searchCode(word) << endl;
    // }
    // else
    // {
    //     cout << "Word not found" << endl;
    // }

    // int code;
    // cout << "Enter a code: " << endl;
    // cin >> code;

    // cout << "Word: " << tokens.at(code - 1).getWord() << endl;

    inFS.open(file);
    string outputfile = "encoder.txt";
    ofstream outFS(outputfile);
    if (!inFS.is_open())
    {
        cout << "Error opening " << file << endl;
        exit(1);
    }

    if (!outFS.is_open())
    {
        cout << "Error opening " << outputfile << endl;
        exit(1);
    }

    string line;
    while (!inFS.eof())
    {
        getline(inFS, line);
        if(line == "")
        {
            outFS << endl;
            continue;
        }
        int len = line.size();
        while (len > 0)
        { // identify all individual strings
            string sub;
            len = line.find(" ");
            if (len > 0)
            {
                sub = line.substr(0, len);
                line = line.substr(len + 1, line.size());
            }
            else
            {
                sub = line.substr(0, line.size() - 1);
            }
            if(sub == "")
            {
                continue;
            }
            outFS << encoder.searchCode(sub) << " ";
        }
        outFS << endl;
    }

    inFS.close();
    outFS.close();

    inFS.open("encoder.txt");
    outFS.open("decoder.txt");
    int code;

    while (inFS >> code)
    {
        outFS << tokens.at(code - 1).getWord() << endl; // decoder
    }

    inFS.close();
    outFS.close();

    return 0;
}