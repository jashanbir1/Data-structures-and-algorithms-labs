#ifndef __TREE_H
#define __TREE_H

#include "Node.h"

class Tree {
private:
  Node *root;

public:
  Tree( );
  ~Tree( );
  void insert(const string &);
  void preOrder( ) const;
  void inOrder( ) const;
  void postOrder( ) const;
  void remove(const string &);
  bool search (const string &) const;

private:
  // Add additional functions/variables here
  void recurDestructor(Node* );
  void recurPreOrder(Node* ) const;
  void recurInOrder(Node* ) const;
  void recurPostOrder(Node* ) const;
  void recurInsert(Node*, const string& );
  void recurRemove(const string&, Node* );
  bool recurSearch(Node* , const string& ) const;
  Node* nodeSearch(Node*, const string& );
  void split(Node* , const string &);

};

#endif