#include <iostream>
#include <string>
#include <cstdlib>
#include <algorithm>

using namespace std;

#include "AVLTree.h"

AVLTree:: AVLTree()// set root to nullptr
{
    root = nullptr;
}

void AVLTree:: insert(const string& insertNode)
{
    // REFERENCED ZYBOOKS AND GOT HELP FROM TA
    Node* insertCurr = root;// set to root to check if if insertNode is less than or greater than curr key
    while (insertCurr != nullptr)
    {
        if (insertCurr->key > insertNode)//if insertcurr key is greater than insertNode
        {
            insertCurr = insertCurr->left;
        }
        else if (insertCurr->key < insertNode)// if insert curr key is less than insertNode
        {
            insertCurr = insertCurr->right;
        }
        else
        {
            return;
        }
    }

    Node* newNode = new Node(insertNode);// create new node in heap

    if (root == nullptr)// if empty tree
    {
        root = newNode;// set root to new node
        newNode->parent = nullptr;// set the parent to nullptr
        return;
    }

    Node* insertCur = root;// set insertcur to root

    while (insertCur)// insertCur is not empty
    {
        if (newNode->key < insertCur->key)// if new nodes key us less than non empty tree node key
        {
            if (insertCur->left == nullptr)// if left leaf is empty
            {
                insertCur->left = newNode;// insert new node in left
                newNode->parent = insertCur;// set parent to insertcurr node
                insertCur = nullptr;
            }
            else
            {
                insertCur = insertCur->left;// traverse down left tree
            }
        }
        else
        {
            if (insertCur->right == nullptr)// if right tree is empty
            {
                insertCur->right = newNode;// set right leaf to new node
                newNode->parent = insertCur;// set parent to insert cur node
                insertCur = nullptr;
            }
            else
            {
                insertCur = insertCur->right;// travrse down right tree
            }
        }
    }

    newNode = newNode->parent; // set new node to the parent

    while(newNode)// while new node is not null
    {
        rebalance(newNode); //rebalance from new node
        newNode = newNode->parent; //set new node to the new node parent
    }
}

int AVLTree:: balanceFactor(Node* balNode)
{
    // REFERENCED ZYBOOKS
    int leftHeight = -1;// set left height to default -1
    int rightHeight = -1;// set left height to default -1

    if(balNode->left != nullptr)// while left tree is not null
    {
        leftHeight = balNode->left->height;// set left height to balnode left height
    }

    if(balNode->right != nullptr) //while right tree is not null
    {
        rightHeight = balNode->right->height;// set right height to right height 
    }
    
    return leftHeight - rightHeight;// subtract right by left
    
}

void AVLTree:: updateHeight(Node* updateNode) 
{
    //REFERENCED ZBOOKS
    int leftHeight = -1;// set left height to default -1
    int rightHeight = -1;// set left height to default -1

    if(updateNode->left != nullptr)// while left tree is not null
    {
        leftHeight = updateNode->left->height;// set left height to balnode left height
    }

    if(updateNode->right != nullptr)//while right tree is not null
    {
        rightHeight = updateNode->right->height;// set right height to right height 
    }

    updateNode->height = max(leftHeight,rightHeight) + 1; // return the max between left height and right height

}

void AVLTree:: rebalance(Node* rebalNode)// rebalance the tree
{
    //REFERENCED ZYBOOKS

    updateHeight(rebalNode);// call update height on rebal node

    if(balanceFactor(rebalNode) == -2)
    {
        if(balanceFactor(rebalNode->right) == 1)
        {
            rotateRight(rebalNode->right);// rotate right if balance fact of right tree is 1
        }
        rotateLeft(rebalNode);
    }
    else if(balanceFactor(rebalNode) == 2)
    {
        if(balanceFactor(rebalNode->left) == -1)
        {
            rotateLeft(rebalNode->left);// rotate right if balance fact of right tree is -1
        }
        rotateRight(rebalNode);
    }
}

bool AVLTree:: setChild(Node* parent, string whichChild, Node* childNode)
{
    //REFERENCED ZYBOOKS
    if(whichChild != "left" && whichChild != "right")// does not have left or right 
    {
        return false;// return false if statement not true
    }

    if(whichChild == "left")
    {
        parent->left = childNode;// if string equals left, parent left leaf equals child
    }
    else
    {
        parent->right = childNode;// else make right leaf equal to child
    }
    if(childNode != nullptr)
    {
        childNode->parent = parent;// set child node parent to parent
    }

    updateHeight(parent);// update height of parent node
    return true;
}

bool AVLTree:: replaceChild(Node* parNode, Node* currChild, Node* newChild)
{
    // REFERENCE ZYBOOKS
    if(parNode->left == currChild)// if par node left equals curr child
    {
        return setChild(parNode, "left", newChild);// Return the parent node and left string
    }
    else if(parNode->right == currChild)// if par node right equals curr child
    {
        return setChild(parNode, "right", newChild);// return the parent node and right string
    }
    return false;// else return false
}

void AVLTree:: rotate(Node* rotateNode)
{
    if(balanceFactor(rotateNode) == 2)// if balance factor is 2
    {
        if(balanceFactor(rotateNode->left) == -1)// if balance factor equals -1
        {
            rotateLeft(rotateNode->left);// rotate left to reallign
        }
        rotateRight(rotateNode);// call rotate right on the whole node
    }
    else if(balanceFactor(rotateNode) == -2)// if balance factor equals -2
    {
        if(balanceFactor(rotateNode->right) == 1)// if balnce factor right equals 1
        {
            rotateRight(rotateNode->right);// call rotate right on right tree
        }
        rotateLeft(rotateNode);// call on whole tree
    }
}
void AVLTree:: rotateRight(Node* leftNode)
{
    // REFERENCED ZYBOOKS
    Node* leftRightChild = leftNode->left->right;// set node to left right

    if(leftNode->parent != nullptr)// if left tree is not empty
    {
        replaceChild(leftNode->parent, leftNode, leftNode->left); //call replace child
    }
    else
    {
        root = leftNode->left;// set root to left leaf
        root->parent = nullptr;// set parent to nullptr
    }

    setChild(leftNode->left, "right", leftNode);// set child to left->left and right string
    setChild(leftNode, "left", leftRightChild);// set child to left node and left string
}

void AVLTree:: rotateLeft(Node* rightNode)// rotatete left
{
    Node* rightLeftChild = rightNode->right->left;// set node to rightnodes right leafs left

    if(rightNode->parent != nullptr)// if right tree is not empty
    {
        replaceChild(rightNode->parent, rightNode, rightNode->right);// call replace child
    }
    else
    {
        root = rightNode->right;//set root to right
        root->parent = nullptr;// set parent to nullptr
    }

    setChild(rightNode->right, "left", rightNode);// set child to right->right and left string
    setChild(rightNode, "right", rightLeftChild);// set child to right node and right string
}

void AVLTree:: printBalanceFactors()
{
    recurPrintBalFactors(root);// call recursive print balance factors on the root
    cout << endl;
}

void AVLTree:: recurPrintBalFactors(Node* printNode)
{
    if(printNode)// while print node is not empty
    {
        recurPrintBalFactors(printNode->left);// call print bal factors left tree
        cout << printNode->key << "(" << balanceFactor(printNode) << "), ";// print out data
        recurPrintBalFactors(printNode->right);// call print bal factors on right tree
    }
}