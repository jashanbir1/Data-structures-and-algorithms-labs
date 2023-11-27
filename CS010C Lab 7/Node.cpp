#include <iostream>
#include <string>
#include <cstdlib>

#include "Node.h"

Node:: Node(string nodString)
{
    key = nodString;
    height = 0;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
}