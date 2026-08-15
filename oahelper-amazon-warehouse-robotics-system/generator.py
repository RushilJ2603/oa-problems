import sys
import random

def main():
    if len(sys.argv) < 3:
        print("Usage: python generator.py <seed> <size>")
        return
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)
    
    n = size
    if n < 2:
        n = 2
    if n > 200000:
        n = 200000
    
    print(n)
    
    case_type = random.randint(0, 5)
    if case_type == 0:
        # all same
        val = random.randint(0, n - 1)
        arr = [val] * n
    elif case_type == 1:
        # sorted
        arr = sorted([random.randint(0, n - 1) for _ in range(n)])
    elif case_type == 2:
        # reverse sorted
        arr = sorted([random.randint(0, n - 1) for _ in range(n)], reverse=True)
    elif case_type == 3:
        # all 0s
        arr = [0] * n
    elif case_type == 4:
        # all n-1
        arr = [n - 1] * n
    else:
        # random
        arr = [random.randint(0, n - 1) for _ in range(n)]
        
    for x in arr:
        print(x)

if __name__ == '__main__':
    main()
