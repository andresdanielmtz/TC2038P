#include <cstddef>
#include <iostream>

class Node {
public:
  int key;
  Node *left;
  Node *right;
  Node(int v) { key = v; }
};

Node *create_tree() {
  Node *root = new Node(10);
  root->left = new Node(2);
  root->right = new Node(3);
  root->left->left = new Node(4);
  root->left->right = new Node(6);

  return root;
}

int main() {
  std::cout << ":D" << std::endl;
  Node *tree = create_tree();
  return 0;
}