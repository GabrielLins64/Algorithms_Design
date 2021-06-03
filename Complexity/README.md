## Algorithms time measurer

Measures the execution time of any algorithm at `complexity.algorithms` submodule. Gives info about the used processor.

<hr>

**Current algorithms:**

- Recursive Fibonacci

> **Algorithm alias:** fibo1<br>
> **Time complexity:** O(2^n)<br>
> **Arguments:** n

- Linear Fibonacci

> **Algorithm alias:** fibo2<br>
> **Time complexity:** O(n)<br>
> **Arguments:** n

- Golden Ratio

> **Algorithm alias:** golden_ratio<br>
> **Time complexity:** O( O(fibo(n)) + O(fibo(n-1)) )<br>
> **Arguments:** fibo (1 or 2), n

- Linear Power

> **Algorithm alias:** pow1<br>
> **Time complexity:** O(n)<br>
> **Arguments:** a, n

- Logarithmic Power

> **Algorithm alias:** pow2<br>
> **Time complexity:** O(log n)<br>
> **Arguments:** a, n

**Usage:**

At this root directory, run:

`$ python3 -m complexity <algorithm_name> <arg 1> <arg 2> ...`

Examples:

`$ python3 -m complexity fibo1 35`

`$ python3 -m complexity golden_ratio 1 35`

`$ python3 -m complexity pow2 20.32 25`
