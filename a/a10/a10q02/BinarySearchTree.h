/****************************
 *
 *
 *  File : BinarySearchTree.h
 *  Author : Brysen Landis
 *
 *
 * **************************/

#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <vector>
#include <queue>
#include "BinarySearchTreeNode.h"

class ValueError {};

class BST
{
public:
    BST()
        : root_(NULL)
    {}

    BST(int x[], int size)
        : root_(NULL)
    {
        for (int i = 0; i < size; ++i) insert(x[i]);
    }

    BST(const BST & bst)
        : root_(NULL)
    {
        copy_from(bst.root_, NULL, root_);
    }

    ~BST()
    {
        clear();
    }

    BST & operator=(const BST & bst)
    {
        if (this != &bst)
        {
            clear();
            copy_from(bst.root_, NULL, root_);
        }
        return *this;
    }

    BSTNode * root()     const { return root_; }
    BSTNode * get_root() const { return root_; }

    void clear()
    {
        destroy(root_);
        root_ = NULL;
    }

    bool is_empty() const { return root_ == NULL; }

    int height() const { return height(root_); }

    int depth(BSTNode * p) const
    {
        int d = 0;
        while (p != NULL && p->parent() != NULL)
        {
            p = p->parent();
            ++d;
        }
        return d;
    }

    int size() const { return size(root_); }

    BSTNode * find(int x) const
    {
        BSTNode * p = root_;
        while (p != NULL)
        {
            if      (x == p->key()) return p;
            else if (x <  p->key()) p = p->left();
            else                    p = p->right();
        }
        return NULL;
    }

    int min() const
    {
        if (is_empty()) throw ValueError();
        return root_->leftmost()->key();
    }

    int max() const
    {
        if (is_empty()) throw ValueError();
        return root_->rightmost()->key();
    }

    bool operator==(const BST & t) const
    {
        return equal(root_, t.root_);
    }

    bool operator!=(const BST & t) const
    {
        return !(*this == t);
    }

    void insert(int x)
    {
        bool ok = ::insert(root_, x);
        if (!ok) throw ValueError();
        if (root_ != NULL) root_->parent() = NULL;
    }

    void remove(int x)
    {
        bool ok = ::remove(root_, x);
        if (!ok) throw ValueError();
        if (root_ != NULL) root_->parent() = NULL;
    }

    std::vector< int > inorder() const
    {
        std::vector< int > ret;
        inorder(root_, ret);
        return ret;
    }

    std::vector< int > preorder() const
    {
        std::vector< int > ret;
        preorder(root_, ret);
        return ret;
    }

    std::vector< int > postorder() const
    {
        std::vector< int > ret;
        postorder(root_, ret);
        return ret;
    }

    std::vector< int > breadthfirst() const
    {
        std::vector< int > ret;
        if (root_ == NULL) return ret;
        std::queue< BSTNode * > q;
        q.push(root_);
        while (!q.empty())
        {
            BSTNode * p = q.front(); q.pop();
            ret.push_back(p->key());
            if (p->left()  != NULL) q.push(p->left());
            if (p->right() != NULL) q.push(p->right());
        }
        return ret;
    }

    BSTNode * select(int k) const
    {
        std::vector< int > v = inorder();
        if (k < 0 || k >= (int)v.size()) return NULL;
        return find(v[k]);
    }

    std::vector< int > range(int m, int M) const
    {
        std::vector< int > ret;
        range(root_, m, M, ret);
        return ret;
    }

protected:
    BSTNode * root_;

    static void destroy(BSTNode * node)
    {
        if (node == NULL) return;
        destroy(node->left());
        destroy(node->right());
        delete node;
    }

    static void copy_from(BSTNode * src, BSTNode * parent, BSTNode * & dst)
    {
        if (src == NULL) { dst = NULL; return; }
        dst = new BSTNode(src->key(), parent);
        copy_from(src->left(),  dst, dst->left());
        copy_from(src->right(), dst, dst->right());
    }

    static int height(const BSTNode * node)
    {
        if (node == NULL) return -1;
        int lh = height(node->left());
        int rh = height(node->right());
        return 1 + (lh > rh ? lh : rh);
    }

    static int size(const BSTNode * node)
    {
        if (node == NULL) return 0;
        return 1 + size(node->left()) + size(node->right());
    }

    static bool equal(const BSTNode * a, const BSTNode * b)
    {
        if (a == NULL && b == NULL) return true;
        if (a == NULL || b == NULL) return false;
        return a->key() == b->key() &&
               equal(a->left(),  b->left()) &&
               equal(a->right(), b->right());
    }

    static void inorder(const BSTNode * node, std::vector< int > & v)
    {
        if (node == NULL) return;
        inorder(node->left(), v);
        v.push_back(node->key());
        inorder(node->right(), v);
    }

    static void preorder(const BSTNode * node, std::vector< int > & v)
    {
        if (node == NULL) return;
        v.push_back(node->key());
        preorder(node->left(), v);
        preorder(node->right(), v);
    }

    static void postorder(const BSTNode * node, std::vector< int > & v)
    {
        if (node == NULL) return;
        postorder(node->left(), v);
        postorder(node->right(), v);
        v.push_back(node->key());
    }

    static void range(const BSTNode * node, int m, int M, std::vector< int > & v)
    {
        if (node == NULL) return;
        if (node->key() > m) range(node->left(),  m, M, v);
        if (node->key() >= m && node->key() < M) v.push_back(node->key());
        if (node->key() < M) range(node->right(), m, M, v);
    }
};

void print_inorder(const BST & bst);
void print_preorder(const BST & bst);
void print_postorder(const BST & bst);

#endif
