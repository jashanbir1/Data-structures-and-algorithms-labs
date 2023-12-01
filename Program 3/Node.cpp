#include "Node.h"
#include <iostream>
#include <cstdlib>

using namespace std;

Node:: Node()
{
    small = "";
    large = "";
    left = nullptr;
    middle = nullptr;
    right = nullptr;
    parent = nullptr;
    nodeCntData = 1;

}

Node:: Node(const string& nodeStr)
{
    small = nodeStr;
    large = "";
    left = nullptr;
    middle = nullptr;
    right = nullptr;
    parent = nullptr;
    nodeCntData = 1;

}