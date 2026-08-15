import sys
import random

def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)
    
    n = max(1, min(1000, size * 10))
    if size > 90:
        n = 1000
        
    initial_energy = random.choice([0, 1, random.randint(2, n), random.randint(1000, 10**14)])
    if size > 90:
        initial_energy = random.choice([0, 10**14])
        
    energy = [random.randint(0, 1000) for _ in range(n)]
    coins = [random.randint(0, 1000) for _ in range(n)]
    
    print(initial_energy)
    print(n)
    for x in energy: print(x)
    print(n)
    for x in coins: print(x)

if __name__ == '__main__':
    main()
