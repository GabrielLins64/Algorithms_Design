import coin_change as cc

if __name__ == '__main__':
    # coins = [25, 10, 5, 1]
    coins = [25,10,5,2]
    n = 13
    res = cc.dinamic_programming_coin_change(coins, n)
    
    print(f"Solutions ({res['amount']}):")
    for sol in res['solution']:
        print(sol)
