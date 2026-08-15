import sys
import random

def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)
    
    n = size
    if n > 100000:
        n = 100000
    if n < 2:
        n = 2
    q = n
    
    print("1") # 1 test case
    print(n)
    print(q)
    
    arr = [random.randint(1, 1000) for _ in range(n)]
    print(" ".join(map(str, arr)))
    
    for _ in range(q):
        if random.random() < 0.3:
            # type 1
            idx = random.randint(1, n)
            v = random.randint(1, 1000)
            print(f"1 {idx} {v}")
        else:
            # type 2
            l = random.randint(1, n)
            r = random.randint(1, n)
            if l > r:
                l, r = r, l
            print(f"2 {l} {r}")

if __name__ == '__main__':
    main()
