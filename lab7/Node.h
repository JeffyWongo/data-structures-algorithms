#ifndef _NODE_H_
#define _NODE_H_
#include <string>

using namespace std;

class Node
{
    public:
        Node(string);
        int height;
        string data;
        Node* left;
        Node* right;
        Node* parent;
};

#endif