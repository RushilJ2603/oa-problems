import sys
import random

def main():
    if len(sys.argv) < 3:
        return
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    
    random.seed(seed)
    
    n = size
    if n > 5000:
        n = 5000
    if n < 1:
        n = 1
        
    if size >= 5000 and seed % 2 == 0:
        start = random.randint(-1000, 1000)
        diff = random.randint(-2, 2)
        arr = []
        val = start
        for _ in range(n):
            arr.append(max(-1000, min(1000, val)))
            val += diff
        print("[" + ", ".join(map(str, arr)) + "]")
        return
        
    arr = []
    i = 0
    while i < n:
        length = random.randint(1, 10)
        if length > n - i:
            length = n - i
        start = random.randint(-1000, 1000)
        diff = random.randint(-100, 100)
        val = start
        for _ in range(length):
            if val < -1000: val = -1000
            if val > 1000: val = 1000
            arr.append(val)
            val += diff
        i += length
        
    print("[" + ", ".join(map(str, arr)) + "]")

if __name__ == '__main__':
    main()
