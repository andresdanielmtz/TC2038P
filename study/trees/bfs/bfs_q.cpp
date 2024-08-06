#include <cstddef>
#include <iostream>
#include <queue>

class Node { 
public: 
  int key;  
  Node * left = NULL;
  Node * right = NULL;

  Node(int v) {
    key = v;
    left = NULL;
    right = NULL;
  }
};

Node * create_tree() { 
  Node * root = new Node(10); 
  root->left = new Node(11);
  root->right = new Node(12);
  root->left->left = new Node(13);
  root->left->right = new Node(14); 

  return root; 

}

void showq(std::queue<int> qg){ 
  while (!qg.empty()) { 
    std::cout << qg.front() << "\t"; 
    qg.pop(); 
  }
  std::cout << "\n";
}

int main() {
  std::queue<int> qdfs; 
  Node * tree = create_tree();

  return 0; 
}
