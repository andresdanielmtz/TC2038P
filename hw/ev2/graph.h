#pragma once
#include <iostream>
#include <vector>

class Graph {
  std::vector<std::vector<int> > adj_matrix;

public:
  void add_edge(int u, int v);
  void print();
};
