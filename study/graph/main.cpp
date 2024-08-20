#include "Graph.h"
#include <iostream>

int main() {
  Graph graph(5);
  graph.addEdge(0, 1);
  graph.addEdge(0, 2);
  graph.addEdge(1, 2);
  graph.addEdge(1, 3);
  graph.addEdge(2, 3);
  graph.addEdge(3, 4);
  graph.printGraph();
  graph.BFS(0);
  std::cout << std::endl;
  graph.DFS(0);
  return 0;
}
