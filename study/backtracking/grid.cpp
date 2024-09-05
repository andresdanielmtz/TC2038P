#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>

using Matrix = std::vector<std::vector<int> >;

Matrix setup_matrix(int n) {
    Matrix matrix(n, std::vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            matrix[i][j] = n * i + j;
        }
    }
    matrix[n-1][n-1] = -1; // using -1 to represent 'v'
    return matrix;
}

int compare_matrix(const Matrix& m, const Matrix& n) {
    if (m.size() != n.size()) {
        std::cout << "Please output a correct list" << std::endl;
        return 0;
    }
    int counter = 0;
    for (size_t i = 0; i < n.size(); ++i) {
        for (size_t j = 0; j < n[i].size(); ++j) {
            if (n[i][j] == m[i][j]) {
                ++counter;
            }
        }
    }
    return counter;
}

std::vector<Matrix> get_matrix_variants(const Matrix& matrix) {
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
    
    std::vector<std::pair<int, int> > directions;
    directions.emplace_back(-1, 0);
    directions.emplace_back(1, 0);
    directions.emplace_back(0, -1);
    directions.emplace_back(0, 1);
    for (const auto& [dx, dy] : directions) {
        int new_x = v_pos.first + dx, new_y = v_pos.second + dy;
        if (new_x >= 0 && new_x < n && new_y >= 0 && new_y < n) {
            Matrix new_matrix = matrix;
            std::swap(new_matrix[v_pos.first][v_pos.second], new_matrix[new_x][new_y]);
            variants.push_back(new_matrix);
        }
    }
    return variants;
}

Matrix randomized_matrix(Matrix matrix) {
    std::random_device rd;
    std::mt19937 gen(rd());
    
    for (int i = 0; i < std::uniform_int_distribution<>(1, 100)(gen); ++i) {
        auto combination_list = get_matrix_variants(matrix);
        if (combination_list.empty()) return matrix;
        matrix = combination_list[std::uniform_int_distribution<>(0, combination_list.size() - 1)(gen)];
    }
    return matrix;
}

std::vector<Matrix> backtracking(const Matrix& objective, Matrix matrix) {
    std::vector<Matrix> combination_path;
    int max_steps = 10000;
    
    while (matrix != objective) {
        if (--max_steps == 0) {
            std::cout << "Esa solución va por encima del número de pasos establecidos dentro del programa" << std::endl;
            return {};
        }
        
        auto combinations = get_matrix_variants(matrix);
        if (combinations.empty()) return {};
        
        int local_val = -1;
        Matrix current_combination;
        
        for (const auto& comb : combinations) {
            int val = compare_matrix(comb, objective);
            if (val > local_val) {
                local_val = val;
                current_combination = comb;
            }
        }
        
        matrix = current_combination;
        combination_path.push_back(current_combination);
    }
    return combination_path;
}

void print_matrix(const Matrix& matrix) {
    for (const auto& row : matrix) {
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

int main() {
    int n = 10;
    Matrix matrix = setup_matrix(n);
    Matrix random_matrix = randomized_matrix(matrix);
    
    std::cout << "Objective Matrix:\n";
    print_matrix(matrix);
    std::cout << "\nCurrent Matrix:\n";
    print_matrix(random_matrix);
    std::cout << "\nPath used to get there:\n";
    
    auto path = backtracking(matrix, random_matrix);
    
    for (const auto& step : path) {
        print_matrix(step);
        std::cout << "\n";
    }
    
    return 0;
}