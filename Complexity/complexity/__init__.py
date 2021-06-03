from . import algorithms
from . import common

usage = f"""
Usage:

$ python3 -m complexity <algorithm_name> <arg 1> <arg 2> ...

Current algorithms: {tuple(algorithms.names.keys())}
"""

def run(args):
    try:
        common.test_algo(
            algorithms.names[args[1]],
            *args[2:]
        )
    except Exception as err:
        print("Error:", err)
        print(usage)
        exit(1)
