import random
import copy 
from collections import deque
def setup_matrix(n: int):
    matrix = []
    count = 0
    for i in range(n):
        local = []
        for j in range(n):
            local.append(count)
            count += 1
            if len(local) > 3:
                matrix.append(local)
                local = []
    matrix[n - 1][n - 1] = "v"
    return matrix 

def compare_matrix(m: list[list[int]], n: list[list[int]]) -> int:
    if len(m) != len(n): 
        print("Please output a correct list")
        return 0
    counter = 0
    for i in range(0, len(n) - 1):
        for j in range(0, len(n) - 1):
            if (n[i][j] == m[i][j]):
                print(":D")
                counter += 1
    print(f"Comparison Meter: {counter}")
    return counter 

def randomized_matrix(n: int) -> list[int]:
    matrix = []
    values = [x for x in range(0, n ** 2)]
    for i in range(n):
        local = []
        for j in range(n):
            elem = random.choice(values)
            local.append(elem)
            values.remove(elem)
            if len(local) > 3: 
                matrix.append(local)
                local = []

    matrix[random.randint(0, n - 1)][random.randint(0, n - 1)] = "v"
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

def backtracking(objective: list[list[int]], matrix = list[list[int]]) -> list[list[int]]:
    print(f"Original Matrix: {matrix} \n")
    queue = deque([(matrix, [])])
    visited = set()

    while queue:
        current_matrix, path = queue.popleft()
        
        if current_matrix == objective:
            return path + [current_matrix]

        matrix_tuple = tuple(map(tuple, current_matrix))
        if matrix_tuple in visited:
            continue
        visited.add(matrix_tuple)

        combinations = get_matrix_variants(current_matrix)
        combinations.sort(key=lambda x: compare_matrix(x, objective), reverse=True)

        for next_matrix in combinations:
            queue.append((next_matrix, path + [current_matrix]))

    return []  #
def main(n: int): 
    matrix = setup_matrix(n)
    random_matrix = randomized_matrix(n)

    backtracking(matrix, random_matrix)

main(4)
