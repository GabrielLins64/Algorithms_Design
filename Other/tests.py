import coin_change as cc
import rod_cutting as rc

# COIN_CHANGE_ARR = [25, 10, 5, 2]
COIN_CHANGE_ARR = [1, 5, 10, 25]
COIN_CHANGE_N   = 163

def test_coin_change_problem():
    coins = COIN_CHANGE_ARR
    n = COIN_CHANGE_N
    res = cc.dinamic_programming_coin_change(coins, n)
    
    print(f"Solutions: {res['amount']}")
    print(f"Best solution: {res['solution']}")
    print(f"Coins: {res['coins']}")
    print(f"Number of coins: {res['num_coins']}")

# ROD_CUTTING_ARR = [1, 5, 8, 9, 10, 17, 17, 20]
ROD_CUTTING_ARR = [1, 5, 8, 9, 10, 17, 17, 20, 22]

def test_rod_cutting_problem():
    prices = ROD_CUTTING_ARR

    res = rc.rod_cutting(prices)
    print(f"Prices: {prices}")
    print(f"Rod size: {len(prices)}")
    print(f"Maximum value: {res['value']}")
    print(f"Cuts indexes: {res['cuts']}")
    print(f"Cuts sizes: {[i + 1 for i in res['cuts']]}")

    val_sum = 0
    for idx in res['cuts']:
        val_sum += prices[idx]
    print(f"Sum: {val_sum}")
