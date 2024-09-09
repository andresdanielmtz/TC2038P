#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

typedef pair<int, int> Point;

vector<Point> get_all_combinations(const vector<vector<int>>& board, const Point& start) {
    vector<Point> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    vector<Point> possible_dir;
    for (const auto& direction : directions) {
        int x_dir = start.first + direction.first;
        int y_dir = start.second + direction.second;
        if (x_dir >= 0 && x_dir < board.size() && y_dir >= 0 && y_dir < board[0].size()) {
            if (board[x_dir][y_dir] == 1) {
                possible_dir.push_back({x_dir, y_dir});
            }
        }
    }
    return possible_dir;
}

int get_distance(const Point& start, const Point& dest) {
    return abs(dest.first - start.first) + abs(dest.second - start.second);
}

vector<Point> backtrack(const vector<vector<int>>& board, const Point& start, const Point& dest, vector<vector<bool>>& visited) {
    if (start == dest) {
        return {start};
    }

    visited[start.first][start.second] = true;
    vector<Point> possible_moves = get_all_combinations(board, start);
    

    sort(possible_moves.begin(), possible_moves.end(), 
         [&dest](const Point& a, const Point& b) {
             return get_distance(a, dest) < get_distance(b, dest);
         });

    for (const auto& move : possible_moves) {
        if (!visited[move.first][move.second]) {
            vector<Point> path = backtrack(board, move, dest, visited);
            if (!path.empty()) {
                path.insert(path.begin(), start);
                return path;
            }
        }
    }

    visited[start.first][start.second] = false;
    return {};
}

vector<Point> get_best_choice(const vector<vector<int>>& board, const Point& start, const Point& dest) {
    vector<vector<bool>> visited(board.size(), vector<bool>(board[0].size(), false));
    vector<Point> path = backtrack(board, start, dest, visited);
    
    if (path.empty()) {
        cout << "It is not possible to get to this destination" << endl;
    }
    
    return path;
}

void print_board(const vector<vector<int>>& board, const vector<Point>& path) {
    for (int i = 0; i < board.size(); ++i) {
        for (int j = 0; j < board[i].size(); ++j) {
            if (find(path.begin(), path.end(), Point{i, j}) != path.end()) {
                cout << "1 ";
            } else {
                cout << board[i][j] << " ";
            }
        }
        cout << endl;
    }
}

int main() {
    vector<vector<int>> board = {
        {1, 0, 0, 0},
        {1, 1, 0, 1},
        {0, 1, 0, 0},
        {1, 1, 1, 1}
    };

    Point dest = {static_cast<int>(board.size()) - 1, static_cast<int>(board[0].size()) - 1};
    Point start = {0, 0};

    vector<Point> choices = get_best_choice(board, start, dest);

    if (!choices.empty()) {
        print_board(board, choices);
    } else {
        cout << "It was not possible :(((" << endl;
    }

    return 0;
}