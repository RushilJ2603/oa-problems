import sys
import random

def generate_test(seed, size):
    random.seed(int(seed))
    
    n_max = 100000
    m_max = 100000
    
    # Scale size parameter to N. 
    # For gate_candidate random brute checks (size up to 120), N will be up to ~6000.
    # For make_hidden (size up to 2000), N will be up to 100000 (max-scale).
    n = min(n_max, max(2, size * 50))
    m = min(m_max, max(2, size * 50))
    
    e = n - 1
    
    edges = []
    struct_type = random.choice(['random', 'line', 'star', 'caterpillar', 'binary'])
    
    if size >= 1000:
        # At max scale, ensure variety based on seed
        struct_type = ['random', 'line', 'star', 'binary'][int(seed) % 4]

    nodes = list(range(n))
    random.shuffle(nodes)
    
    if struct_type == 'line':
        for i in range(1, n):
            edges.append((i-1, i))
    elif struct_type == 'star':
        for i in range(1, n):
            edges.append((0, i))
    elif struct_type == 'binary':
        for i in range(1, n):
            edges.append(((i-1)//2, i))
    elif struct_type == 'caterpillar':
        spine_len = n // 2
        for i in range(1, spine_len):
            edges.append((i-1, i))
        for i in range(spine_len, n):
            spine_node = random.randint(0, spine_len - 1)
            edges.append((spine_node, i))
    else:
        for i in range(1, n):
            p = random.randint(0, i - 1)
            edges.append((p, i))
            
    out_edges = []
    for u, v in edges:
        if random.choice([True, False]):
            out_edges.append((u, v))
        else:
            out_edges.append((v, u))
    random.shuffle(out_edges)
    
    char_type = random.choice(['random', 'few', 'all_same'])
    if char_type == 'all_same':
        c = random.choice('abcdefghijklmnopqrstuvwxyz')
        chars = [c] * n
    elif char_type == 'few':
        vocab = random.sample('abcdefghijklmnopqrstuvwxyz', random.randint(2, 4))
        chars = [random.choice(vocab) for _ in range(n)]
    else:
        chars = [random.choice('abcdefghijklmnopqrstuvwxyz') for _ in range(n)]
        
    queries = [random.randint(0, n - 1) for _ in range(m)]
    
    print(f"{n} {e}")
    for u, v in out_edges:
        print(f"{u} {v}")
    print(n)
    for c in chars:
        print(c)
    print(m)
    for q in queries:
        print(q)

if __name__ == '__main__':
    generate_test(int(sys.argv[1]), int(sys.argv[2]))
