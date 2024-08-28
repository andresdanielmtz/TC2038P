denom = {500: 0, 200: 0, 100: 0, 50: 0, 20: 0, 10: 0, 5: 0, 2: 0, 1: 0}

def change(p, q, denom): 
    to_change = q - p
    print(f"Change: {to_change}")
    for val in denom: 
        print(val)
    pass 


print(change(1000, 1101, denom))