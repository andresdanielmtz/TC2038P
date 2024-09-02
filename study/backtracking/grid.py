import random

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

def backtracking(objective: list[int], matrix = list[int]) -> list[int]:
    pass

matrix = setup_matrix(4)
random_matrix = randomized_matrix(4)

print(matrix)
print(random_matrix)
