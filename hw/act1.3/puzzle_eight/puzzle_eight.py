import random
import copy
from collections import deque

def setup_matrix(n: int) -> list[list[int]]:
    matrix = [[n * i + j for j in range(n)] for i in range(n)]
    matrix[n-1][n-1] = "v"  # last element is "v"
    return matrix

def print_matrix(matrix: list[list[int]]):
    for row in matrix:
        for val in row:
            print(val, end=" ")
        print()

def compare_matrix(m: list[list[int]], n: list[list[int]]) -> int:
    if len(m) != len(n):
        print("Please output a correct list")
        return 0
    counter = 0
    for i in range(len(n)):
        for j in range(len(n[i])):
            if n[i][j] == m[i][j]:
                counter += 1
    return counter

def randomized_matrix(matrix: list[list[int]]) -> list[list[int]]:
    n = len(matrix)
    flat_matrix = [item for sublist in matrix for item in sublist if item != "v"]
    random.shuffle(flat_matrix)

    new_matrix = []
    index = 0
    for i in range(n):
        row = []
        for j in range(n):
            if i == n - 1 and j == n - 1:
                row.append("v")
            else:
                row.append(flat_matrix[index])
                index += 1
        new_matrix.append(row)

    return new_matrix

def get_matrix_variants(matrix: list[list[int]]) -> list[list[list[int]]]:
    variants = []
    n = len(matrix)
    
    v_pos = None
    for i, row in enumerate(matrix):
        if "v" in row:
            v_pos = (i, row.index("v"))
            break
    
    directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]
    
    for dx, dy in directions:
        new_x, new_y = v_pos[0] + dx, v_pos[1] + dy
        if 0 <= new_x < n and 0 <= new_y < n:
            new_matrix = copy.deepcopy(matrix)
            new_matrix[v_pos[0]][v_pos[1]], new_matrix[new_x][new_y] = new_matrix[new_x][new_y], "v"
            variants.append(new_matrix)
    return variants

def backtracking(objective: list[list[int]], matrix: list[list[int]], max_steps: int = 10000) -> list[list[int]]:
    current_matrix = matrix
    combination_path = []
    steps = 0
    visited = set()

    def matrix_to_string(m):
        return ",".join(",".join(str(val) for val in row) for row in m)

    while current_matrix != objective and steps < max_steps:
        matrix_str = matrix_to_string(current_matrix)
        if matrix_str in visited:
            # Instead of returning None, let's try a random move
            combinations = get_matrix_variants(current_matrix)
            if not combinations:
                return None
            current_matrix = random.choice(combinations)
            continue

        visited.add(matrix_str)

        combinations = get_matrix_variants(current_matrix)
        if not combinations:
            return None

        best_combination = max(combinations, key=lambda x: compare_matrix(x, objective))
        
        if compare_matrix(best_combination, objective) <= compare_matrix(current_matrix, objective):
            # If we're not improving, try a random move
            best_combination = random.choice(combinations)

        print(f"Step {steps + 1}:")
        print_matrix(best_combination)
        print()

        current_matrix = best_combination
        combination_path.append(current_matrix)
        steps += 1

    return combination_path if current_matrix == objective else None

def main(n: int):
    print("Backtracking Path:")
    matrix = setup_matrix(n)
    random_matrix = randomized_matrix(matrix)
    
    backtracking_path = backtracking(matrix, random_matrix, max_steps=100000)  # Increased max_steps
    if backtracking_path:
        print(f"Solution found in {len(backtracking_path)} moves.")
    else:
        print("No solution found with backtracking.")

if __name__ == "__main__":
    main(3)