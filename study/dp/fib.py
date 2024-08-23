memo = {0 : 0, 1 : 1}

def fib(n, memo):
    memo = memo or {}
    if n in memo:
        return memo[n]
    if n == 0:
        return 0
    elif n == 1:
        return 1    
    memo[n] = fib(n - 1, memo) + fib(n - 2, memo)
    return memo[n] 

for i in range(100):
    res = fib(i, memo)
    print(f"Result: {res}")

