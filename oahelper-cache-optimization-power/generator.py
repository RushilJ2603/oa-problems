import sys
import random

def main():
    if len(sys.argv) < 3:
        print("Usage: python3 generator.py <seed> <size>")
        return
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)
    
    n = size
    if n > 100000:
        n = 100000
    
    # Randomly select a mode
    mode = random.random()
    
    if mode < 0.1 and size >= 100000: # 10% chance of max scale all identical
        power = [10**9 for _ in range(n)]
    elif mode < 0.2: # sorted
        power = sorted([random.randint(1, 10**9) for _ in range(n)])
    elif mode < 0.3: # reverse sorted
        power = sorted([random.randint(1, 10**9) for _ in range(n)], reverse=True)
    elif mode < 0.4: # all duplicate
        val = random.randint(1, 10**9)
        power = [val for _ in range(n)]
    else: # fully random
        power = [random.randint(1, 10**9) for _ in range(n)]
        
    print(n)
    for p in power:
        print(p)

if __name__ == '__main__':
    main()
