#include "IntList.h"

IntList::IntList()
{
    dummyHead = new IntNode(0);
    dummyTail = new IntNode(0);
    dummyHead->prev = nullptr;
    dummyHead->next = dummyTail;
    dummyTail->prev = dummyHead;
    dummyTail->next = nullptr;
}

IntList::~IntList()
{
    IntNode* currNode = dummyHead;
    while (currNode != nullptr)
    {
        IntNode* tempNode = currNode;
        currNode = currNode->next;
        delete tempNode;
    }
}

void IntList::push_front(int value)
{
    IntNode* node = new IntNode(value);
    node->next = dummyHead->next;
    node->prev = dummyHead;
    dummyHead->next->prev = node;
    dummyHead->next = node;
}

void IntList::pop_front()
{
    if (!empty()) {
        IntNode* tempNode = dummyHead->next;
        dummyHead->next = tempNode->next;
        tempNode->next->prev = dummyHead;
        delete tempNode; 
    }
}

void IntList::push_back(int value)
{
    IntNode* node = new IntNode(value);
    node->next = dummyTail;
    node->prev = dummyTail->prev;
    dummyTail->prev->next = node;
    dummyTail->prev = node;
}

void IntList::pop_back()
{
    if (!empty()) {
        IntNode* tempNode = dummyTail->prev;
        dummyTail->prev = tempNode->prev;
        tempNode->prev->next = dummyTail;
        delete tempNode; 
    }
}

bool IntList::empty() const
{
    if(dummyHead->next == dummyTail)
    {
        return true;
    }
    else
    {
        return false;
    }
}

ostream & operator<<(ostream &out, const IntList &rhs)
{
    IntNode* currNode = rhs.dummyHead->next;
    if(!rhs.empty())
    {
        while(currNode->next != rhs.dummyTail)
        {
            out << currNode->data << " ";
            currNode = currNode->next;
        }
        out << currNode->data;
    }
    return out;
}

void IntList::printReverse() const
{
    IntNode* currNode = dummyTail->prev;
    if(!empty())
    {
        while(currNode->prev != dummyHead)
        {
            cout << currNode->data << " ";
            currNode = currNode->prev;
        }
        cout << currNode->data;
    }
}