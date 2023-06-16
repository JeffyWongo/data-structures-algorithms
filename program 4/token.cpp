#include "token.h"
#include <iostream>

using namespace std;


Token::Token(const string &s) {
	word = s;
    frequency = 1;
}

Token::Token(const string &s, int value)
{
    word = s;
    code = value;
}


void Token::addFrequency()
{
    frequency++;
}

const string& Token::getWord()
{
    return word;
}

int Token::getFrequency()
{
    return frequency;
}

void Token::setFrequency(int value)
{
    frequency = value;
}

void Token::setWord(const string& value)
{
    word = value;
}

void Token::setCode(int value)
{
    code = value;
}

int Token::getCode()
{
    return code;
}