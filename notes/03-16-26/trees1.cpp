#include <iostream>

/*
               10

          20         8

       4     30   2     12

            6  3 1  5      7
 */


class Node
{
public:
    Node(int key, Node * parent=NULL, Node * left=NULL, Node * right=NULL)
        : key_(key), parent_(parent), left_(left), right_(right)
    {}
    int key_;
    Node * left_;
    Node * right_;
    Node * parent_;
};

std::ostream & operator<<(std::ostream & cout, const Node & n)
{
    cout << "<Node " << &n << ' '
         << "key:" << n.key_ << ", "
         << "parent:" << n.parent_ << ", "
         << "left:" << n.left_ << ", "
         << "right:" << n.right_ << '>';
    return cout;
}


void preorder_DFT_print(Node * p)
{
    // empty/base case
    if (p == NULL)
    {
        std::cout << ' ';
    }
    // recursive case
    else
    {
        std::cout << p->key_ << ' ';
        preorder_DFT_print(p->left_);
        preorder_DFT_print(p->right_);
    }

    return;
}
    
int main()
{
    Node * p10 = new Node(10);
    Node * p20 = new Node(20, p10);
    p10->left_ = p20;
    Node * p8 = new Node(8, p10);
    p10->right_ = p8;

    Node * p4 = new Node(4, p20);
    p20->left_ = p4;
    Node * p30 = new Node(30, p20);
    p20->right_ = p30;

    Node * p2 = new Node(2, p8);
    p8->left_ = p2;
    Node * p12 = new Node(12, p8);
    p8->right_ = p12;
    
    Node * p6 = new Node(6, p30);
    p30->left_ = p6;
    Node * p3 = new Node(3, p30);
    p30->right_ = p3;
    
    Node * p1 = new Node(1, p2);
    p2->left_ = p1;
    Node * p5 = new Node(5, p2);
    p2->right_ = p5;

    Node * p7 = new Node(7, p12);
    p12->right_ = p7;
    
    std::cout << *p10 << '\n';
    std::cout << *p20 << '\n';
    std::cout << *p8 << '\n';
    std::cout << *p4 << '\n';
    std::cout << *p30 << '\n';
    std::cout << *p2 << '\n';
    std::cout << *p12 << '\n';
    std::cout << *p6 << '\n';
    std::cout << *p3 << '\n';
    std::cout << *p1 << '\n';
    std::cout << *p5 << '\n';
    std::cout << *p7 << '\n';

    /*
      traversals
      -- depth first traversals
         -- preorder DFT print = root, left, right
         -- inorder DFT print = left, root, right
         -- postorder DFT print = left, right, root
      -- breadth first traversal BFT     
     */
 
    preorder_DFT_print(p10);
    std::cout << std::endl;
    
    return 0;
}
