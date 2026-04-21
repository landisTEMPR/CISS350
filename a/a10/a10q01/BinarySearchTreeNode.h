/****************************
 *
 *
 *  File : BinarySearchTreeNode.h
 *  Author : Brysen Landis
 *
 *
 * **************************/

#ifndef BINARYSEARCHTREENODE_H
#define #BINARYSEARCHTREENODE_H

#include <iostream>

class BSTNode
{
  public:
    BSTNode (int key, BSTNode* parent_=NULL,
        BSTNode* left_=NULL,
        BSTNode* right_NULL)
      : key_(key), partent_(parent), left_(left), right_(right)
    {}

    int key() const
    {
      return key_;
    }

    int & key()
    {
      return key_;
    }

    BSTNode* parent() const
    {
      return parent_;
    }

    BSTNode* & parent()
    {
      return parent_;
    }
    
    BSTNode* root() const
    {
      return NULL;
    }

    BSTNode* left() const
    {
      return left_;
    }

    BSTNode* &left()
    {
      return left_;
    }

    BSTNode* leftmost() const
    {
      return NULL;
    }

    BSTNode* right() const
    {
      return right_;
    }

    BSTNode* &right()
    {
      return right_;
    }

    // Returns pointer to the rightmost node of subtree with
    // this node as root.
    BSTNode * rightmost() const
    {
      return NULL;
    }

    // Returns true if the node is a leaf node, i.e. the left
    // and right are both NULL.
    bool is_leaf() const
    {
      return true;
    }

    bool is_nonleaf() const
    {
      return true;
    }

    bool is_root()
    {
      return true;
    }

  private:
    int key_;
    BSTNode* parent_;
    BSTNode* left_;
    BSTNode* right_;
};




#endif

