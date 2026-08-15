import sys
import random

def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)
    
    n = min(size, 100000)
    m = min(size, 100000)
    if n < 2: n = 2
    if m < 1: m = 1
    
    u, v, w = [], [], []
    
    if seed % 10 == 0:
        # degenerate: disconnected
        m = 1
        u = [1]
        v = [2]
        w = [10]
        src, dest = 1, n
    elif seed % 10 == 1:
        # max constraints line graph
        for i in range(1, m+1):
            u.append(i)
            v.append(i+1)
            w.append(random.randint(0, 10**9))
        src, dest = 1, m+1
        n = m + 1
    else:
        # random graph
        nodes = list(range(1, n+1))
        random.shuffle(nodes)
        src = nodes[0]
        dest = nodes[-1]
        
        if random.random() < 0.5:
            # connected
            for i in range(1, n):
                u.append(nodes[random.randint(0, i-1)])
                v.append(nodes[i])
                w.append(random.randint(0, 10**9))
            for i in range(n-1, m):
                u.append(random.randint(1, n))
                v.append(random.randint(1, n))
                w.append(random.randint(0, 10**9))
        else:
            # maybe disconnected
            for i in range(m):
                u.append(random.randint(1, n))
                v.append(random.randint(1, n))
                w.append(random.randint(0, 10**9))
                
    print(f"{n} {m}")
    for i in range(m):
        print(f"{u[i]} {v[i]} {w[i]}")
    print(f"{src} {dest}")

if __name__ == '__main__':
    main()
