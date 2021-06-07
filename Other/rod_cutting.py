def rod_cutting(prices):
    n = len(prices)
    dp_values = [0 for i in range(n + 1)]
    cuts = [-1] * (n + 1)
    max_val = float('-inf')

    for i in range(1, n + 1):
        for j in range(i):
            current_cut_value = prices[j] + dp_values[i - j - 1]

            if (current_cut_value > max_val):
                max_val = current_cut_value
                cuts[i] = j + 1
        
        dp_values[i] = max_val
    
    length = n
    actual_cuts = []
    while (length > 0):
        actual_cuts.append(cuts[length] - 1)
        length -= cuts[length]

    solution = {
        "value": dp_values[n],
        "cuts": actual_cuts
    }

    return solution
