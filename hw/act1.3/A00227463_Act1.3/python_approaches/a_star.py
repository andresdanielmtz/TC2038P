import heapq

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

def get_distance(start, dest) -> int: # manhattan distance approach 
    return sum([dest[0] - start[0], dest[1] - start[1]])

def get_best_choice(board, start, dest) -> list[list[int]]:
    start_tuple = tuple(start)
    dest_tuple = tuple(dest)
    heap = [(0, start_tuple, [])]  # (f, current, path)
    g_scores = {start_tuple: 0}
    f_scores = {start_tuple: get_distance(start, dest)}
    came_from = {}

    while heap:
        f, current, path = heapq.heappop(heap)
        
        if current == dest_tuple:
            return reconstruct_path(came_from, current)

        for neighbor in get_all_combinations(board, list(current)):
            neighbor_tuple = tuple(neighbor)
            tentative_g_score = g_scores[current] + 1

            if tentative_g_score < g_scores.get(neighbor_tuple, float('inf')):
                came_from[neighbor_tuple] = current
                g_scores[neighbor_tuple] = tentative_g_score
                f_scores[neighbor_tuple] = tentative_g_score + get_distance(list(neighbor_tuple), dest)
                heapq.heappush(heap, (f_scores[neighbor_tuple], neighbor_tuple, path + [list(neighbor_tuple)]))

    print("It is not possible to get to this destination")
    return None

def reconstruct_path(came_from: dict, current: list[int]) -> list[list[int]]:
    total_path = [list(current)]
    while current in came_from:
        current = came_from[current]
        total_path.append(list(current))
    return total_path[::-1]

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
    if choices: 
        print_board(board, choices)
    else:
        print("It was not possible :(((")

board = [[1, 0, 0, 0], [1, 1, 0, 1], [0, 1, 0, 0], [1, 1, 1, 1]]
main(board)

