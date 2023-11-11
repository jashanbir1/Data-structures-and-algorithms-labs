#ifndef _NODE_H_
#define _NODE_H_
#include <string>

using namespace std;

class Node
{
  private:
    string data;
    Node* left;
    Node* right;
    int count;
  public:
    Node(string);
    void setData(string);
    void setLeft(Node*);
    void setRight(Node*);
    void setCount(int);
    string getData() const;
    Node* getLeft() const;
    Node* getRight() const;
    int getCount() const;
};

#endif