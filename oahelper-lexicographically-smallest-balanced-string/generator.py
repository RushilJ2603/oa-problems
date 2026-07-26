#!/usr/bin/env python3
import random
import sys
import string

def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)

    if size >= 200:
        n = 10**5
    else:
        n = max(1, min(size, 40))

    # choose k dividing n often, sometimes not
    divisors = [d for d in range(1, n + 1) if n % d == 0]
    if random.random() < 0.85 and divisors:
        k = random.choice(divisors)
    else:
        k = random.randint(1, n)

    alphabet = string.ascii_lowercase[: random.randint(1, 26)]
    s = "".join(random.choice(alphabet) for _ in range(n))
    print(n, k)
    print(s)

if __name__ == "__main__":
    main()
