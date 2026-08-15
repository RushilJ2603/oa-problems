import sys
import random

def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)
    
    n = min(size, 1000000)
    if n < 1: n = 1
    
    k = random.randint(1, n)
    if seed % 10 == 0:
        k = 1
    elif seed % 10 == 1:
        k = n
        
    if seed % 10 == 2:
        val = random.randint(1, 10**9)
        arr = [val] * n
    elif seed % 10 == 3:
        arr = sorted([random.randint(1, 10**9) for _ in range(n)])
    elif seed % 10 == 4:
        arr = sorted([random.randint(1, 10**9) for _ in range(n)], reverse=True)
    else:
        arr = [random.randint(1, 10**9) for _ in range(n)]
        
    print(n)
    for x in arr:
        print(x)
    print(k)

if __name__ == '__main__':
    main()
