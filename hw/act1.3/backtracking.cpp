#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <cmath>
#include <algorithm>

using namespace std;

typedef pair<int, int> Point;

// Custom hash function for Point
struct PointHash {
    size_t operator()(const Point& p) const {
        return hash<int>()(p.first) ^ hash<int>()(p.second);
    }
};

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

vector<Point> reconstruct_path(const unordered_map<Point, Point, PointHash>& came_from, Point current) {
    vector<Point> total_path = {current};
    while (came_from.find(current) != came_from.end()) {
        current = came_from.at(current);
        total_path.push_back(current);
    }
    reverse(total_path.begin(), total_path.end());
    return total_path;
}

vector<Point> get_best_choice(const vector<vector<int>>& board, const Point& start, const Point& dest) {
    auto cmp = [](const tuple<int, Point, vector<Point>>& a, const tuple<int, Point, vector<Point>>& b) {
        return get<0>(a) > get<0>(b);
    };
    priority_queue<tuple<int, Point, vector<Point>>, vector<tuple<int, Point, vector<Point>>>, decltype(cmp)> heap(cmp);
    
    unordered_map<Point, int, PointHash> g_scores;
    unordered_map<Point, int, PointHash> f_scores;
    unordered_map<Point, Point, PointHash> came_from;

    heap.push({0, start, {}});
    g_scores[start] = 0;
    f_scores[start] = get_distance(start, dest);

    while (!heap.empty()) {
        auto [f, current, path] = heap.top();
        heap.pop();

        if (current == dest) {
            return reconstruct_path(came_from, current);
        }

        for (const auto& neighbor : get_all_combinations(board, current)) {
            int tentative_g_score = g_scores[current] + 1;

            if (g_scores.find(neighbor) == g_scores.end() || tentative_g_score < g_scores[neighbor]) {
                came_from[neighbor] = current;
                g_scores[neighbor] = tentative_g_score;
                f_scores[neighbor] = tentative_g_score + get_distance(neighbor, dest);
                vector<Point> new_path = path;
                new_path.push_back(neighbor);
                heap.push({f_scores[neighbor], neighbor, new_path});
            }
        }
    }

    cout << "It is not possible to get to this destination" << endl;
    return {};
}

void print_board(const vector<vector<int>>& board, const vector<Point>& path) {
    for (int i = 0; i < board.size(); ++i) {
        for (int j = 0; j < board[i].size(); ++j) {
            if (find(path.begin(), path.end(), Point{i, j}) != path.end()) {
                cout << "1 ";
            } else {
                cout << "0 ";
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