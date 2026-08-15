import random
import sys

def main():
    if len(sys.argv) < 3:
        return
    random.seed(int(sys.argv[1]))
    size = int(sys.argv[2])
    
    if size >= 10:
        R = 500
        C = 500
    else:
        R = random.randint(1, 50 * size)
        C = random.randint(1, 50 * size)
        
    print(f"{R} {C}")
    for _ in range(R):
        row = [random.randint(-10000, 10000) for _ in range(C)]
        print(*(row))

if __name__ == '__main__':
    main()
