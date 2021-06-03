from time import time
import platform, subprocess, re

def get_processor_name():
    if platform.system() == "Windows":
        return platform.processor()
    elif platform.system() == "Linux":
        command = "cat /proc/cpuinfo"
        all_info = subprocess.check_output(command, shell=True).strip()
        for line in all_info.split("\n".encode()):
            if "model name".encode() in line:
                return re.sub( ".*model name.*:", "", line.decode(), 1)

def exec_time(func):
    def wrapper(*args):
        start = time()
        print("Result:", func(*args))
        total_time = time() - start
        print("Execution time:", total_time)
    return wrapper

@exec_time
def test_time(algo, *args):
    return algo(*args)

def test_algo(algo, *args):
    print("Processor:", get_processor_name())
    print("Algorithm:", algo.__doc__)
    test_time(algo, *args)
