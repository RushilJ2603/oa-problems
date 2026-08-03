#!/usr/bin/env python3
import random
import sys

def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)

    MAXN = 80
    if size <= 3:
        n = random.randint(0, 2)
        m = random.randint(0, 2)
        k = random.randint(0, 2)
    elif size <= 10:
        n = random.randint(0, min(4, size))
        m = random.randint(0, min(4, size))
        k = random.randint(0, min(4, size))
    elif size <= 40:
        bound = min(12, size)
        n = random.randint(1, bound)
        m = random.randint(1, bound)
        k = random.randint(1, bound)
    elif size <= 150:
        bound = min(25, MAXN)
        n = random.randint(5, bound)
        m = random.randint(5, bound)
        k = random.randint(5, bound)
    elif size <= 400:
        bound = min(50, MAXN)
        n = random.randint(20, bound)
        m = random.randint(20, bound)
        k = random.randint(20, bound)
    else:
        # MAX-SCALE
        n = m = k = MAXN

    def gen_seq(length):
        mode = (seed + length) % 4
        seq = []
        for i in range(length):
            if mode == 0:
                seq.append(random.randint(-100, 100))
            elif mode == 1:
                seq.append(i * 10 + random.randint(0, 5))
            elif mode == 2:
                seq.append(random.choice([0, 1, -1, 100, -100, 10**9, -10**9]))
            else:
                seq.append(random.randint(-10**9, 10**9))
        return seq

    X, Y, Z = gen_seq(n), gen_seq(m), gen_seq(k)
    print(n, m, k)
    print(" ".join(map(str, X)) if X else "")
    print(" ".join(map(str, Y)) if Y else "")
    print(" ".join(map(str, Z)) if Z else "")

if __name__ == "__main__":
    main()
