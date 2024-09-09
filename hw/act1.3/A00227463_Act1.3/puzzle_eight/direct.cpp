#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>

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

Matrix randomized_matrix(Matrix matrix) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 50); // limits 
    
    for (int i = 0; i < dis(gen); i++) {
        auto combination_list = get_matrix_variants(matrix);
        if (combination_list.empty()) return matrix;
        matrix = combination_list[dis(gen) % combination_list.size()];
    }
    return matrix;
}

vector<Matrix> backtracking(const Matrix& objective, Matrix matrix) {
    Matrix current_matrix = matrix;
    vector<Matrix> combination_path;
    int max_steps = 10000;
    while (current_matrix != objective) {
        max_steps--;
        if (max_steps == 0) {
            cout << "Esa solución va por encima del número de pasos establecidos dentro del programa" << endl;
            return {};
        }
        auto combinations = get_matrix_variants(current_matrix);
        int local_val = -1;
        Matrix current_combination;

        if (combinations.empty()) return {};

        for (const auto& comb : combinations) {
            int val = compare_matrix(comb, objective);
            if (val > local_val) {
                local_val = val;
                current_combination = comb;
            }
        }
        current_matrix = current_combination;
        combination_path.push_back(current_combination);
    }
    return combination_path;
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

int main() {
    int n = 3;
    auto matrix = setup_matrix(n);
    auto random_matrix = randomized_matrix(matrix);

    cout << "Objective Matrix:" << endl;
    print_matrix(matrix);
    cout << endl;

    cout << "Current Matrix:" << endl;
    print_matrix(random_matrix);
    cout << endl;

    cout << "Path used to get there:" << endl;

    auto path = backtracking(matrix, random_matrix);
    for (const auto& step : path) {
        print_matrix(step);
        cout << endl;
    }

    return 0;
}