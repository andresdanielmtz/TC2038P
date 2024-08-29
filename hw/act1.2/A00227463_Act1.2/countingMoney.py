memo = dict()

def get_optimal_denomination(remaining: int, denominations: dict):
    for val in sorted(denominations.keys(), reverse=True):
        if val <= remaining and denominations[val] > 0:
            return val
    return 0

def calculate_change(remaining: int, denominations: dict) -> list[int]:
    denom_tuple = tuple(sorted(denominations.items())) # Tupla de las denominaciones (500, 200, 100, 50, 20, 10, 5, 2, 1) 
    
    
    if (remaining, denom_tuple) in memo:
        return memo[(remaining, denom_tuple)]

    if remaining == 0:
        return []

    optimal = get_optimal_denomination(remaining, denominations)
    if optimal == 0:
        memo[(remaining, denom_tuple)] = None
        return None

    denominations[optimal] -= 1
    result = calculate_change(remaining - optimal, denominations) 
    
    if result is not None:
        result = [optimal] + result
        memo[(remaining, denom_tuple)] = result
        return result
    
    denominations[optimal] += 1
    memo[(remaining, denom_tuple)] = None
    return None


denominations = {500: 10, 200: 5, 100: 10, 50: 12, 20: 14, 10: 2, 5: 1, 2: 1, 1: 2}

def print_result(target_change):
    result = calculate_change(target_change, denominations)
    if result:
        print(f"Change for {target_change}: {result}")
    else:
        print(f"Lo siento, pero no hay cambio suficiente para {target_change} :(")
    print(f"Remaining Denominations: {denominations} \n")

target_change = 102
print_result(target_change)
print_result(102)
print_result(102)