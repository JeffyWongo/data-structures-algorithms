#ifndef _NODE_H_
#define _NODE_H_
using namespace std;
#include <string>

class Node
{
    public:
        Node(string);
        string getString() const;
        void setString(string&);
        Node* getRight() const;
        Node* getLeft() const;
        void setLeft(Node*);
        void setRight(Node*);
        int getCount() const;
        void setCount(int);
        void add();
        void sub();

    private:
        Node* right;
        Node* left;
        string data;
        int count;
};

#endif