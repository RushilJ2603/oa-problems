import sys
import random

def main():
    if len(sys.argv) < 3:
        print("Usage: python generator.py <seed> <size>")
        sys.exit(1)
    
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)
    
    max_c = max(1, min(100000, size * 10000))
    max_m = max(0, min(100000, size * 10000))
    max_q = max(1, min(100000, size * 10000))
    
    if size >= 10:
        clusters = 100000
        m = 100000
        q = 100000
    else:
        clusters = random.randint(max_c // 2, max_c)
        if clusters == 0: clusters = 1
        m = random.randint(max_m // 2, max_m)
        q = random.randint(max_q // 2, max_q)
    
    print(f"{clusters}")
    print(f"{m}")
    
    # We want a mix of connected components, some large, some small.
    # To keep m fast, just random edges are fine.
    for _ in range(m):
        u = random.randint(1, clusters)
        v = random.randint(1, clusters)
        print(f"{u} {v}")
        
    print(f"{q}")
    for _ in range(q):
        t = random.randint(1, 2)
        c = random.randint(1, clusters)
        print(f"{t} {c}")

if __name__ == "__main__":
    main()
