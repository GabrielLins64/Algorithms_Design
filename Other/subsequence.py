def longest_decreasing_subsequence(A):
    m = [0] * len( A )
    for x in range( len( A ) - 2, -1, -1 ):
        for y in range( len( A ) - 1, x, -1 ):
            if m[x] <= m[y] and A[x] > A[y]:
                m[x] = m[y] + 1
    max_value = max( m )
    result = []
    for i in range( len( m ) ):
        if max_value == m[i]:
            result.append( A[i] )
            max_value -= 1
    
    return result
