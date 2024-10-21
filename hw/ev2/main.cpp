#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <vector>
#include <unordered_set>

const int INF = std::numeric_limits<int>::max();

void addEdge(std::vector<std::vector<int> > &graph, int u, int v, int wt) {
    graph[u][v] = wt;
    graph[v][u] = wt;
}

std::vector<std::pair<int, int> > primMST(const std::vector<std::vector<int> > &graph) {
    int V = graph.size();
    int costMSTPrim = 0;
    std::unordered_set<int> selected;
    std::unordered_set<int> missing;
    std::vector<std::pair<int, int> > selectedEdgesP;

    selected.insert(0); // Start with vertex 0
    for (int i = 1; i < V; i++) {
        missing.insert(i);
    }

    int connected = V - 1;
    while (connected) {
        int minCost = INF;
        int selVertex = -1;
        int selSource = -1;

        for (int source : selected) {
            for (int dest = 0; dest < V; dest++) {
                if (missing.find(dest) != missing.end() && graph[source][dest] < minCost) {
                    minCost = graph[source][dest];
                    selVertex = dest;
                    selSource = source;
                }
            }
        }

        costMSTPrim += minCost;
        selected.insert(selVertex);
        missing.erase(selVertex);
        selectedEdgesP.push_back(std::make_pair(selSource, selVertex));
        connected--;
    }

    std::cout << "MST cost: " << costMSTPrim << " km" << std::endl;
    return selectedEdgesP;
}

std::vector<int> traveling_salesman(const std::vector<std::vector<int> > &graph) {
    int n = graph.size();
    std::vector<int> tour;
    std::vector<bool> visited(n, false);
    tour.push_back(0); // Start from the first city
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

int calculate_tour_length(const std::vector<int> &tour, const std::vector<std::vector<int> > &graph) {
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
    std::vector<std::vector<int> > graph(V, std::vector<int>(V, INF));

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            int weight;
            input_file >> weight;
            if (weight != 0) {
                addEdge(graph, i, j, weight);
            }
        }
        graph[i][i] = 0;
    }
    input_file.close();

    // Problem 1: Minimum Spanning Tree (Prim's Algorithm)
    std::cout << "Problem 1: Optimal way to cable the colonies (MST method)" << std::endl;
    std::vector<std::pair<int, int> > mst = primMST(graph);
    for (const auto &edge : mst) {
        std::cout << "(" << edge.first << "," << edge.second << ") ";
    }
    std::cout << std::endl;

    // Problem 2: Traveling Salesman Problem
    std::vector<int> tour = traveling_salesman(graph);
    int tour_length = calculate_tour_length(tour, graph);

    std::cout << "\nProblem 2: Shortest path that goes through every node (TSP method)" << std::endl;
    for (int city : tour) {
        std::cout << static_cast<char>('A' + city) << " ";
    }
    std::cout << "\nTotal cable length: " << tour_length << " km" << std::endl;

    return 0;
}