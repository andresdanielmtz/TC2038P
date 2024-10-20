#include <iostream>
#include <utility>
#include <vector>
void addEdge(std::vector<std::pair<int, int> > adj[], int u, int v, int wt) {
  for (const auto& edge : adj[u]) {
    if (edge.first == v && edge.second == wt) {
      return; // Edge already exists, do not add it again
    }
  }
  adj[u].push_back(std::make_pair(v, wt));
  adj[v].push_back(std::make_pair(u, wt));
}

void printGraph(std::vector<std::pair<int, int> > adj[], int V) {
  int v, w;
  for (int u = 0; u < V; u++) {
    std::cout << u << "\n"; 
    for (auto it = adj[u].begin(); it != adj[u].end(); it++) {
      v = it->first;
      w = it->second;
      std::cout << v << ", w: \t" << w << "\n";
    }
    std::cout << "\n";
  }
}

int main() {
  int V;
  std::cin >> V;
  std::vector<std::pair<int, int> > adj[V];

  // Input parsing for adjacency matrix, through stdin (standard input)

  for (int i = 0; i < V; ++i) {
    for (int j = 0; j < V; ++j) {
      int wt;
      std::cin >> wt;
      if (wt != 0) {
        addEdge(adj, i, j, wt);
      }
    }
  }
  

  printGraph(adj, V);
  return 0;
}