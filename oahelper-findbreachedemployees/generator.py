#!/usr/bin/env python3
import sys, random

def main():
    seed = int(sys.argv[1]); size = int(sys.argv[2])
    random.seed(seed)
    if size <= 3:
        n = random.randint(1, 3); m = random.randint(1, 4)
    elif size <= 10:
        n = random.randint(2, 8); m = random.randint(2, 10)
    elif size <= 40:
        n = random.randint(5, 30); m = random.randint(5, 40)
    elif size <= 150:
        n = random.randint(40, 120); m = random.randint(40, 150)
    else:
        n = m = 2500  # max-scale
    k = random.randint(1, m)
    units = random.sample(range(1, m + 1), k)
    print(k)
    for u in units:
        print(u)
    print(n)
    for _ in range(n):
        # bias toward sparse access
        row = ['1' if random.random() < 0.25 else '0' for _ in range(m)]
        if all(c == '0' for c in row):
            row[random.randrange(m)] = '1'
        print(''.join(row))

if __name__ == "__main__":
    main()
