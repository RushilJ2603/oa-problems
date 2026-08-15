import sys
import random

def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)
    
    n = min(20, size)
    if n < 1: n = 1
    
    # generate random edges
    edges = []
    if size >= 100:
        # max scale input: full tournament or complete graph to ensure many cycles
        m = n * (n - 1)
        for u in range(1, n + 1):
            for v in range(1, n + 1):
                if u != v:
                    edges.append((u, v))
        # maybe drop a few edges randomly
        edges = [e for e in edges if random.random() < 0.8]
    else:
        # sparse graph
        for _ in range(n * 2):
            u = random.randint(1, n)
            v = random.randint(1, n)
            if u != v:
                edges.append((u, v))
                
    edges = list(set(edges)) # unique edges
    random.shuffle(edges)
    m = len(edges)
    
    print(f"{n} {m}")
    for u, v in edges:
        print(f"{u} {v}")

if __name__ == '__main__':
    main()
