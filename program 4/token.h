#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <iostream>

using namespace std;

class Token
{
private:
    string word;
    int frequency;
    int code;

public:
    Token(const string &);
    Token(const string&, int);
    void addFrequency();
    const string &getWord();
    int getFrequency();
    void setFrequency(int);
    void setWord(const string&);
    void setCode(int);
    int getCode();

};
#endif
