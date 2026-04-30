/*************************
 *
 *  File : BinarySearchTreeNode.cpp
 *  Author : Brysen Landis
 *
 *
 * ***********************/

#include <iostream>
#include "BinarySearchTreeNode.h"

std::ostream & operator<<(std::ostream & cout, const BSTNode & node)
{
    cout << "<Node: " << &node
         << ", key:"    << node.key()
         << ", parent:" << node.parent()
         << ", left:"   << node.left()
         << ", right:"  << node.right() << '>';
    return cout;
}

void print_inorder(const BSTNode * node)
{
    if (node == NULL) return;
    print_inorder(node->left());
    std::cout << (*node) << '\n';
    print_inorder(node->right());
}

bool insert(BSTNode * & node, int x)
{
    if (node == NULL)
    {
        node = new BSTNode(x);
        return true;
    }
    if (x == node->key()) return false;
    if (x < node->key())
    {
        bool ok = insert(node->left(), x);
        if (ok && node->left() != NULL)
            node->left()->parent() = node;
        return ok;
    }
    else
    {
        bool ok = insert(node->right(), x);
        if (ok && node->right() != NULL)
            node->right()->parent() = node;
        return ok;
    }
}

bool remove(BSTNode * & node, int x)
{
    if (node == NULL) return false;

    if (x < node->key())
    {
        bool ok = remove(node->left(), x);
        if (node->left() != NULL)
            node->left()->parent() = node;
        return ok;
    }
    else if (x > node->key())
    {
        bool ok = remove(node->right(), x);
        if (node->right() != NULL)
            node->right()->parent() = node;
        return ok;
    }
    else
    {
        if (node->left() == NULL && node->right() == NULL)
        {
            delete node;
            node = NULL;
        }
        else if (node->left() == NULL)
        {
            BSTNode * tmp = node;
            node = node->right();
            node->parent() = tmp->parent();
            delete tmp;
        }
        else if (node->right() == NULL)
        {
            BSTNode * tmp = node;
            node = node->left();
            node->parent() = tmp->parent();
            delete tmp;
        }
        else
        {
            BSTNode * successor = node->right()->leftmost();
            node->key() = successor->key();
            remove(node->right(), successor->key());
            if (node->right() != NULL)
                node->right()->parent() = node;
        }
        return true;
    }
}
