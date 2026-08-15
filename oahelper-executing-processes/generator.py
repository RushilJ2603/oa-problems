import sys
import random

def main():
    if len(sys.argv) < 3:
        sys.exit(1)
    
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)
    
    # Scale based on size parameter
    MAX_N = 300000
    MAX_P = 1000000000
    
    n = min(size, MAX_N)
    if n < 1:
        n = 1
        
    print(n)
    
    # Depending on seed parity, generate different types of arrays
    kind = seed % 5
    if kind == 0:
        # completely random
        priorities = [random.randint(1, MAX_P) for _ in range(n)]
    elif kind == 1:
        # sorted increasing
        priorities = sorted([random.randint(1, MAX_P) for _ in range(n)])
    elif kind == 2:
        # sorted decreasing
        priorities = sorted([random.randint(1, MAX_P) for _ in range(n)], reverse=True)
    elif kind == 3:
        # all same
        val = random.randint(1, MAX_P)
        priorities = [val] * n
    else:
        # max values with a very small value at the end (worst case for some algorithms)
        priorities = [MAX_P] * (n - 1) + [1]
        
    print(" ".join(map(str, priorities)))

if __name__ == "__main__":
    main()
