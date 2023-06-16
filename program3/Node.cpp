#include "Node.h"
Node::Node(string key)
{
    right = nullptr;
    left = nullptr;
    data = key;
    count = 0;
}

string Node::getString() const
{
    return data;
}

void Node::setString(string& key)
{
    data = key;
}

Node* Node::getRight() const
{
    return right;
}

Node* Node::getLeft() const
{
    return left;
}

void Node::setLeft(Node* node)
{
    left = node;
}

void Node::setRight(Node* node)
{
    right = node;
}

int Node::getCount() const
{
    return count;
}

void Node::setCount(int num)
{
    count = num;
}

void Node::add()
{
    count++;
}

void Node::sub()
{
    count--;
}
