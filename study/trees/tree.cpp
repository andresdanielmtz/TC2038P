#include <iostream>

class TreeNode {
public:
  int data;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int d) {
    data = d;
    left = NULL;
    right = NULL;
  }
};

/*

The main (and technically the only) difference between these traversals is the
order in which the std::cout is. Even though it's a somewhat trivial change, it
affects the entirety of the data we get.

*/

/*
INORDER Traversal

Left -> Root -> Right

Starts from the left-most root, then goes to the root and lastly to the right.
After this it goes to the root of the root and then to the right subtree.
*/

void inorderTraversal(TreeNode *root) {
  if (root == NULL) {
    return;
  }

  inorderTraversal(root->left);
  std::cout << root->data << std::endl;
  inorderTraversal(root->right);
}

/*
PREORDER Traversal

Root -> Left -> Right

Starts from the root, then goes to the left and then to the right. After this we get to the root to the root and so on and so forth.

This is usually the most used method (or the first that comes to mind) when talking about DFS since it goes to the bottom of said branch starting from the left, all the way to the right. 
*/

void preorderTraversal(TreeNode *root) {
  if (root == NULL) {
    return;
  }

  std::cout << root->data << std::endl;
  preorderTraversal(root->left);
  preorderTraversal(root->right);
}

/*
POSTORDER Traversal

Left -> Right -> Root

Starts from the left, goes to the right leaf and finally to the root. After this it does NOT go to the root but to the right-most element on the tree.

It's pretty weird. Used to delete trees since it goes to the leafs first before going to the roots of it. 
*/

void postorderTraversal(TreeNode *root) {
  if (root == NULL) {
    return;
  }

  postorderTraversal(root->left);
  postorderTraversal(root->right);

  std::cout << root->data << std::endl;
}

int main() {
  TreeNode *root = new TreeNode(10);
  root->left = new TreeNode(11);
  root->right = new TreeNode(12);
  root->left->left = new TreeNode(13);
  root->left->right = new TreeNode(14);
  root->right->left = new TreeNode(15);

  preorderTraversal(root);
  return 0;
}