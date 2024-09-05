import random
import copy 
from collections import deque

def setup_matrix(n: int) -> list[list[int]]:
    matrix = [[n * i + j for j in range(n)] for i in range(n)]
    matrix[n-1][n-1] = "v" # last element is "v" 
    return matrix


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
    for i in range(4, random.randint(1, 100)):
        combination_list = get_matrix_variants(matrix)
        if not combination_list: return matrix 
        matrix = random.choice(combination_list)
    return matrix

def get_matrix_variants(matrix: list[list[int]]) -> list[list[list[int]]]:
    variants = []
    n = len(matrix)
    
    v_pos = None
    for i, row in enumerate(matrix):
        if 'v' in row:
            v_pos = (i, row.index('v'))
            break
    
    directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]
    
    for dx, dy in directions:
        new_x, new_y = v_pos[0] + dx, v_pos[1] + dy
        if 0 <= new_x < n and 0 <= new_y < n:
            new_matrix = copy.deepcopy(matrix)
            new_matrix[v_pos[0]][v_pos[1]], new_matrix[new_x][new_y] = new_matrix[new_x][new_y], 'v'
            variants.append(new_matrix) 
    return variants

def backtracking(objective: list[list[int]], matrix: list[list[int]]) -> list[list[int]]:
    current_matrix = matrix 
    combination_path = []
    max_steps = 10000
    while current_matrix != objective: 
        max_steps -= 1 
        if max_steps == 0:
            print("Esa solución va por encima del número de pasos establecidos dentro del programa")
            return 
        combinations = get_matrix_variants(current_matrix) # combinations 
        local_val = -1 # can't have -1 
        current_combination = None

        if not combinations: return 

        for comb in combinations: 
            val = compare_matrix(comb, objective)
            if val > local_val: 
                local_val = val
                current_combination = comb
        # print(local_val)
        current_matrix = current_combination
        combination_path.append(current_combination)
    return combination_path



def main(n: int): 
    """Main function to setup and run the backtracking solver."""
    matrix = setup_matrix(n)
    random_matrix = randomized_matrix(matrix)

    print(f"Objective Matrix: \n {matrix} \n")
    print(f"Current Matrix: \n {random_matrix} \n")

    print("Path used to get to there: \n")

    path = backtracking(matrix, random_matrix)
    print(path)

main(10)
