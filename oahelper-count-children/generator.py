import sys
import random

def main():
    if len(sys.argv) < 3:
        print("Usage: python generator.py <seed> <size>")
        sys.exit(1)
    
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)
    
    max_N = 10**18
    max_k = min(2000, max(1, size * 200))
    
    # Needs to be non-degenerate. At large sizes, output max scale but vary them!
    if size >= 10:
        k = random.randint(1900, 2000)
        n = max_N - random.randint(0, 1000)
        i = n - k + 1
    else:
        k = random.randint(1, max_k)
        n = random.randint(k, max_N)
        i = n - k + 1
    
    print(n)
    print(i)

if __name__ == "__main__":
    main()
