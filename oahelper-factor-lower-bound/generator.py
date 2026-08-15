import sys
import random

def main():
    if len(sys.argv) < 3:
        print("Usage: python generator.py <seed> <size>")
        sys.exit(1)
    
    seed = int(sys.argv[1])
    size = float(sys.argv[2])
    
    random.seed(seed)
    
    if size == 0:
        N = random.randint(2, 100)
        m = random.randint(1, 10)
    elif size == 1:
        # Max scale
        highly_composite = [735134400, 892371480, 977728752, 1000000000, 999999999]
        N = random.choice(highly_composite)
        if seed % 3 == 0:
            N = int(1e9)
        m = 100000
    else:
        # Interpolate
        max_m = 100000
        max_N = 10**9
        m = int(10 + size * (max_m - 10))
        if random.random() < 0.5:
            N = random.randint(2, max_N)
        else:
            N = random.randint(2, max(2, int(size * max_N)))
            
    m = max(1, min(m, 100000))
    N = max(2, min(N, 10**9))
    
    nums = set()
    nums.add(0)
    while len(nums) < m:
        nums.add(random.randint(1, 100000))
        
    nums = list(nums)
    
    # some tests want sorted/reverse-sorted
    if seed % 7 == 0:
        nums.sort()
    elif seed % 7 == 1:
        nums.sort(reverse=True)
    else:
        random.shuffle(nums)
    
    print(N)
    print(m)
    print(" ".join(map(str, nums)))

if __name__ == '__main__':
    main()
