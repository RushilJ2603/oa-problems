import sys
import random

def generate_tree(seed, size):
    random.seed(seed)
    
    if size < 3:
        size = 3
    if size > 100:
        size = 100
        
    n = size
    
    # max scale if size is large
    is_max = (size == 100 and random.random() < 0.5)
    max_val = 10**12 if is_max else 1000
    
    root_val = random.randint(0, max_val)
    print(n)
    print(root_val)
    
    paths = [""]
    available_spots = [("L", ""), ("R", "")]
    
    edges = []
    
    for _ in range(n - 1):
        idx = random.randint(0, len(available_spots) - 1)
        direction, parent = available_spots.pop(idx)
        
        new_path = parent + direction
        paths.append(new_path)
        
        available_spots.append(("L", new_path))
        available_spots.append(("R", new_path))
        
        val = random.randint(0, max_val)
        edges.append((new_path, val))
        
    random.shuffle(edges)
    
    for path, val in edges:
        print(f"{path} {val}")

if __name__ == '__main__':
    generate_tree(int(sys.argv[1]), int(sys.argv[2]))
