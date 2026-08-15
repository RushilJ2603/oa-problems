import sys
import random

def main():
    if len(sys.argv) < 3:
        sys.exit(1)
        
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)
    
    # Scale based on size parameter
    MAX_N = 100000
    MAX_M = 200000
    MAX_DURATION = 10000
    
    n = min(size, MAX_N)
    if n < 1: n = 1
    
    s = max(1, n // 10)
    
    kind = seed % 4
    if kind == 0:
        s = 1 # all on one station to maximize contention
    elif kind == 1:
        s = n # independent stations
        
    print(f"{n} {s}")
    
    for i in range(1, n + 1):
        station = random.randint(1, s)
        duration = random.randint(1, MAX_DURATION)
        if i == n and kind == 2:
            duration = MAX_DURATION
        print(f"{station} {duration}")
        
    m = min(n * 2, MAX_M)
    if kind == 3:
        m = 0 # no dependencies
        
    edges = set()
    for _ in range(m):
        u = random.randint(1, n - 1)
        v = random.randint(u + 1, n)
        edges.add((u, v))
        
    print(len(edges))
    for u, v in edges:
        print(f"{u} {v}")

if __name__ == "__main__":
    main()
