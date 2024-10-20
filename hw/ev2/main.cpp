#include <iostream>
#include <utility>
#include <vector>


void addEdge(std::vector<std::pair<int, int> > adj[], int u, int v, int wt) {
  for (const auto &edge : adj[u]) {
    if (edge.first == v && edge.second == wt) {
      return; // If edge already exists, don't add it again : )
    }
  }
  adj[u].push_back(std::make_pair(v, wt));
  adj[v].push_back(std::make_pair(u, wt));
}

/**
 * @brief https://www.geeksforgeeks.org/floyd-warshall-algorithm-dp-16/
 * 
 * @param V 
 * @return std::vector<std::vector<int> > 
 */

std::vector<std::vector<int> > floyd_warshall(std::vector<std::pair<int, int> >adj[], int V) {
    std::vector<std::vector<int> > dist(V, std::vector<int>(V, INT_MAX));

    for (int i = 0; i < V; i++) {
        dist[i][i] = 0; // Distance from a vertex to itself is 0
        for (const auto& edge : adj[i]) {
            int j = edge.first;
            int weight = edge.second;
            dist[i][j] = weight;
        }
    }

    // Floyd-Warshall algorithm
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX &&
                    dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    return dist;
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


  std::vector<std::vector<int> > dist = floyd_warshall(adj, V);
  for (int i = 0; i < V; i++) {
      for (int j = 0; j < V; j++) {
          if (dist[i][j] == INT_MAX) {
              std::cout << "INF ";
          } else {
              std::cout << dist[i][j] << " ";
          }
      }
      std::cout << "\n";
  }

  return 0;
}