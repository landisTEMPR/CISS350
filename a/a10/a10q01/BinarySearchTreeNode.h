/****************************
 *
 *
 *  File : BinarySearchTreeNode.h
 *  Author : Brysen Landis
 *
 *
 * **************************/

#ifndef BINARYSEARCHTREENODE_H
#define BINARYSEARCHTREENODE_H

#include <iostream>

class BSTNode
{
public:
    BSTNode(int key, BSTNode * parent_ = NULL,
            BSTNode * left_ = NULL,
            BSTNode * right_ = NULL)
        : key_(key), parent_(parent_), left_(left_), right_(right_)
    {}

    int key() const  { return key_; }
    int & key()      { return key_; }

    BSTNode * parent() const    { return parent_; }
    BSTNode * & parent()        { return parent_; }

    BSTNode * left() const      { return left_; }
    BSTNode * & left()          { return left_; }

    BSTNode * right() const     { return right_; }
    BSTNode * & right()         { return right_; }

    BSTNode * root() const
    {
        const BSTNode * p = this;
        while (p->parent_ != NULL) p = p->parent_;
        return const_cast< BSTNode * >(p);
    }

    BSTNode * leftmost() const
    {
        const BSTNode * p = this;
        while (p->left_ != NULL) p = p->left_;
        return const_cast< BSTNode * >(p);
    }

    BSTNode * rightmost() const
    {
        const BSTNode * p = this;
        while (p->right_ != NULL) p = p->right_;
        return const_cast< BSTNode * >(p);
    }

    bool is_leaf()    const { return left_ == NULL && right_ == NULL; }
    bool is_nonleaf() const { return !is_leaf(); }
    bool is_root()    const { return parent_ == NULL; }

private:
    int key_;
    BSTNode * parent_;
    BSTNode * left_;
    BSTNode * right_;
};

std::ostream & operator<<(std::ostream &, const BSTNode &);
void print_inorder(const BSTNode *);
bool insert(BSTNode * &, int);
bool remove(BSTNode * &, int);

#endif
