#include <iostream> 

struct node {
  int data;
  struct node *left;
  struct node *right;
  node(int d) {
    data = d;
    left = NULL;
    right = NULL;
  }
};

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