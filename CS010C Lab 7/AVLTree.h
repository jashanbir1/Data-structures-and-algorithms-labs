#ifndef AVLTREE_H
#define AVLTREE_H
#include <iostream>
#include <cstdlib>

using namespace std;

#include "Node.h"

class AVLTree {

    private:
    Node* root;

    public:
    void insert(const string &);
    int balanceFactor(Node*);
    void printBalanceFactors();
    AVLTree();

    private:
    void recurPrintBalFactors(Node *);
    //Node* findUnbalancedNode(Node* ):
    bool replaceChild(Node*, Node*, Node*);
    bool setChild(Node*, string, Node*);
    void updateHeight(Node* );
    void rebalance(Node* );
    void rotate(Node* );
    void rotateLeft(Node* );
    void rotateRight(Node* );

};
#endif
