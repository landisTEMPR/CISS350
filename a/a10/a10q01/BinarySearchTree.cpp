/*************************
 *
 *  File : BinarySearchTree.cpp
 *  Author : Brysen Landis
 *
 *
 * ***********************/

#include "BinarySearchTree.h"

void print_inorder(const BST & bst)
{
    print_inorder(bst.root());
}

void print_preorder(const BST & bst)
{
    std::vector< int > v = bst.preorder();
    for (int i = 0; i < (int)v.size(); ++i)
    {
        if (i > 0) std::cout << ' ';
        std::cout << v[i];
    }
    std::cout << '\n';
}

void print_postorder(const BST & bst)
{
    std::vector< int > v = bst.postorder();
    for (int i = 0; i < (int)v.size(); ++i)
    {
        if (i > 0) std::cout << ' ';
        std::cout << v[i];
    }
    std::cout << '\n';
}
