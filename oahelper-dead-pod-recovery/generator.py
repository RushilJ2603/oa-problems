import sys
import random

def generate():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)
    
    # Scale parameters
    if size <= 10:
        pods = random.randint(1, 10)
        n = random.randint(0, min(15, pods * (pods - 1) // 2))
        q = random.randint(1, 20)
    elif size <= 100:
        pods = random.randint(50, 100)
        n = random.randint(50, 200)
        q = random.randint(50, 300)
    else:
        # Max scale
        pods = 100000
        n = 100000
        q = 200000
        
    print(pods)
    print(n)
    print(2)
    
    # Generate connections
    edges = set()
    # To make interesting connected components, we can build some trees
    for i in range(1, min(pods, n + 1)):
        if i == 1: continue
        # Connect to a random previous node to form a forest/tree
        u = random.randint(1, i - 1)
        v = i
        if random.choice([True, False]):
            u, v = v, u
        edges.add((u, v))
        
    while len(edges) < n:
        u = random.randint(1, pods)
        v = random.randint(1, pods)
        if u != v:
            edges.add((min(u, v), max(u, v)))
            
    edges = list(edges)[:n]
    random.shuffle(edges)
    
    for u, v in edges:
        if random.choice([True, False]):
            print(f"{u} {v}")
        else:
            print(f"{v} {u}")
            
    print(q)
    print(2)
    
    # Generate queries
    # We want a mix of type 1 and type 2
    # Ensure at least one type 1 query
    
    queries = []
    # If size is large, we might want to kill all pods in a component to test efficiency
    if size >= 50 and random.random() < 0.3:
        # Adversarial pattern: kill pods from smallest to largest in a component, and keep querying
        for i in range(1, pods + 1):
            if len(queries) < q - 1:
                queries.append((2, i))
                if random.random() < 0.5 and len(queries) < q - 1:
                    queries.append((1, i))
    else:
        for _ in range(q):
            t = random.choices([1, 2], weights=[0.4, 0.6])[0]
            p = random.randint(1, pods)
            queries.append((t, p))
            
    # Guarantee at least one type 1
    if all(t == 2 for t, p in queries):
        queries[-1] = (1, random.randint(1, pods))
        
    for t, p in queries:
        print(f"{t} {p}")

if __name__ == "__main__":
    generate()
