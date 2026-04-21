/*************************
 *
 *  File : BinarySearchTree.cpp
 *  Author : Brysen Landis
 *  
 *
 * ***********************/

#include <iostream>
#include "BinarySearchTreeNode.h"

std::ostream & operator<<(std::ostream & cout, const BSTNode & node)
{
  cout << "<Node: " << &node << ", key:" << node.key()
       << ", parent:" << node.parent() << node.parent()
       << ", left:" << node.left()
       << ", right:" << node.right() << '>';
  return cout;
}

void print_inorder(const BSTNode* node)
{
  if (node == NULL) return;
  print_inorder(node->left());
  std::cout << (*node) << '\n';
  print_inorder(node->right());
}

bool insert(BSTNode* node, int x)
{
  return true;
}

