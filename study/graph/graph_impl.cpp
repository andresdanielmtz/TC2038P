#include <iostream>
#include <queue>

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



void bfs_tree(Node * root) {
  std::queue<Node *> q;
  if (root) { 
    q.push(root); 
    std::cout << root->key << " "; 
  }
  else { 
    std::cout << "NULL" << std::endl; 
  }

  while (!q.empty()) {
    Node * temp_node = q.front();
    q.pop(); 

    if (temp_node->left) { 
      q.push(temp_node->left); 
      std::cout << temp_node->left->key << " "; 
    }
    else { 
      std::cout << "NULL "; 
    }

    
    if (temp_node->right) { 
      q.push(temp_node->right); 
      std::cout << temp_node->right->key << " "; 
    }
    else { 
      std::cout << "NULL "; 
    }
  }
}  


void dfs_tree(Node * root) { 
  if (root == NULL) {
    return; 
  }
  std::cout << root->key << " "; 
  dfs_tree(root->left); 
  dfs_tree(root->right); 
}

int main() {
  std::cout << ":D" << std::endl;
  Node *tree = create_tree();
  bfs_tree(tree); 
  return 0;
}
