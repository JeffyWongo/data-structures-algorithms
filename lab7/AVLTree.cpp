#include "AVLTree.h"

using namespace std;

int AVLTree::balanceFactor(Node *node)
{
    int left = -1;
    int right = -1;

    if (node->left)
    {
        left = node->left->height;
    }
    if (node->right)
    {
        right = node->right->height;
    }
    return left - right;
}

void AVLTree::printBalanceFactors()
{
    printBalanceFactors(root);
    cout << endl;
}

void AVLTree::printBalanceFactors(Node *node)
{
    if (node) // inorder traversal
    {
        printBalanceFactors(node->left); // left child
        cout << node->data << "(" << balanceFactor(node) << "), "; // print
        printBalanceFactors(node->right); // right child
    }
}

void AVLTree::visualizeTree(const string &outputFilename)
{
    ofstream outFS(outputFilename.c_str());
    if (!outFS.is_open())
    {
        cout << "Error" << endl;
        return;
    }
    outFS << "digraph G {" << endl;
    visualizeTree(outFS, root);
    outFS << "}";
    outFS.close();
    string jpgFilename = outputFilename.substr(0, outputFilename.size() - 4) + ".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}

void AVLTree::visualizeTree(ofstream &outFS, Node *n)
{
    if (n)
    {
        if (n->left)
        {
            visualizeTree(outFS, n->left);
            outFS << n->data << " -> " << n->left->data << ";" << endl;
        }

        if (n->right)
        {
            visualizeTree(outFS, n->right);
            outFS << n->data << " -> " << n->right->data << ";" << endl;
        }
    }
}

void AVLTree::insert(const string &value)
{
    Node *node = new Node(value);
    if (root == nullptr)
    {
        root = node;
        root->parent = nullptr;
        return;
    }

    Node *curr = root;
    while (curr)
    {
        if (node->data < curr->data) // if value is less than current
        {
            if (!curr->left) // leaf node
            {
                curr->left = node;
                node->parent = curr;
                curr = nullptr; // exit
            }
            else // left child is current, traverses through tree
            {
                curr = curr->left;
            }
        }
        else if (node->data > curr->data) // if value is greater than current
        {
            if (!curr->right) // leaf node
            {
                curr->right = node;
                node->parent = curr;
                curr = nullptr; // exit 
            }
            else // right child is current, traverses through tree
            {
                curr = curr->right;
            }
        }
        else // if node = current, removes duplicate inputs
        {
            return;
        }
    }
    node = node->parent;
    while (node) // traverses up until root to check balance factors
    {
        rotate(node);
        node = node->parent;
    }
}

// Node *AVLTree::findUnbalancedNode(Node *node)
// {
//     if (node)
//     {
//         if (balanceFactor(node) == 2 || balanceFactor(node) == -2)
//         {
//             Node* unbalancedNode = node;
//         }
//         return findUnbalancedNode(node->parent);
//         }
//     }
//     return 0;
// }

void AVLTree::rotate(Node *node)// checks all 4 cases
{
    updateHeight(node); // because node just got added
    if (balanceFactor(node) == -2) // if right skewed
    {
        if (balanceFactor(node->right) == 1) // right left
        {
            rotateRight(node->right);
        }
        rotateLeft(node); // left
    }
    else if (balanceFactor(node) == 2) // if left skewed
    {
        if (balanceFactor(node->left) == -1) // left right
        {
            rotateLeft(node->left);
        }
        rotateRight(node); // right
    }
}

void AVLTree::rotateRight(Node *node)
{
    Node *leftRightChild = node->left->right;
    if (node->parent)
    {
        replaceChild(node->parent, node, node->left); // parent, currentchild, newchild (makes node's child the child of node's parent)
    }
    else // node is root
    {
        root = node->left;
        root->parent = nullptr;
    }
    setChild(node->left, "right", node); // (set node->left's right child to node)
    setChild(node, "left", leftRightChild); // set node's left child to leftrightchild
}

void AVLTree::rotateLeft(Node *node)
{
    Node *rightLeftChild = node->right->left;
    if (node->parent)
    {
        replaceChild(node->parent, node, node->right); // parent, currentchild, newchild (makes node's child the child of node's parent)
    }
    else
    {
        root = node->right;
        root->parent = nullptr;
    }
    setChild(node->right, "left", node); // (set node->right's left child to node)
    setChild(node, "right", rightLeftChild); // (set node's right child to rightleftchild)
}

void AVLTree::setChild(Node *parent, string whichChild, Node *child)
{
    if (whichChild == "left")
    {
        parent->left = child;
    }
    else
    {
        parent->right = child;
    }
    if (child)
    {
        child->parent = parent;
    }
    updateHeight(parent); // since height is decreasing
}

void AVLTree::replaceChild(Node *parent, Node *currentChild, Node *newChild)
{
    if (parent->left == currentChild) // if left child
    {
        setChild(parent, "left", newChild);
    }
    else if (parent->right == currentChild) // if right child
    {
        setChild(parent, "right", newChild);
    }
}

void AVLTree::updateHeight(Node *node)
{
    int leftHeight = -1;
    int rightHeight = -1;
    if (node->left)
    {
        leftHeight = node->left->height;
    }
    if (node->right)
    {
        rightHeight = node->right->height;
    }
    node->height = max(leftHeight, rightHeight) + 1;
}