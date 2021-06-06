import numpy as np

def combine(parent, me):
    if len(parent) == 0:
        return [[me]]
    return [entry + [me] for entry in parent]

def dinamic_programming_coin_change(coins, n):
    coins.sort()
    table = [0 for k in range(n + 1)]
    table[0] = 1
    ways = [[] for _ in range(n + 1)]

    for coin in coins:
        for x in range(coin, n + 1):
            table[x] = table[x] + table[x - coin]
            ways[x].extend(combine(ways[x - coin], coin))

    solutions = [x for x in ways[n] if np.sum(x) == n]
    solution = {
        "solution": solutions,
        "amount": table[n]
    }
    return solution
