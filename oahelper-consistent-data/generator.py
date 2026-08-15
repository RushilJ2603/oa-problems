import sys
import random

def main():
    if len(sys.argv) < 3:
        return
        
    seed = int(sys.argv[1])
    try:
        size = int(sys.argv[2])
    except ValueError:
        size = 10
    
    random.seed(seed)
    
    if size >= 10:
        n = 1000000
    else:
        n = random.randint(1, 100 * size)
        
    # Append trailing spaces so the raw string length varies substantially with size
    # This guarantees max(len) > min(len) for the gate check.
    padding = " " * (size * 10)
    print(f"{n}{padding}")

if __name__ == '__main__':
    main()
