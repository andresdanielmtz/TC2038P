def duplicatedWork(n: int) -> None:
    pair_list = {}
    for c in range(n):
        for d in range(n):
            res = c**3 + d**3
            pair_list[res] = (c, d)
    for a in range(n):
        for b in range(n):
            res = a**3 + b**3
            if res in pair_list:
                print(f"({a}, {b}) = {pair_list[res]}")


# TODO: Figure out why is it necessarily right.


def optimizedDuplicatedWork(n: int) -> None:
    pair_list = {}
    for c in range(n):
        for d in range(n):
            res = c**3 + d**3
            pair_list[res] = (c, d)
    for results, pair in pair_list.items():
        for pair1 in pair:
            for pair2 in pair:
                print(f"{pair1} {pair2}")


if __name__ == "__main__":
    optimizedDuplicatedWork(10)
