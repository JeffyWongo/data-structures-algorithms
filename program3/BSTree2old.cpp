#include "BSTree.h"
#include "Node.h"
#include <iostream>
using namespace std;

BSTree::BSTree()
{
    root = nullptr;
}

BSTree::~BSTree()
{
    if (root)
    {
        delete root;
    }
}

void BSTree::preOrder() const
{
    preOrder(root);
    cout << endl;
}

void BSTree::preOrder(Node *node) const
{
    if (node)
    {
        cout << node->getString() << "(" << node->getCount() << "), ";
        preOrder(node->getLeft());
        preOrder(node->getRight());
    }
}

void BSTree::inOrder() const
{
    inOrder(root);
    cout << endl;
}

void BSTree::inOrder(Node *node) const
{
    if (node)
    {
        inOrder(node->getLeft());
        cout << node->getString() << "(" << node->getCount() << "), ";
        inOrder(node->getRight());
    }
}

void BSTree::postOrder() const
{
    postOrder(root);
    cout << endl;
}

void BSTree::postOrder(Node *node) const
{
    if (node)
    {
        postOrder(node->getLeft());
        postOrder(node->getRight());
        cout << node->getString() << "(" << node->getCount() << "), ";
    }
}

void BSTree::insert(const string &newString)
{
    Node *foundNode = nodeSearch(root, newString);
    if (!foundNode)
    {
        if (!root)
        {
            root = new Node(newString);
            root->add();
            return;
        }
        else
        {
            Node *newNode = new Node(newString);
            Node *node = root;
            while (node)
            {
                if (newNode->getString() < node->getString())
                {
                    if (!node->getLeft())
                    {
                        node->setLeft(newNode);
                        newNode->add();
                        node = nullptr;
                    }
                    else
                    {
                        node = node->getLeft();
                    }
                }
                else
                {
                    if (!node->getRight())
                    {
                        node->setRight(newNode);
                        newNode->add();
                        node = nullptr;
                    }
                    else
                    {
                        node = node->getRight();
                    }
                }
            }
        }
    }
    else
    {
        foundNode->add();
    }
}

bool BSTree::search(const string &key) const
{
    return nodeSearch(root, key) != nullptr;
}

Node *BSTree::nodeSearch(Node *node, const string &key) const
{
    if (node)
    {
        if (node->getString() == key)
        {
            return node;
        }
        else if (node->getString() < key)
        {
            return nodeSearch(node->getRight(), key);
        }
        else if (node->getString() > key)
        {
            return nodeSearch(node->getLeft(), key);
        }
        else
        {
            return nullptr;
        }
    }
    else
    {
        return nullptr;
    }
}

string BSTree::largest() const
{
    Node *node = root;
    while (node)
    {
        if (!node->getRight())
        {
            return node->getString();
        }
        else
        {
            node = node->getRight();
        }
    }
    return "";
}

Node *BSTree::largestNode(Node *subtree) const
{
    Node *node = subtree;
    while (node)
    {
        if (!node->getRight())
        {
            return node;
        }
        else
        {
            node = node->getRight();
        }
    }
    return nullptr;
}

string BSTree::smallest() const
{
    Node *node = root;
    while (node)
    {
        if (!node->getLeft())
        {
            return node->getString();
        }
        else
        {
            node = node->getLeft();
        }
    }
    return "";
}

Node *BSTree::smallestNode(Node *subtree) const
{
    Node *node = subtree;
    while (node)
    {
        if (!node->getLeft())
        {
            return node;
        }
        else
        {
            node = node->getLeft();
        }
    }
    return nullptr;
}

int BSTree::height(const string &key) const
{
    Node *node = nodeSearch(root, key);
    if (node)
    {
        return max(findHeight(node->getLeft()), findHeight(node->getRight()));
    }
    else
    {
        return -1;
    }
}

int BSTree::findHeight(Node *node) const
{
    if (node)
    {
        return max(findHeight(node->getLeft()), findHeight(node->getRight())) + 1;
    }
    else
    {
        return 0;
    }
}

// void BSTree::remove(const string &key)
// {
//     Node *node = nodeSearch(root, key);
//     if (node)
//     {
//         if (node->getCount() > 1)
//         {
//             node->sub();
//             return;
//         }
//         else
//         {
//             Node *parent = getParent(key);
//             if (!node->getLeft() && !node->getRight()) // if leaf
//             {
//                 if (!parent) // if root
//                 {
//                     root = nullptr;
//                 }
//                 else if(key < parent->getString())
//                 {
//                     parent->setLeft(nullptr);
//                 }
//                 else
//                 {
//                     parent->setRight(nullptr);
//                 }
//             }
//             else
//             {
//                 Node *temp;
//                 if (node->getLeft())
//                 {
//                     temp = largestNode(node->getLeft());
//                 }
//                 else
//                 {
//                     temp = smallestNode(node->getRight());
//                 }
//                 Node* copy = temp;
//                 remove(temp->getString());
//                 node = copy;
//             }
//         }
//     }
//     return;
// }

void BSTree::remove(const string &key)
{
    bool found = search(key);
    if (found)
    {
        Node *found = nodeSearch(root, key);
        if (found->getCount() > 1)
        {
            found->sub();
            return;
        }
        else
        {
            removeNode(found);
        }
    }
}

void BSTree::removeNode(Node *node)
{
    Node *parent = getParent(node->getString());

    if (node->getLeft() == nullptr && node->getRight() == nullptr) // if leaf
    {
        if (node->getString() < parent->getString())
        {
            parent->setLeft(nullptr);
        }
        else
        {
            parent->setRight(nullptr);
        }
    }
    else
    {
        Node *temp = nullptr;
        if(node->getLeft())
        {
            temp = node->getLeft();
            while (temp->getRight())
            {
                temp = temp->getRight();
            }
        }
        else
        {
            temp = node->getRight();
            while (temp->getLeft())
            {
                temp = temp->getLeft();
            }
        }
        string tempData = temp->getString();
        int tempCount = temp->getCount();
        removeNode(temp);
        node->setString(tempData);
        node->setCount(tempCount);
    }
}

Node *BSTree::getParent(const string &key) const
{
    Node *parent = nullptr;
    Node *currNode = root;
    while (currNode)
    {
        if (currNode->getString() == key)
        {
            return parent;
        }
        else if (currNode->getString() < key)
        {
            parent = currNode;
            currNode = currNode->getRight();
        }
        else
        {
            parent = currNode;
            currNode = currNode->getLeft();
        }
    }
    return parent;
}