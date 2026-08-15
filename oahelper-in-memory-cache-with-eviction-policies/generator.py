import sys
import random

def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)
    
    capacity = max(1, min(10000, size * 100))
    n = max(1, min(100000, size * 1000))
    if size > 90:
        capacity = random.randint(100, 1000)
        n = 100000
    if size < 5:
        capacity = random.randint(1, 5)
        n = random.randint(5, 20)
        
    policy = random.choice(["LRU", "LFU"])
    
    print(capacity)
    print(policy)
    print(n)
    
    keys = [f"key_{i}" for i in range(min(n, capacity * 2 + 10))]
    
    for _ in range(n):
        cmd = random.choice(["put", "get", "get", "put", "delete", "size"])
        if cmd == "put": print(f"put {random.choice(keys)} {random.randint(1, 100)}")
        elif cmd == "get": print(f"get {random.choice(keys)}")
        elif cmd == "delete": print(f"delete {random.choice(keys)}")
        elif cmd == "size": print("size")
        elif cmd == "clear": print("clear")

if __name__ == '__main__':
    main()
