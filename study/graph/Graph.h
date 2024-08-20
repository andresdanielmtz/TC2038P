#ifndef GRAPH_H
#define GRAPH_H

#include <utility>
#include <vector>

class Graph {
public:
  Graph(int v);
  void addEdge(int src, int dest);
  void printGraph();
  int getNumVertices();
  void BFS(int start);
  void DFS(int start);
  void deleteEdge(int src, int dest);

private:
  int numVertices;
  std::vector<std::vector<int> > adjList;
};

#endif