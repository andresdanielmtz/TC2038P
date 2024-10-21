#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <fstream>

const int INF = std::numeric_limits<int>::max();

void addEdge(std::vector<std::vector<int>>& graph, int u, int v, int wt) {
    graph[u][v] = wt;
    graph[v][u] = wt;
}

std::vector<std::vector<int>> floyd_warshall(const std::vector<std::vector<int>>& graph) {
    int V = graph.size();
    std::vector<std::vector<int>> dist = graph;

    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF &&
                    dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
    return dist;
}

/**
 * @brief This function solves the Traveling Salesman Problem using a greedy algorithm. It uses the nearest neighbor heuristic to find an approximate solution.
 * 
 * @param graph 
 * @return std::vector<int> 
 */
std::vector<int> traveling_salesman(const std::vector<std::vector<int>>& graph) {
    int n = graph.size();
    std::vector<int> tour;
    std::vector<bool> visited(n, false);
    
    tour.push_back(0);  // Start from the first city
    visited[0] = true;

    for (int i = 1; i < n; i++) {
        int last = tour.back();
        int next = -1;
        int min_dist = INF;

        for (int j = 0; j < n; j++) {
            if (!visited[j] && graph[last][j] != INF && graph[last][j] < min_dist) {
                next = j;
                min_dist = graph[last][j];
            }
        }

        if (next == -1) {

            break;
        }

        tour.push_back(next);
        visited[next] = true;
    }
    tour.push_back(0);

    return tour;
}

int calculate_tour_length(const std::vector<int>& tour, const std::vector<std::vector<int>>& graph) {
    int length = 0;
    for (size_t i = 0; i < tour.size() - 1; i++) {
        length += graph[tour[i]][tour[i + 1]];
    }
    return length;
}

int main() {
    std::ifstream input_file("in.txt");
    if (!input_file.is_open()) {
        std::cerr << "Error opening input file" << std::endl;
        return 1;
    }

    int V;
    input_file >> V;

    std::vector<std::vector<int>> graph(V, std::vector<int>(V, INF));

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            int weight;
            input_file >> weight;
            if (weight != 0) {
                addEdge(graph, i, j, weight);
            }
        }
        graph[i][i] = 0;  // Distance to self is 0
    }

    input_file.close();

    // Traveling Salesman Problem
    std::vector<int> tour = traveling_salesman(graph);
    int tour_length = calculate_tour_length(tour, graph);

    std::cout << "\nOptimal cabling route (TSP solution):" << std::endl;
    for (int city : tour) {
        std::cout << city << " ";
    }
    std::cout << "\nTotal cable length: " << tour_length << " km" << std::endl;

    return 0;
}