#include <iostream>
#include <string>

using namespace std;

#include "BSTree.h"

/* WAS UNABLE TO FIGURE OUT REMOVE FUNCTION PARAMETER WITH EMPTY TREE, MEMORY ERROR, EVERY OTHER FUNCTION WORKS*/


BSTree::BSTree()
{
    root = nullptr;
}

BSTree::~BSTree()
{
    delete root;
}

Node* BSTree:: max1(Node* maxVal)// helper function for remove
{
    if(maxVal->getRight() == nullptr)// if largest val right leaf is empty
    {
        return maxVal;// return node
    }
    return max1(maxVal->getRight());// recursively go down right subtree
}

Node* BSTree:: min1(Node* minVal)
{
    if(minVal->getLeft() == nullptr)// if left leaf of min val is empty
    {
        return minVal;// return node
    }
    return min1(minVal->getLeft());// recursively go down left tree
}

void BSTree:: insert(const string& newStr)
{
    Node* newNode = new Node(newStr);// create new node in heap to insert
    Node* currNode = root;// set a root node

    if(root == nullptr)// if empty tree, set newNode to the root
    {
        root = newNode;
        root->setRight(nullptr);
        root->setLeft(nullptr);
    }
    else
    {
        while(currNode != nullptr)// while tree is not empty
        {
            if(newNode->getData() == currNode->getData())// if more than one of same type of string
            {
                currNode->setCount(currNode->getCount() + 1);// increase count
                return;
            }
            if(newNode->getData() < currNode->getData())// if new node is less than currnode
            {
                if(currNode->getLeft() == nullptr)// if left leaf is empty
                {
                    currNode->setLeft(newNode);// set new node to left leaf
                    break;
                }
                else
                {
                    currNode = currNode->getLeft();// keep going down tree
                }
            }
            else
            {
                if (newNode->getData() > currNode->getData())// if new node is greater than curr node
                {
                    if(currNode->getRight() == nullptr)// if empty leaf in right subtree
                    {
                        currNode->setRight(newNode);//set right leaf to new node
                        break;
                    }
                    else
                    {
                        currNode = currNode->getRight();// keep going down right subtree
                    }
                }
            }
        }
    }

}
void BSTree:: recursiveRemove(Node *prevNode, Node* currNode, string rmvStr)
{
    if (currNode == nullptr) { //empty tree
        return;
    }
    else if(currNode->getData() == rmvStr){ //found node we want to remove
        if(currNode->getCount() > 1 && currNode->getData() != prevNode->getData()){
            currNode->setCount(currNode->getCount() - 1); //removing element that's count is >1
            return;
        }
        if(currNode == root && currNode->getCount() > 1){ //if node that's found is root and has count >1
            currNode->setCount(currNode->getCount() - 1);
            return;
        }
        else if(!currNode->getRight() && !currNode->getLeft()) { //if node to be removed was a leaf

            if(currNode->getData() > prevNode->getData()) { //if it was on the right of prev
                prevNode->setRight(nullptr);
                delete currNode;
                return;
            }
            else if(currNode->getData() < prevNode->getData()) { //if on left of prev
                prevNode->setLeft(nullptr);
                delete currNode;
                return;
            }
            else if(currNode->getData() == prevNode->getData()) { //if equal to prev
                if(prevNode->getRight() == nullptr){ //if right is already nptr
                    prevNode->setLeft(nullptr); //delete left
                    delete currNode;
                }
                else if(prevNode->getLeft() == nullptr) { // vice versa ^
                    prevNode->setRight(nullptr);
                    delete currNode;
                     }
                else if(prevNode->getRight() && prevNode->getLeft()){ //if both right and left aren't null
                    if(currNode->getData() == prevNode->getLeft()->getData()){  // if equal to left
                        prevNode->setLeft(nullptr);
                        delete currNode;
                    }
                    else if(currNode->getData() == prevNode->getRight()->getData()){//vice versa
                        prevNode->setRight(nullptr);
                        delete currNode;
                    }
                }
            }
        }
        else if((currNode->getLeft() != nullptr && currNode->getRight() != nullptr) || (currNode->getLeft() != nullptr && currNode->getRight() == nullptr)){ //if not a leaf node
            Node* leftVal = max1(currNode->getLeft()); //calls max to find largest from that point forward
            currNode->setData(leftVal->getData());
            currNode->setCount(leftVal->getCount());
            recursiveRemove(currNode, currNode->getLeft(), currNode->getData());
        }
        else if(!currNode->getLeft() && currNode->getRight()){ //if left u want to find min
            Node* rightVal = min1(currNode->getRight());
            currNode->setData(rightVal->getData());
            currNode->setCount(rightVal->getCount());
            recursiveRemove(currNode, currNode->getRight(), currNode->getData());
        }
    }
    else if(currNode->getData() < rmvStr){ // if node is less than root
        recursiveRemove(currNode, currNode->getRight(), rmvStr);
    }
    else if (currNode->getData() > rmvStr) { //greater than root
        recursiveRemove(currNode, currNode->getLeft(), rmvStr);
    }
}

