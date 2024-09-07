board = [[1, 0, 0, 0], [1, 1, 0, 1], [0, 1, 0, 0], [1, 1, 1, 1]]

# Backtracking Method 

def get_all_combinations(board: list[list[int]], start: list[int]) -> list[list[int]]:
    directions = [(0, 1), (0, -1), (1, 0), (-1, 0)] # all possible combinations 
    possible_dir = [] 
    for direction in directions:
        x_dir = start[0] + direction[0]
        y_dir = start[1] + direction[1] 

        if 0 <= x_dir < len(board) and 0 <= y_dir < len(board):
            path = board[x_dir][y_dir]
            if path == 1:
                possible_dir.append([x_dir, y_dir])
                        
    return possible_dir
        
def get_distance(start, dest) -> int:
    return sum([dest[0] - start[0], dest[1] - start[1]])

def get_best_choice(board, start, dest) -> list[list[int]]: 
    combinations = []
    combinations.append(start)
    while start != dest:
        
        combs = get_all_combinations(board, start)
        if not combs: 
            print("It is no possible to get to this destination")
            return 

        min_val = len(board) ** 10 # can't have -1 in how close it is 
        min_comb = None
        for comb in combs:
            if get_distance(comb, dest) < min_val:
                min_val = get_distance(comb, dest)
                min_comb = comb 
        start = min_comb
        combinations.append(start)
    return combinations

def print_board(board, combinations) -> None:

    for i in range(0, len(board)):
        for j in range(0, len(board)):
            if [i, j] in combinations:
                print(1, end = " ")
            else: 
                print(0, end = " ")
        print("\n")


def main(board):
    dest = [len(board) - 1, len(board) - 1] # [3, 3]
    start = [0, 0] # first elem 
    choices = get_best_choice(board, start, dest)
    # print(get_all_combinations(board, start))
    print_board(board, choices)
main(board)

