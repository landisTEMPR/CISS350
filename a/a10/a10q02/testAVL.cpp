/*************************
 *
 *  File : testAVL.cpp
 *  Author : Brysen Landis
 *
 *
 * ***********************/

#include <iostream>
#include <vector>
#include "AVL.h"

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

static int avl_ht(const BSTNode * x)
{
    if (x == NULL) return -1;
    int lh = avl_ht(x->left());
    int rh = avl_ht(x->right());
    return 1 + (lh > rh ? lh : rh);
}

bool check_avl(const BSTNode * n)
{
    if (n == NULL) return true;
    if (n->left()  && n->left()->key()  >= n->key()) return false;
    if (n->right() && n->right()->key() <= n->key()) return false;
    int b = avl_ht(n->right()) - avl_ht(n->left());
    if (b < -1 || b > 1) return false;
    return check_avl(n->left()) && check_avl(n->right());
}

int main()
{
    std::cout << "=== sequential insert (worst case for plain BST) ===\n";
    AVL avl;
    for (int i = 1; i <= 15; ++i)
    {
        avl.insert(i);
        std::cout << "inserted " << i
                  << "  height=" << avl.height()
                  << "  size="   << avl.size()
                  << "  balanced=" << check_avl(avl.root()) << '\n';
    }
    std::cout << "inorder: "; print_vec(avl.inorder()); std::cout << '\n';

    std::cout << "\n=== remove ===\n";
    avl.remove(1);
    std::cout << "remove 1: balanced=" << check_avl(avl.root())
              << "  "; print_vec(avl.inorder()); std::cout << '\n';

    avl.remove(8);
    std::cout << "remove 8: balanced=" << check_avl(avl.root())
              << "  "; print_vec(avl.inorder()); std::cout << '\n';

    avl.remove(15);
    std::cout << "remove 15: balanced=" << check_avl(avl.root())
              << "  "; print_vec(avl.inorder()); std::cout << '\n';

    std::cout << "\n=== duplicate insert ===\n";
    try
    {
        avl.insert(5);
    }
    catch (ValueError &)
    {
        std::cout << "ValueError caught on duplicate: pass\n";
    }

    std::cout << "\n=== remove missing ===\n";
    try
    {
        avl.remove(999);
    }
    catch (ValueError &)
    {
        std::cout << "ValueError caught on missing: pass\n";
    }

    std::cout << "\n=== copy constructor ===\n";
    AVL avl2(avl);
    print_vec(avl2.inorder()); std::cout << '\n';
    std::cout << "equal: " << (avl == avl2) << '\n';

    std::cout << "\n=== assignment ===\n";
    AVL avl3;
    avl3 = avl;
    print_vec(avl3.inorder()); std::cout << '\n';

    std::cout << "\n=== reverse insert ===\n";
    AVL avl4;
    for (int i = 20; i >= 1; --i) avl4.insert(i);
    std::cout << "height=" << avl4.height()
              << "  size=" << avl4.size()
              << "  balanced=" << check_avl(avl4.root()) << '\n';
    std::cout << "inorder: "; print_vec(avl4.inorder()); std::cout << '\n';

    std::cout << "\n=== min, max, find, select, range ===\n";
    std::cout << "min: " << avl4.min() << '\n';
    std::cout << "max: " << avl4.max() << '\n';
    std::cout << "find(10): " << avl4.find(10)->key() << '\n';
    std::cout << "select(4): " << avl4.select(4)->key() << " (expect 5)\n";
    std::cout << "range(5,11): "; print_vec(avl4.range(5, 11)); std::cout << '\n';

    return 0;
}
