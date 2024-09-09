#include <algorithm>
#include <cmath>
#include <iostream>
#include <queue>
#include <random>
#include <unordered_map>
#include <vector>
#include <string>

using Matrix = std::vector<std::vector<int> >;

Matrix setup_matrix(int n) {
    Matrix matrix(n, std::vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            matrix[i][j] = n * i + j;
        }
    }
    matrix[n - 1][n - 1] = -1; // using -1 to represent 'v'
    return matrix;
}

// Heuristic function: calculates the Manhattan distance for the entire matrix
int heuristic(const Matrix &current, const Matrix &objective) {
    int distance = 0;
    int n = current.size();
    std::unordered_map<int, std::pair<int, int> > obj_positions;

    // Map objective matrix positions
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            obj_positions[objective[i][j]] = std::make_pair(i, j);
        }
    }

    // Calculate total Manhattan distance for current matrix
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (current[i][j] == -1)
                continue; // Skip 'v'
            auto [goal_x, goal_y] = obj_positions[current[i][j]];
            distance += std::abs(i - goal_x) + std::abs(j - goal_y);
        }
    }

    return distance;
}

std::vector<Matrix> get_matrix_variants(const Matrix &matrix) {
    std::vector<Matrix> variants;
    int n = matrix.size();
    std::pair<int, int> v_pos;

    // Find 'v' position
    for (int i = 0; i < n; ++i) {
        auto it = std::find(matrix[i].begin(), matrix[i].end(), -1);
        if (it != matrix[i].end()) {
            v_pos = {i, static_cast<int>(std::distance(matrix[i].begin(), it))};
            break;
        }
    }

    std::vector<std::pair<int, int> > directions = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    for (const auto &[dx, dy] : directions) {
        int new_x = v_pos.first + dx, new_y = v_pos.second + dy;
        if (new_x >= 0 && new_x < n && new_y >= 0 && new_y < n) {
            Matrix new_matrix = matrix;
            std::swap(new_matrix[v_pos.first][v_pos.second],
                      new_matrix[new_x][new_y]);
            variants.push_back(new_matrix);
        }
    }
    return variants;
}

// Custom comparator for priority queue
struct MatrixNode {
    Matrix matrix;
    int g_cost; // cost from start to current node
    int f_cost; // total estimated cost (g + h)

    bool operator>(const MatrixNode &other) const {
        return f_cost > other.f_cost;
    }
};

std::vector<Matrix> a_star(const Matrix &start, const Matrix &objective) {
    std::priority_queue<MatrixNode, std::vector<MatrixNode>, std::greater<> > open_set;
    std::unordered_map<std::string, int> g_cost_map; // Maps serialized matrix to g-cost
    std::unordered_map<std::string, Matrix> came_from; // Tracks path

    auto serialize = [](const Matrix &m) {
        std::string s;
        for (const auto &row : m) {
            for (int val : row)
                s += std::to_string(val) + ",";
        }
        return s;
    };

    open_set.push({start, 0, heuristic(start, objective)});
    g_cost_map[serialize(start)] = 0;

    while (!open_set.empty()) {
        MatrixNode current = open_set.top();
        open_set.pop();

        if (current.matrix == objective) {
            // Reconstruct path
            std::vector<Matrix> path;
            Matrix step = current.matrix;
            while (step != start) {
                path.push_back(step);
                step = came_from[serialize(step)];
            }
            path.push_back(start);
            std::reverse(path.begin(), path.end());
            return path;
        }

        for (const auto &neighbor : get_matrix_variants(current.matrix)) {
            int tentative_g_cost = current.g_cost + 1;
            std::string neighbor_key = serialize(neighbor);

            if (tentative_g_cost < g_cost_map[neighbor_key]) {
                g_cost_map[neighbor_key] = tentative_g_cost;
                int f_cost = tentative_g_cost + heuristic(neighbor, objective);
                open_set.push({neighbor, tentative_g_cost, f_cost});
                came_from[neighbor_key] = current.matrix;
            }
        }
    }

    return {}; // Return empty if no solution
}

void print_matrix(const Matrix &matrix) {
    for (const auto &row : matrix) {
        for (int val : row) {
            if (val == -1) {
                std::cout << "v ";
            } else {
                std::cout << val << " ";
            }
        }
        std::cout << std::endl;
    }
}

Matrix randomized_matrix(const Matrix &original) {
    Matrix random_matrix = original;
    int n = random_matrix.size();
    std::random_device rd;
    std::mt19937 g(rd());

    for (int i = 0; i < n * n; ++i) {
        int r1 = std::uniform_int_distribution<>(0, n - 1)(g);
        int c1 = std::uniform_int_distribution<>(0, n - 1)(g);
        int r2 = std::uniform_int_distribution<>(0, n - 1)(g);
        int c2 = std::uniform_int_distribution<>(0, n - 1)(g);
        std::swap(random_matrix[r1][c1], random_matrix[r2][c2]);
    }

    return random_matrix;
}

int main() {
    int n = 4; // Changed to 4 for faster execution
    Matrix matrix = setup_matrix(n);
    Matrix random_matrix = randomized_matrix(matrix);

    std::cout << "Objective Matrix:\n";
    print_matrix(matrix);
    std::cout << "\nCurrent Matrix:\n";
    print_matrix(random_matrix);
    std::cout << "\nPath used to get there:\n";

    auto path = a_star(random_matrix, matrix);

    for (const auto &step : path) {
        print_matrix(step);
        std::cout << "\n";
    }

    return 0;
}
