import sys
import random

def main():
    if len(sys.argv) < 3:
        sys.exit(1)
    
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)
    
    max_N = 1000
    max_M = 1000
    max_T = 1000
    max_F = 1000
    
    def get_val(max_val, size):
        return max(2, int(max_val * size / 100.0))
        
    n = get_val(max_N, size)
    m = get_val(max_M, size)
    if size == 100:
        n = max_N
        m = max_M
        
    m = min(m, n * (n - 1) // 2)
    maxTime = max(1, int(max_T * size / 100.0))
    if size == 100:
        maxTime = max_T
        
    fees = [random.randint(1, int(max_F * size / 100.0) or 1) for _ in range(n)]
    
    edges = []
    edges_set = set()
    
    if size == 100 and seed % 2 == 0:
        # Generate a path to ensure max TLE checking
        src = 0
        dest = n - 1
        for i in range(n - 1):
            t = random.randint(1, 10)
            edges.append((i, i + 1, t))
            edges_set.add((i, i + 1))
        # pad with remaining edges
        while len(edges) < m:
            u = random.randint(0, n - 1)
            v = random.randint(0, n - 1)
            if u == v: continue
            if u > v: u, v = v, u
            if (u, v) not in edges_set:
                edges_set.add((u, v))
                edges.append((u, v, random.randint(1, 10)))
    else:
        while len(edges) < m:
            u = random.randint(0, n - 1)
            v = random.randint(0, n - 1)
            if u == v: continue
            if u > v: u, v = v, u
            if (u, v) not in edges_set:
                edges_set.add((u, v))
                t = random.randint(1, max(1, int(max_T * size / 100.0)))
                edges.append((u, v, t))
        src = random.randint(0, n - 1)
        dest = random.randint(0, n - 1)
        
    print(f"{n} {m} {maxTime}")
    print(" ".join(map(str, fees)))
    for u, v, t in edges:
        print(f"{u} {v} {t}")
    print(f"{src} {dest}")

if __name__ == '__main__':
    main()
