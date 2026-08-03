#!/usr/bin/env python3
import random
import sys

def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)

    # Map size -> n; large size hits constraint max 1e5
    if size <= 3:
        n = random.randint(1, 3)
    elif size <= 10:
        n = random.randint(2, size)
    elif size <= 40:
        n = random.randint(10, size)
    elif size <= 150:
        n = random.randint(40, min(size, 200))
    elif size <= 400:
        n = random.randint(200, min(size, 2000))
    else:
        n = 10**5  # MAX-SCALE

    print(n)
    # Mix of value regimes so length-2/3 constraints matter
    mode = seed % 5
    for i in range(n):
        if mode == 0:
            # all negative small
            print(random.randint(-5, -1))
        elif mode == 1:
            # alternating large magnitude
            print((-1) ** i * random.randint(10**8, 10**9))
        elif mode == 2:
            # mostly zeros / tiny
            print(random.choice([0, 0, 0, 1, -1, 2, -2]))
        elif mode == 3:
            # random full range
            print(random.randint(-10**9, 10**9))
        else:
            # clustered positives and deep negatives
            if random.random() < 0.3:
                print(random.randint(-10**9, -10**8))
            else:
                print(random.randint(0, 10**9))

if __name__ == "__main__":
    main()
