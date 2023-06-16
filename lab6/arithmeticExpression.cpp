#include "arithmeticExpression.h"
#include <stack>
#include <fstream>
#include <sstream>

int arithmeticExpression::priority(char op){
    int priority = 0;
    if(op == '('){
        priority =  3;
    }
    else if(op == '*' || op == '/'){
        priority = 2;
    }
    else if(op == '+' || op == '-'){
        priority = 1;
    }
    return priority;
}

string arithmeticExpression::infix_to_postfix(){
    stack<char> s;
    ostringstream oss;
    char c;
    for(unsigned i = 0; i< infixExpression.size();++i){
        c = infixExpression.at(i);
        if(c == ' '){
            continue;
        }
        if(c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')'){ //c is an operator
            if( c == '('){
                s.push(c);
            }
            else if(c == ')'){
                while(s.top() != '('){
                    oss << s.top();
                    s.pop();
                }
                s.pop();
            }
            else{
                while(!s.empty() && priority(c) <= priority(s.top())){
                    if(s.top() == '('){
                        break;
                    }
                    oss << s.top();
                    s.pop();
                }
                s.push(c);
            }
        }
        else{ //c is an operand
            oss << c;
        }
    }
    while(!s.empty()){
        oss << s.top();
        s.pop();
    }
    return oss.str();
}

// void arithmeticExpression::visualizeTree(const string &outputFilename){
//     ofstream outFS(outputFilename.c_str());
//     if(!outFS.is_open()){
//         cout<<"Error opening "<< outputFilename<<endl;
//         return;
//     }
//     outFS<<"digraph G {"<<endl;
//     visualizeTree(outFS,root);
//     outFS<<"}";
//     outFS.close();
//     string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
//     string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
//     system(command.c_str());
// }

arithmeticExpression::arithmeticExpression(const string &expression)
{
    infixExpression = expression;
    root = nullptr;
}

void arithmeticExpression::buildTree()
{ // create a stack to save operands
    string postfix = infix_to_postfix();
	stack<TreeNode*> tree;
    char key = 'a';

	for (unsigned i = 0; i < postfix.size(); ++i) 
    {
        TreeNode *newNode = new TreeNode(postfix.at(i), key + i);
		if (priority(postfix.at(i)) == 0)  // if operand
        {
			tree.push(newNode);
		}
		else if (priority(postfix.at(i)) > 0) // if operator
        { // save each internal node
			newNode->right = tree.top();
			tree.pop();
			newNode->left = tree.top();
			tree.pop();
			tree.push(newNode);
			root = newNode;
		}
	}
}

void arithmeticExpression::infix()
{
    infix(root);
}

void arithmeticExpression::prefix()
{
    prefix(root);
}

void arithmeticExpression::postfix()
{
    postfix(root);
}

void arithmeticExpression::infix(TreeNode *node) // (a+(b*c))
{
    if (node)
    {
        if (node->left)
        {
            cout << '(';
        }
        infix(node->left);
        cout << node->data;
        infix(node->right);
        if (node->right)
        {
            cout << ')';
        }
    }
}

void arithmeticExpression::prefix(TreeNode *node) // +a*bc
{
    if (node)
    {
        cout << node->data;
        prefix(node->left);
        prefix(node->right);
    }
}

void arithmeticExpression::postfix(TreeNode *node) // abc*+
{
    if (node)
    {
        postfix(node->left);
        postfix(node->right);
        cout << node->data;
    }
}