void BSTree:: remove(const string &key)
{
    recursiveRemove(root,root, key);// recursively call remove
}

Node* BSTree:: recursiveSearch(const string &key, Node* currNode) const
{
    if (currNode != nullptr)// if not empty tree
    {
        if(currNode->getData() == key)// if data is at currnode
        {
            return currNode; //return string
        }
    
        else
        {
            if (key < currNode->getData())// if key is less than currnode
            {
                return recursiveSearch(key,currNode->getLeft());// recursively go left
            }
            else
            {
                return recursiveSearch(key,currNode->getRight());// recursvely go right
            }
        }
    }
    else
    {
        return 0;// string not found, return
    }
}

bool BSTree:: search(const string &key) const
{
    return recursiveSearch(key, root);// call recrusive search function
}

string BSTree:: largest() const// get largest in right subtree
{
    Node* currNode = root;
    if (currNode == nullptr)
    {
        return "";
    }
    else
    {
        while(currNode->getRight() != nullptr)// if right subtree is not null
        {
            currNode = currNode->getRight();// keep going right
        }
        return currNode->getData();// return largest string
    }
}

string BSTree:: smallest() const// return smallest element
{
    Node* currNode = root;
    if (currNode == nullptr)
    {
        return "";
    }
    else
    {
        while(currNode->getLeft() != nullptr)// while left subtree next is not nullptr
        {
            currNode = currNode->getLeft();// keep getting left
        }
        return currNode->getData();// once it is null, return the string
    }
}

int BSTree:: height(const string& heightString) const
{
    if(!search(heightString))// if string is not in tree, return -1
    {
        return -1;
    }

    Node* currNode = recursiveSearch(heightString,root);// set currnode to the string we want
    Node* Lefty = currNode;// set left to currnode
    Node* Righty = currNode;//set right to currnode
    int leftNum = 0;
    int rightNum = 0;

    if(currNode->getLeft() != nullptr)// if left is not null
    {
        Lefty = Lefty->getLeft();//get next left element
        leftNum++;//add the edge
        leftNum += height(Lefty->getData());
    }
    if(currNode->getRight() != nullptr)// if right subtree is not empty
    {
        Righty = Righty->getRight();// get next right
        rightNum++;// add the edge
        rightNum += height(Righty->getData());
    }
    // return the larger height, left or right subtree
    if(leftNum >= rightNum)
    {
        return leftNum;
    }
    else
    {
        return rightNum;
    }
}

void BSTree:: recursiveInOrder(Node *inOrderNode) const// traverse from left subtree, root, right subtree
{
    if(inOrderNode)
    {
        recursiveInOrder(inOrderNode->getLeft());
        cout << inOrderNode->getData() << "(" << inOrderNode->getCount() << "), ";
        recursiveInOrder(inOrderNode->getRight());
    }

}
void BSTree:: recursivePostOrder(Node *PostOrderNode) const // traverse from left subtree, right subtree, then root
{
    if(PostOrderNode)
    {
        recursivePostOrder(PostOrderNode->getLeft());
        recursivePostOrder(PostOrderNode->getRight());
        cout << PostOrderNode->getData() << "(" << PostOrderNode->getCount() << "), ";
    }
}
void BSTree:: recursivePreOrder(Node *PreOrderNode) const// traverse from root, to left subtree, then right subtree
{
    if(PreOrderNode)
    {
        cout << PreOrderNode->getData() << "(" << PreOrderNode->getCount() << "), ";
        recursivePreOrder(PreOrderNode->getLeft());
        recursivePreOrder(PreOrderNode->getRight());
    }
}
void BSTree:: preOrder() const
{
    recursivePreOrder(root);// call recursive preOrder
    cout << endl;
}
void BSTree:: postOrder() const
{
    recursivePostOrder(root); // call recursive PostOrder
    cout << endl;
}
void BSTree:: inOrder() const
{
    recursiveInOrder(root);// call recursive InOrder
    cout << endl;
}