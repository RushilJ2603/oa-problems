import sys
import random

def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)
    
    N = 2 + (size * 10000 // 100) if size > 1 else 2
    N = min(max(N, 2), 10000)
    
    M = 1 + (size * 50000 // 100)
    M = min(max(M, 1), 50000)
    
    K = random.randint(0, 10)
    
    if size >= 95:
        N = 10000
        M = 50000
        K = 10
        
    print(f"{N} {M} {K}")
    
    edges = []
    if random.random() < 0.7:
        path = list(range(2, N))
        random.shuffle(path)
        path = [1] + path + [N]
        for i in range(len(path) - 1):
            if len(edges) < M:
                edges.append((path[i], path[i+1], random.randint(1000, 10**6)))
                
    while len(edges) < M:
        u = random.randint(1, N)
        v = random.randint(1, N)
        if u != v:
            edges.append((u, v, random.randint(1, 10**6)))
            
    for u, v, w in edges:
        print(f"{u} {v} {w}")
        
    for _ in range(K):
        a = random.randint(1, N)
        b = random.randint(1, N)
        while a == b:
            b = random.randint(1, N)
        print(f"{a} {b}")

if __name__ == '__main__':
    main()
