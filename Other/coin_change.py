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

    res_coins = [0] * len(coins)
    for idx, coin in enumerate(coins):
        res_coins[idx] = solutions[-1].count(coin)

    solution = {
        "solution": solutions[-1],
        "coins": res_coins,
        "num_coins": np.sum(res_coins),
        "amount": table[n]
    }
    return solution
