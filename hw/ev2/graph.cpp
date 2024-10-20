#include <iostream>
#include <vector>
#include "graph.h"

void Graph::add_edge(int u, int v) { 
    adj_matrix[u][v] = 1;
    adj_matrix[v][u] = 1;
}

void Graph::print() {
    for (int i = 0; i < adj_matrix.size(); i++) {
        std::cout << i << ": ";
        for (int j = 0; j < adj_matrix[i].size(); j++) {
            if (adj_matrix[i][j] == 1) {
                std::cout << j << " ";
            }
        }
        std::cout << std::endl;
    }
}