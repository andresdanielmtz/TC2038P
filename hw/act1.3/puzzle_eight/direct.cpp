#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <unordered_set>

using namespace std;

typedef vector<vector<int>> Matrix;

Matrix setup_matrix(int n) {
    Matrix matrix(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = n * i + j;
        }
    }
    matrix[n-1][n-1] = -1; // -1 represents "v"
    return matrix;
}

void print_matrix(const Matrix& matrix) {
    for (const auto& row : matrix) {
        for (int val : row) {
            if (val == -1) cout << "v ";
            else cout << val << " ";
        }
        cout << endl;
    }
}

int compare_matrix(const Matrix& m, const Matrix& n) {
    if (m.size() != n.size()) {
        cout << "Please output a correct list" << endl;
        return 0;
    }
    int counter = 0;
    for (size_t i = 0; i < n.size(); i++) {
        for (size_t j = 0; j < n[i].size(); j++) {
            if (n[i][j] == m[i][j]) {
                counter++;
            }
        }
    }
    return counter;
}

Matrix randomized_matrix(const Matrix& matrix) {
    int n = matrix.size();
    vector<int> flat_matrix;
    for (const auto& row : matrix) {
        for (int val : row) {
            if (val != -1) flat_matrix.push_back(val);
        }
    }
    
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(flat_matrix.begin(), flat_matrix.end(), default_random_engine(seed));

    Matrix new_matrix(n, vector<int>(n));
    int index = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == n - 1 && j == n - 1) {
                new_matrix[i][j] = -1;
            } else {
                new_matrix[i][j] = flat_matrix[index++];
            }
        }
    }
    return new_matrix;
}

vector<Matrix> get_matrix_variants(const Matrix& matrix) {
    vector<Matrix> variants;
    int n = matrix.size();
    
    pair<int, int> v_pos;
    for (int i = 0; i < n; i++) {
        auto it = find(matrix[i].begin(), matrix[i].end(), -1);
        if (it != matrix[i].end()) {
            v_pos = {i, static_cast<int>(it - matrix[i].begin())};
            break;
        }
    }
    
    vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    
    for (const auto& [dx, dy] : directions) {
        int new_x = v_pos.first + dx;
        int new_y = v_pos.second + dy;
        if (0 <= new_x && new_x < n && 0 <= new_y && new_y < n) {
            Matrix new_matrix = matrix;
            swap(new_matrix[v_pos.first][v_pos.second], new_matrix[new_x][new_y]);
            variants.push_back(new_matrix);
        }
    }
    return variants;
}

vector<Matrix> backtracking(const Matrix& objective, Matrix matrix, int max_steps = 30000) {
    Matrix current_matrix = matrix;
    vector<Matrix> combination_path;
    int steps = 0;
    unordered_set<string> visited;

    auto matrix_to_string = [](const Matrix& m) {
        string s;
        for (const auto& row : m) {
            for (int val : row) {
                s += to_string(val) + ",";
            }
        }
        return s;
    };

    while (current_matrix != objective && steps < max_steps) {
        string matrix_str = matrix_to_string(current_matrix);
        if (visited.find(matrix_str) != visited.end()) {
            // Instead of returning empty, let's try a random move
            auto combinations = get_matrix_variants(current_matrix);
            if (combinations.empty()) return {};
            current_matrix = combinations[rand() % combinations.size()];
            continue;
        }
        visited.insert(matrix_str);

        auto combinations = get_matrix_variants(current_matrix);
        if (combinations.empty()) return {};

        auto best_combination = *max_element(combinations.begin(), combinations.end(),
            [&objective](const Matrix& a, const Matrix& b) {
                return compare_matrix(a, objective) < compare_matrix(b, objective);
            });
        
        if (compare_matrix(best_combination, objective) <= compare_matrix(current_matrix, objective)) {
            // If we're not improving, try a random move
            best_combination = combinations[rand() % combinations.size()];
        }

        cout << "Step " << steps + 1 << ":" << endl;
        print_matrix(best_combination);
        cout << endl;

        current_matrix = best_combination;
        combination_path.push_back(current_matrix);
        steps++;
    }

    return (current_matrix == objective) ? combination_path : vector<Matrix>{};
}

int main() {
    int n = 3; // You can change this to any size you want
    auto matrix = setup_matrix(n);
    auto random_matrix = randomized_matrix(matrix);

    cout << "Objective Matrix:" << endl;
    print_matrix(matrix);
    cout << endl;

    cout << "Initial Matrix:" << endl;
    print_matrix(random_matrix);
    cout << endl;

    cout << "Backtracking Path:" << endl;
    auto backtracking_path = backtracking(matrix, random_matrix);
    if (!backtracking_path.empty()) {
        cout << "Solution found in " << backtracking_path.size() << " moves." << endl;
    } else {
        cout << "No solution found with backtracking." << endl;
    }

    return 0;
}