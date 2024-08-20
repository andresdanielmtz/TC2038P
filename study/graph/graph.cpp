#include "Graph.h"
#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <utility>

Graph::Graph(int v) {
  numVertices = v;
  adjList.resize(v);
}

void Graph::printGraph() {
  for (int i = 0; i < numVertices; i++) {
    std::cout << "Adjacency list of vertex " << i << "\nhead";
    for (auto x : adjList[i]) {
      std::cout << " -> " << x;
    }
    std::cout << std::endl;
  }
}

void Graph::addEdge(int src, int dest) {
  if (src < numVertices && dest < numVertices) {
    adjList[src].push_back(dest);
  }
}

int Graph::getNumVertices() { return numVertices; }

void Graph::BFS(int start) {
  std::queue<int> q;
  std::vector<bool> visited(numVertices, false);

  q.push(start);
  visited[start] = true;

  while (!q.empty()) {
    int current = q.front();
    std::cout << current << " ";
    q.pop();

    for (int x : adjList[current]) {
      if (!visited[x]) {
        q.push(x);
        visited[x] = true;
      }
    }
  }
}

void Graph::DFS(int start) {
  std::stack<int> s;
  std::vector<bool> visited(numVertices, false);

  s.push(start);
  visited[start] = true;

  while (!s.empty()) {
    int current = s.top();
    std::cout << current << " ";
    s.pop();

    for (auto x : adjList[current]) {
      if (!visited[x]) {
        s.push(x);
        visited[x] = true;
      }
    }
  }
}

void Graph::deleteEdge(int src, int dest) {
  if (src > numVertices || dest > numVertices) {
    return;
  }

  for (auto it = adjList[src].begin(); it != adjList[src].end(); it++) {
    if (*it == dest) {
      adjList[src].erase(it);
      break;
    }
  }
}