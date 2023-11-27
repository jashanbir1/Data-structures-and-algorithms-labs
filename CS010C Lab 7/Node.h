#ifndef NODE_H
#define NODE_H
#include <string>
using namespace std;

struct Node {

    public:

    Node(string );
    int height;
    string key;
    Node* left;
    Node* right;
    Node* parent;
};

#endif