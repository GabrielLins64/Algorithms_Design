"""PAA algorithms for complexity testing
"""

def fibo1(n):
    """Recursive Fibo O(2^n)"""
    n = int(n)
    if(n == 1):
        return 1
    elif(n == 2):
        return 1
    else:
        return fibo1(n-1) + fibo1(n-2)

def fibo2(n):
    """Linear Fibo O(n)"""
    n = int(n)
    f = []
    f.append(1)
    f.append(1)
    for i in range(2, n):
        f.append(f[i-1] + f[i-2])
    return f[n-1]

def golden_ratio(fibo, n):
    """Fibonacci Golden Ratio O( O( fibo(n) ) + O( fibo(n-1) ) )"""
    algo = fibo1 if fibo == '1' else fibo2
    n = int(n)
    return algo(n) / algo(n-1)

def pow1(a, n):
    """Linear Power O(n)"""
    a = float(a)
    n = int(n)
    res = a
    for i in range(n-1):
        res *= a
    return res

def pow2(a, n):
    """Log(n) Power O(log n)"""
    a = float(a)
    n = int(n)
    if(n == 0): return 1
    elif(n == 1): return a
    else:
        if(n % 2 == 0): 
            tmp = pow2(a, n/2)
            return tmp * tmp
        else:
            tmp = pow2(a, (n-1)/2)
            return a * tmp * tmp

names = {
    "fibo1": fibo1,
    "fibo2": fibo2,
    "golden_ratio": golden_ratio,
    "pow1": pow1,
    "pow2": pow2,
}
