#include "Tree.h"
#include <iostream>

using namespace std;

Tree:: Tree()// constructor, constructs root to null
{
    root = nullptr;
}
Tree:: ~Tree()// destructor
{
    if(root != nullptr)
    {
        recurDestructor(root);// calls recursive destructor
    }
}
void Tree:: recurDestructor(Node* deleteTree)// recursively deletes tree
{
    if(deleteTree != nullptr)
    {
        recurDestructor(deleteTree->left);// goes down left tree
        recurDestructor(deleteTree->middle);// goes down middle of tree
        recurDestructor(deleteTree->right);// goes down right side of tree
        delete deleteTree;// delete node
    }
}

void Tree:: split(Node* tree, const string& splitStr)// split helper for insert
{
    Node *lefty = nullptr;// left child
    Node *righty = nullptr;// right child
    string middleStr = "";// middle key

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

void Tree:: insert(const string &insurtStr)// insert, calls helper recursive insert
{
    if(root == nullptr)// if empty tree
    {
        root = new Node(insurtStr);// new val as root
    }
    recurInsert(root,insurtStr);// call recursive insert
}

void Tree:: recurInsert(Node* tree, const string& insertStr)// recursive helper for insert function
{
    if(insertStr < tree->small){ //edge case for when insertStr is smaller than both keys
        if(tree->nodeCntData == 1){// if only one key
            if(tree->left == nullptr)//if left child is empty
            {
                tree->large = tree->small;// assign large and small to each other cuz only one 1 value
                tree->small = insertStr;// assign small with string
                ++tree->nodeCntData;// add num of keys in tree
            }
            else
            {
                recurInsert(tree->left, insertStr);// insert on left leaf
            }
        }
        else if(tree->nodeCntData == 2)// has two keys in a node
        {
            if(tree->left != nullptr)// if left leaf is empty
            {
                recurInsert(tree->left,insertStr);// insert string
            }
            else
            {
                split(tree, insertStr);// split to insert string
            }
        }
        else
        {
            split(tree, insertStr);// split
        }
    }
    else if(insertStr > tree->small) // when insertStr either in between or bigger than tree
    { 
        if(tree->nodeCntData == 1) //check how many are in tree
        { 
            if(tree->right == nullptr)//if at leaf then insert as large insertStr in tree
            {  
                tree->large = insertStr;
                ++tree->nodeCntData;
            }
            else{
                recurInsert(tree->right, insertStr); //else branch to the right
            }
        }
        else if(tree->nodeCntData == 2 && insertStr < tree->large)// when insertStr is bigger than both in tree
        { 
            if(tree->middle != nullptr)//recursively call insert to insert in the middle
            { 
                recurInsert(tree->middle, insertStr);
            }
            else //else lost so split
            { 
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
    if(recurSearch(tree,removeStr))
    {
        //find the node contianing removeStr
        tree = nodeSearch(tree, removeStr);
        //if node is root
        if(tree->parent == nullptr){
            //if a leaf
            if(tree->left == nullptr && tree->right == nullptr)
            {
                //if only 1 removeStr inside
                if(tree->nodeCntData == 1)
                {
                    delete tree;
                    root = nullptr;
                }
                //more than 1 removeStr
                else
                {
                    //check to see which removeStr is the removeStr we are trying to remove
                    if(tree->small == removeStr)
                    {
                        tree->small = tree->large;
                        tree->large = "";
                        --tree->nodeCntData;
                    }
                    else if(tree->large == removeStr)
                    {
                        tree->large = "";
                        --tree->nodeCntData;
                    }
                }
            }
            else //node has children
            { 
                tree->small = tree->left->small;
                tree->large = tree->right->small;
                ++tree->nodeCntData;
                delete tree->right;
                delete tree->left;
                tree->right = nullptr;
                tree->left = nullptr;

            }
        }
        else //node is not root
        { 
            if(tree->nodeCntData == 1) // node has one removeStr
            { 
                Node* treeParent = tree->parent;
                if(treeParent->right == tree) //node is right child of parent
                {  
                    treeParent->large = treeParent->small;
                    treeParent->small = treeParent->left->small;
                }
                else if(treeParent->left == tree) //node is left child
                { 
                    treeParent->large = treeParent->right->small;
                }
                ++treeParent->nodeCntData;
                delete treeParent->left;
                delete treeParent->right;
                treeParent->left = nullptr;
                treeParent->right = nullptr;
            }
            else // more than one removeStr
            { 
                if(tree->small == removeStr) //in case the small field
                { 
                    tree->small = tree->large;
                }
                --tree->nodeCntData;
                tree->large = "";         
            }
        }
    }
    
}
bool Tree:: search(const string &searchKey) const // call recur bool search
{
    return recurSearch(root, searchKey);
}

bool Tree:: recurSearch(Node* tree, const string& serchKey) const
{
    if(tree == nullptr)// if tree is empty
    {
        return false;// no strings to search for, return false
    }
    if (tree->small == serchKey || tree->large == serchKey)// if word is found
    {
        return true;
    }
    else
    {
        if(serchKey < tree->small)// if word is less than smaller key
        {
            return recurSearch(tree->left,serchKey);// search left tree
        }
        else if(tree->nodeCntData == 2 && serchKey < tree->large)// if node has two keys and less than larger string
        {
            return recurSearch(tree->middle, serchKey);// search middle
        }
        else 
        {
            return recurSearch(tree->right, serchKey);// string is large, search right tree
        }
    }   
}

Node* Tree:: nodeSearch(Node* tree, const string&  searchNodeStr)// return node
{
    if(tree == nullptr){ //if empty
        return nullptr;// no string, return null
    }
    if(tree->small == searchNodeStr || tree->large == searchNodeStr){ //if key found return the node
        return tree;
    }
    else{
        if(searchNodeStr < tree->small){
            return nodeSearch(tree->left, searchNodeStr); //string is smaller than small key, traverse left
        }
        else if(tree->nodeCntData == 2 && searchNodeStr < tree->large)// node has two keys, and less than large string
        {
            return nodeSearch(tree->middle, searchNodeStr); //traverse down the middle
        }
        else{
            return nodeSearch(tree->right, searchNodeStr); //key is larger than middle and left, traverse right
        }
    }
}
void Tree:: preOrder( ) const
{
    recurPreOrder(root); // call recursive preOrder 
}

void Tree:: inOrder( ) const
{
    recurInOrder(root);// call recursive InOrder
}

void Tree:: postOrder( ) const
{
    recurPostOrder(root); // call recursive PostOrder
}

void Tree:: recurPreOrder(Node* tree) const
{
    if(tree == nullptr)
    {
        return; // if tree, is empty, nothing to print
    }
    else
    {
        if(tree->nodeCntData == 1)// has only one key in node
        {
            // print in order of root, left leaf, right leaf
            cout << tree->small << ", ";
            recurPreOrder(tree->left);
            recurPreOrder(tree->right);
        }
        else if(tree->nodeCntData == 2) // has two keys in a node
        {
            // print in order of key, then left, , key, then middle, then right
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
        return;// if empty, nothing to print, return
    }
    else
    {
        if(tree->nodeCntData == 1)// has only one key in node
        {
            //print in order of left, then root, then right
            recurInOrder(tree->left);
            cout << tree->small << ", ";
            recurInOrder(tree->right);
        }
        else if(tree->nodeCntData == 2) // has two keys in a node
        {
            // print in order of left, key, then middle, , key, then right
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
            //print in order of left, then right, then key
            recurPostOrder(tree->left);
            recurPostOrder(tree->right);
            cout << tree->small << ", ";
        }
        else if(tree->nodeCntData == 2) // has two keys in a node
        {
            // print in order of left, then middle, then right, then key
            recurPostOrder(tree->left);
            recurPostOrder(tree->middle);
            cout << tree->small << ", ";
            recurPostOrder(tree->right);
            cout << tree->large << ", ";
        }
    }
}