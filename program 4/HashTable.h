#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <list>
#include <iostream>
#include "token.h"

using namespace std;

class HashTable {

 private:
 	int size;
	list<Token> *hashTable;
	

 public:
	HashTable(int);
	bool isEmpty() const;
	bool search(const string &);
	void insertEncoder(const string &, int);
	void insertDecoder(const string &, int);
	int searchCode(const string &);
	string searchString(int);
 
 private:
	int decodeHash(int);
	int encodeHash(const string &);
};

#endif