/*************************
 *
 *  File : test.cpp
 *  Author : Brysen Landis
 *
 *
 * ***********************/

#include <iostream>
#include <vector>
#include "BinarySearchTreeNode.h"
#include "BinarySearchTree.h"

void print_vec(const std::vector< int > & v)
{
    std::cout << '[';
    for (int i = 0; i < (int)v.size(); ++i)
    {
        if (i > 0) std::cout << ", ";
        std::cout << v[i];
    }
    std::cout << ']';
}

int main()
{
    std::cout << "testing BinarySearchTreeNode ...\n";
    BSTNode * n = new BSTNode(5);
    print_inorder(n); std::cout << "\n\n";

    insert(n, 3); print_inorder(n); std::cout << "\n\n";
    insert(n, 0); print_inorder(n); std::cout << "\n\n";
    insert(n, 1); print_inorder(n); std::cout << "\n\n";
    insert(n, 4); print_inorder(n); std::cout << "\n\n";
    insert(n, 8); print_inorder(n); std::cout << '\n';

    std::cout << "testing BinarySearchTree ...\n";
    BST bst;
    print_inorder(bst); std::cout << '\n';

    bst.insert(5);  print_inorder(bst); std::cout << '\n';
    bst.insert(0);  print_inorder(bst); std::cout << '\n';
    bst.insert(2);  print_inorder(bst); std::cout << '\n';
    bst.insert(-2); print_inorder(bst); std::cout << '\n';
    bst.insert(10); print_inorder(bst); std::cout << '\n';
    bst.insert(8);  print_inorder(bst); std::cout << '\n';
    bst.insert(9);  print_inorder(bst); std::cout << '\n';
    bst.insert(7);  print_inorder(bst); std::cout << '\n';

    try
    {
        std::cout << "testing duplicate insert ... ";
        bst.insert(7);
    }
    catch (ValueError &)
    {
        std::cout << "pass\n";
    }

    std::cout << "\ntraversals:\n";
    std::cout << "inorder:      "; print_vec(bst.inorder());      std::cout << '\n';
    std::cout << "preorder:     "; print_vec(bst.preorder());     std::cout << '\n';
    std::cout << "postorder:    "; print_vec(bst.postorder());    std::cout << '\n';
    std::cout << "breadthfirst: "; print_vec(bst.breadthfirst()); std::cout << '\n';

    std::cout << "\nsize:   " << bst.size()   << '\n';
    std::cout << "height: " << bst.height() << '\n';
    std::cout << "min:    " << bst.min()    << '\n';
    std::cout << "max:    " << bst.max()    << '\n';

    std::cout << "\nfind(8):  " << bst.find(8)->key()         << '\n';
    std::cout << "find(99): " << (bst.find(99) ? "found" : "NULL") << '\n';

    std::cout << "\nselect(0): " << bst.select(0)->key() << " (expect -2)\n";
    std::cout << "select(4): " << bst.select(4)->key() << " (expect 7)\n";

    std::cout << "\nrange(0,9): "; print_vec(bst.range(0, 9)); std::cout << '\n';

    std::cout << "\nremove tests:\n";
    bst.remove(9);  print_vec(bst.inorder()); std::cout << '\n';
    bst.remove(0);  print_vec(bst.inorder()); std::cout << '\n';
    bst.remove(8);  print_vec(bst.inorder()); std::cout << '\n';
    bst.remove(5);  print_vec(bst.inorder()); std::cout << '\n';

    try
    {
        std::cout << "remove missing ... ";
        bst.remove(999);
    }
    catch (ValueError &)
    {
        std::cout << "pass\n";
    }

    std::cout << "\ncopy constructor:\n";
    BST bst2(bst);
    print_vec(bst2.inorder()); std::cout << '\n';
    std::cout << "equal: " << (bst == bst2) << '\n';

    std::cout << "\nassignment:\n";
    BST bst3;
    bst3 = bst;
    print_vec(bst3.inorder()); std::cout << '\n';

    std::cout << "\nclear:\n";
    bst3.clear();
    std::cout << "is_empty: " << bst3.is_empty() << '\n';

    std::cout << "\ndepth:\n";
    BST bst4;
    bst4.insert(5); bst4.insert(3); bst4.insert(7); bst4.insert(1);
    std::cout << "depth(5): " << bst4.depth(bst4.find(5)) << '\n';
    std::cout << "depth(3): " << bst4.depth(bst4.find(3)) << '\n';
    std::cout << "depth(1): " << bst4.depth(bst4.find(1)) << '\n';

    return 0;
}
