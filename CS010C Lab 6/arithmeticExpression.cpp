#include <iostream>
#include <string>
#include <stack>
#include <sstream>

#include "arithmeticExpression.h"

using namespace std;

arithmeticExpression:: arithmeticExpression(const string &arithString)// construct the empty tree
{
    root = nullptr;// set root to empty
    infixExpression = arithString;// set the expression to passed in string
}

arithmeticExpression:: ~arithmeticExpression()// destructor
{
    delete root;// delete the root of the tree as necessary
}

void arithmeticExpression:: buildTree()// build the arithmetic tree with stack implementation
{
    infixExpression = infix_to_postfix();// set expression to postfix
	stack <TreeNode*> stak;// initialize a stack ADT and variable

	for (unsigned i = 0; i < infixExpression.size(); ++i)// for loop to iterate through tree
    {
		TreeNode *insertNode = new TreeNode(infixExpression.at(i), 'a' + i);// initialize a new node
		if (priority(infixExpression.at(i)) == 0) {
			stak.push(insertNode);// push new nodeto top of stack
		}
		else if (priority(infixExpression.at(i)) > 0)//if priority is positive
        {
			insertNode->right = stak.top();// set right insertNode node to top
			stak.pop();// pop from front of stack
			insertNode->left = stak.top();// set left insertNode to top
			stak.pop();// pop from front of stack
			stak.push(insertNode);// push insert node to top of stack
			root = insertNode;// set root to insert node, aka top of stack
		}
	}
}

void arithmeticExpression:: infix()// uses recurisve infix
{
    if(root == nullptr)
    {
        throw runtime_error("empty tree, cannot print");// if empty tree, send error message
    }
    infix(root);
}

void arithmeticExpression:: infix(TreeNode* currNode)// recursive infix, goes from left subtree, root, right subtree
{
    if(currNode != nullptr)// while tree is not empty
    {
        if(currNode->left != nullptr)// if left node is not empty
        {
            cout << "(";// output parentheses around the order
        }
        infix(currNode->left);
        cout << currNode->data;
        infix(currNode->right);

        if(currNode->right != nullptr)
        {
            cout << ")";// close parentheses around values
        }
    }
}

void arithmeticExpression:: postfix(TreeNode* currNode)// recursive postfx, left tree, right tree, root
{
    if(currNode != nullptr)
    {
        postfix(currNode->left);
        postfix(currNode->right);
        cout << currNode->data;
    }
}
void arithmeticExpression:: postfix()// uses recursive postfix
{
    if(root == nullptr)
    {
        throw runtime_error("empty tree, cannot print");// if empty tree, throw error message
    }
    postfix(root);
}
void arithmeticExpression:: prefix(TreeNode* currNode)// recursve prefix, root,left tree, right tree
{
    if(currNode != nullptr)
    {
        cout << currNode->data;
        prefix(currNode->left);
        prefix(currNode->right);
    }
}
void arithmeticExpression:: prefix()// uses recursive prefix
{
    if(root == nullptr)
    {
        throw runtime_error("empty tree, cannot print");
    }
    prefix(root);
}
int arithmeticExpression::priority(char op){// given code from instructor
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

string arithmeticExpression::infix_to_postfix(){// given code from professor
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

void arithmeticExpression::visualizeTree(const string &outputFilename){
}
