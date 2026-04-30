/****************************
 *
 *
 *  File : AVL.h
 *  Author : Brysen Landis
 *
 *
 * **************************/

#ifndef AVL_H
#define AVL_H

#include "BinarySearchTree.h"

class AVL : public BST
{
public:
    AVL() : BST() {}

    AVL(int x[], int size) : BST()
    {
        for (int i = 0; i < size; ++i) insert(x[i]);
    }

    AVL(const AVL & other) : BST(other) {}

    AVL & operator=(const AVL & other)
    {
        BST::operator=(other);
        return *this;
    }

    void insert(int x)
    {
        bool ok = ::insert(root_, x);
        if (!ok) throw ValueError();
        if (root_ != NULL) root_->parent() = NULL;
        rebalance_up(find(x));
        if (root_ != NULL) root_->parent() = NULL;
    }

    void remove(int x)
    {
        BSTNode * p = find(x);
        if (p == NULL) throw ValueError();
        BSTNode * start = p->parent();

        bool ok = ::remove(root_, x);
        if (!ok) throw ValueError();
        if (root_ != NULL) root_->parent() = NULL;

        rebalance_up(start);
        if (root_ != NULL) root_->parent() = NULL;
    }

private:
    static int ht(const BSTNode * n)
    {
        if (n == NULL) return -1;
        int lh = ht(n->left());
        int rh = ht(n->right());
        return 1 + (lh > rh ? lh : rh);
    }

    static int bf(const BSTNode * n)
    {
        if (n == NULL) return 0;
        return ht(n->right()) - ht(n->left());
    }

    BSTNode * rotate_right(BSTNode * y)
    {
        BSTNode * x  = y->left();
        BSTNode * B  = x->right();
        BSTNode * yp = y->parent();

        x->right() = y;
        y->left()  = B;

        y->parent() = x;
        if (B != NULL) B->parent() = y;
        x->parent() = yp;

        if (yp == NULL)           root_ = x;
        else if (yp->left() == y) yp->left() = x;
        else                      yp->right() = x;

        return x;
    }

    BSTNode * rotate_left(BSTNode * x)
    {
        BSTNode * y  = x->right();
        BSTNode * B  = y->left();
        BSTNode * xp = x->parent();

        y->left()  = x;
        x->right() = B;

        x->parent() = y;
        if (B != NULL) B->parent() = x;
        y->parent() = xp;

        if (xp == NULL)           root_ = y;
        else if (xp->left() == x) xp->left() = y;
        else                      xp->right() = y;

        return y;
    }

    BSTNode * fix(BSTNode * n)
    {
        int b = bf(n);
        if (b == -2)
        {
            if (bf(n->left()) <= 0)
                return rotate_right(n);
            else
            {
                rotate_left(n->left());
                return rotate_right(n);
            }
        }
        else if (b == 2)
        {
            if (bf(n->right()) >= 0)
                return rotate_left(n);
            else
            {
                rotate_right(n->right());
                return rotate_left(n);
            }
        }
        return n;
    }

    void rebalance_up(BSTNode * p)
    {
        while (p != NULL)
        {
            BSTNode * parent = p->parent();
            fix(p);
            p = parent;
        }
    }
};

#endif
