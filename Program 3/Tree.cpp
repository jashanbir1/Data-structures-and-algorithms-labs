#include "Tree.h"
#include <iostream>

using namespace std;

Tree:: Tree()
{
    root = nullptr;
}
Tree:: ~Tree()
{
    if(root != nullptr)
    {
        recurDestructor(root);
    }
}
void Tree:: recurDestructor(Node* deleteTree)
{
    if(deleteTree != nullptr)
    {
        recurDestructor(deleteTree->left);
        recurDestructor(deleteTree->middle);
        recurDestructor(deleteTree->right);
        delete deleteTree;
    }
}

void Tree:: split(Node* tree, const string& splitStr)
{
    Node *lefty = nullptr;
    Node *righty = nullptr;
    string middleStr = "";

    if(splitStr == tree->small || splitStr == tree->large){ //error case for duplicates
        throw runtime_error("duplicate");
    }
    //setting the A,B,C or left,middle, and right to prepare for split
    if(splitStr < tree->small){ //edge case for when the splitStr is smaller than both keys in tree
        lefty = new Node(splitStr);
        righty = new Node(tree->large);
        middleStr = tree->small;

        
    }
    else if(splitStr > tree->large){ //edge case for when the splitStr is larger than both keys in tree
        lefty = new Node(tree->small);
        middleStr = tree->large;
        righty = new Node(splitStr);


    }
    else{ //when splitStr is in between
        lefty = new Node(tree->small);
        middleStr = splitStr;
        righty = new Node(tree->large);

    }
    //making the current node a single splitStr to prepare for split
    tree->large = "";
    --tree->nodeCntData;

    if(tree->parent != nullptr){// edge case for when the node has parents
        //promote middleStr to parent large splitStr
        tree->parent->large = middleStr;
        ++tree->parent->nodeCntData;
        // previous left and right child become middle and right child
        tree->parent->middle = lefty;
        lefty->parent = tree->parent;
        tree->parent->right = righty;
        righty->parent = tree->parent;
    }
    else{ 
        //making middleStr parent of lefty and right child
        tree->small = middleStr;
        tree->left = lefty;
        tree->right = righty;
        lefty->parent = tree;
        righty->parent = tree;
    }
}

void Tree:: insert(const string &insurtStr)
{
    if(root == nullptr)
    {
        root = new Node(insurtStr);
    }
    recurInsert(root,insurtStr);
}

void Tree:: recurInsert(Node* tree, const string& insertStr)
{
    if(insertStr < tree->small){ //edge case for when insertStr is smaller than both keys
        if(tree->nodeCntData == 1){
            if(tree->left == nullptr){
                tree->large = tree->small;
                tree->small = insertStr;
                ++tree->nodeCntData; 
            }
            else{
                recurInsert(tree->left, insertStr);
            }
        }
        else if(tree->nodeCntData == 2){
            if(tree->left != nullptr){
                recurInsert(tree->left,insertStr);
            }
            else{
                split(tree, insertStr);
            }
        }
        else{
            split(tree, insertStr);
        }
    }
    else if(insertStr > tree->small){ // when insertStr either in between or bigger than tree
        if(tree->nodeCntData == 1){ //check how many are in tree
            if(tree->right == nullptr){  //if at leaf then insert as large insertStr in tree
                tree->large = insertStr;
                ++tree->nodeCntData;
            }
            else{
                recurInsert(tree->right, insertStr); //else branch to the right
            }
        }
        else if(tree->nodeCntData == 2 && insertStr < tree->large){ // when insertStr is bigger than both in tree
            if(tree->middle != nullptr){ //recursively call insert to insert in the middle
                recurInsert(tree->middle, insertStr);
            }
            else{ //else lost so split
                split(tree, insertStr);
            }
        }
        else{
            split(tree, insertStr);
        }
    }

}

void Tree:: remove(const string &remooveStr)
{
    recurRemove(remooveStr,root);
}

