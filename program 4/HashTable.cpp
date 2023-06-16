#include "HashTable.h"
#include "token.h"
#include <iostream>

using namespace std;

HashTable::HashTable(int s)
{
    size = s;
    hashTable = new list<Token>[size];
}

int HashTable::decodeHash(int value)
{
    return value % size;
}

int HashTable::encodeHash(const string &s)
{
    int value = 0;
    for (unsigned i = 0; i < s.size(); i++)
    {
        value += s[i];
    }
    return value % size;
}

void HashTable::insertEncoder(const string &s, int code)
{
    int value = encodeHash(s);   // get hash value
    Token word = Token(s, code); // input word in new location
    hashTable[value].push_back(word);
}

void HashTable::insertDecoder(const string &s, int code)
{
    int value = decodeHash(code);
    Token word = Token(s, code);
    hashTable[value].push_back(word);
}

bool HashTable::search(const string &s)
{
    int value = encodeHash(s);
    list<Token>::iterator it;
    for (it = hashTable[value].begin(); it != hashTable[value].end(); ++it)
    {
        if (it->getWord() == s)
        {
            return true;
        }
    }
    return false;
}

int HashTable::searchCode(const string &s)
{
    int value = encodeHash(s);
    list<Token>::iterator it;
    for (it = hashTable[value].begin(); it != hashTable[value].end(); ++it)
    {
        if (it->getWord() == s)
        {
            return it->getCode();
        }
    }
    return -1;
}
