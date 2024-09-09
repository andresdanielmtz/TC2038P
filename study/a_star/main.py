import random 

def setup_matrix(n: int) -> list[list[int]]:
    matrix = [[0 for j in range(n)] for i in range(n)]
    matrix[n - 1][n- 1] = 1 
    return matrix 

x = setup_matrix(4)
print(x)
