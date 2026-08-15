import sys
import random

def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)
    
    n = max(2, min(3000, size * 30))
    m = max(1, min(100000, size * 1000))
    if size > 90:
        n = 3000
        m = 100000
    if size < 5:
        n = random.randint(2, 10)
        m = random.randint(n-1, min(n*(n-1)//2, 20))
    
    edges = set()
    edge_list = []
    
    # ensure connectivity
    for i in range(2, n + 1):
        u = random.randint(1, i - 1)
        v = i
        w = random.randint(1, 100000)
        if random.random() < 0.5: u, v = v, u
        edges.add((min(u,v), max(u,v)))
        edge_list.append((u, v, w))
    
    # additional edges
    attempts = 0
    while len(edge_list) < m and attempts < 100000:
        attempts += 1
        u = random.randint(1, n)
        v = random.randint(1, n)
        if u == v: continue
        if (min(u,v), max(u,v)) in edges: continue
        edges.add((min(u,v), max(u,v)))
        w = random.randint(1, 100000)
        edge_list.append((u, v, w))
        
    random.shuffle(edge_list)
    print(f"{n} {len(edge_list)}")
    for u, v, w in edge_list:
        print(f"{u} {v} {w}")

if __name__ == '__main__':
    main()