void Tree:: recurRemove(const string& removeStr, Node* tree)
{
     if(tree == nullptr){
        return;
    }
    //check if node exists
    if(recurSearch(tree,removeStr)){
        //find the node contianing removeStr
        tree = nodeSearch(tree, removeStr);
        //if node is root
        if(tree->parent == nullptr){
            //if a leaf
            if(tree->left == nullptr && tree->right == nullptr){
                //if only 1 removeStr inside
                if(tree->nodeCntData == 1){
                    delete tree;
                    root = nullptr;
                }
                //more than 1 removeStr
                else{
                    //check to see which removeStr is the removeStr we are trying to remove
                    if(tree->small == removeStr){
                        tree->small = tree->large;
                        tree->large = "";
                        --tree->nodeCntData;
                    }
                    else if(tree->large == removeStr){
                        tree->large = "";
                        --tree->nodeCntData;
                    }
                }
            }
            else{ //node has children
                tree->small = tree->left->small;
                tree->large = tree->right->small;
                ++tree->nodeCntData;
                delete tree->right;
                delete tree->left;
                tree->right = nullptr;
                tree->left = nullptr;

            }
        }
        else{ //node is not root
            if(tree->nodeCntData == 1){ // node has one removeStr
                Node* treeParent = tree->parent;
                if(treeParent->right == tree){  //node is right child of parent
                    treeParent->large = treeParent->small;
                    treeParent->small = treeParent->left->small;
                }
                else if(treeParent->left == tree){ //node is left child
                    treeParent->large = treeParent->right->small;
                }
                ++treeParent->nodeCntData;
                delete treeParent->left;
                delete treeParent->right;
                treeParent->left = nullptr;
                treeParent->right = nullptr;
            }
            else{ // more than one removeStr
                if(tree->small == removeStr){ //in case the small field
                    tree->small = tree->large;
                }
                --tree->nodeCntData;
                tree->large = "";         
            }
        }
    }
    
}
bool Tree:: search(const string &searchKey) const
{
    return recurSearch(root, searchKey);
}

bool Tree:: recurSearch(Node* tree, const string& serchKey) const
{
    if(tree == nullptr)
    {
        return false;
    }
    if (tree->small == serchKey || tree->large == serchKey)
    {
        return true;
    }
    else
    {
        if(serchKey < tree->small)
        {
            return recurSearch(tree->left,serchKey);
        }
        else if(tree->nodeCntData == 2 && serchKey < tree->large)
        {
            return recurSearch(tree->middle, serchKey);
        }
        else 
        {
            return recurSearch(tree->right, serchKey);
        }
    }   
}

Node* Tree:: nodeSearch(Node* tree, const string&  searchNodeStr)
{
    if(tree == nullptr){ //if empty
        return nullptr;
    }
    if(tree->small == searchNodeStr || tree->large == searchNodeStr){ //if key found return the node
        return tree;
    }
    else{
        if(searchNodeStr < tree->small){
            return nodeSearch(tree->left, searchNodeStr); //traverse left
        }
        else if(tree->nodeCntData == 2 && searchNodeStr < tree->large){
            return nodeSearch(tree->middle, searchNodeStr); //traverse down the middle
        }
        else{
            return nodeSearch(tree->right, searchNodeStr); //traverse right
        }
    }
}
void Tree:: preOrder( ) const
{
    recurPreOrder(root);
}

void Tree:: inOrder( ) const
{
    recurInOrder(root);
}

void Tree:: postOrder( ) const
{
    recurPostOrder(root);
}

void Tree:: recurPreOrder(Node* tree) const
{
    if(tree == nullptr)
    {
        return;
    }
    else
    {
        if(tree->nodeCntData == 1)// has only one key in node
        {
            cout << tree->small << ", ";
            recurPreOrder(tree->left);
            recurPreOrder(tree->right);
        }
        else if(tree->nodeCntData == 2) // has two keys in a node
        {
            cout << tree->small << ", ";
            recurPreOrder(tree->left);
            cout << tree->large << ", ";
            recurPreOrder(tree->middle);
            recurPreOrder(tree->right);
        }
    }
}
void Tree:: recurInOrder(Node* tree) const
{
    if (tree == nullptr)
    {
        return;
    }
    else
    {
        if(tree->nodeCntData == 1)// has only one key in node
        {
            recurInOrder(tree->left);
            cout << tree->small << ", ";
            recurInOrder(tree->right);
        }
        else if(tree->nodeCntData == 2) // has two keys in a node
        {
            recurInOrder(tree->left);
            cout << tree->small << ", ";
            recurInOrder(tree->middle);
            cout << tree->large << ", ";
            recurInOrder(tree->right);
        }
    }
}

void Tree:: recurPostOrder(Node* tree) const
{
    if(tree == nullptr)
    {
        return;
    }
    else
    {
        if(tree->nodeCntData == 1)// has only one key in node
        {
            recurPostOrder(tree->left);
            recurPostOrder(tree->right);
            cout << tree->small << ", ";
        }
        else if(tree->nodeCntData == 2) // has two keys in a node
        {
            recurPostOrder(tree->left);
            recurPostOrder(tree->middle);
            cout << tree->small << ", ";
            recurPostOrder(tree->right);
            cout << tree->large << ", ";
        }
    }
}