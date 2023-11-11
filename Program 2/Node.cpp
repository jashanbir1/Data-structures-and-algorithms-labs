#include <iostream>
#include <string>

using namespace std;

#include "Node.h"

Node:: Node(string myString)
{
    left = nullptr;
    right = nullptr;
    data = myString;
    count = 1;
}

void Node:: setData(string myString)
{
    data = myString;
}

void Node:: setLeft(Node* lefty)
{
    left = lefty;
}

void Node:: setRight(Node* righty)
{
    right = righty;
}

void Node:: setCount(int myCount)
{
    count = myCount;
}

string Node::getData() const
{
    return data;
}

Node* Node:: getLeft() const
{
    return left;
}

Node* Node:: getRight() const
{
    return right;
}

int Node:: getCount() const
{
    return count;
}