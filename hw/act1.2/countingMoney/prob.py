denom = {500: 10, 200: 5, 100: 10, 50: 12, 20: 14, 10: 2, 5: 1, 2: 1, 1: 0}
combinations = {}


def get_combination(change: int, denom: dict, memo: dict) -> list[int]:
    # print("Computing a new combination :)")
    change_combination = []
    change_copy = change
    for val in denom:
        if val <= change:
            while denom[val] > 0 and change > 0 and val <= change:
                denom[val] -= 1
                change_combination.append(val)
                change -= val
    memo[change_copy] = change_combination
    if change > 0:
        print("It wasn't possible to obtain a combination, I am sorry.")
        return
    return change_combination


def get_combination_stored(change: int, memo: dict, denom: dict) -> list[int]:
    # print("Using a stored combination :D")
    total_change = memo[change]
    combination = []
    for elem in total_change:
        if denom[elem] > 0:
            denom[elem] -= 1
            combination.append(elem)
        else:
            memo[change] = get_combination(change, denom, memo)
            return memo[change]
    return combination


def change(p: int, q: int, denom: dict, combinations: dict) -> list[int]:
    if len(denom) < 9:
        return combinations
    to_change = q - p
    if to_change in combinations:
        return get_combination_stored(to_change, combinations, denom)
    else:
        return get_combination(change=to_change, denom=denom, memo=combinations)


res = change(1000, 1102, denom, combinations)
res_1 = change(100, 202, denom, combinations)
print(res)
print(res_1)
