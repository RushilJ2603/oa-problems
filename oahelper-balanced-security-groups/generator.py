#!/usr/bin/env python3
import random
import sys


def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)

    # Map size hint to n; large size must hit max constraint.
    if size <= 3:
        n = random.randint(1, 5)
    elif size <= 10:
        n = random.randint(6, 20)
    elif size <= 25:
        n = random.randint(15, 40)
    elif size <= 60:
        n = random.randint(30, 80)
    elif size <= 120:
        n = random.randint(50, 120)
    elif size <= 150:
        n = random.randint(200, 800)
    elif size <= 400:
        n = random.randint(2000, 8000)
    else:
        n = 100000

    mode = seed % 8
    vals = []
    if mode == 0:
        # Few distinct grades, balanced frequencies
        k = random.randint(1, min(8, n))
        grades = list(range(1, k + 1))
        vals = [random.choice(grades) for _ in range(n)]
    elif mode == 1:
        # All identical
        vals = [random.randint(1, 10**5)] * n
    elif mode == 2:
        # All unique (or nearly)
        if n <= 10**5:
            vals = list(range(1, n + 1))
            random.shuffle(vals)
        else:
            vals = [random.randint(1, 10**5) for _ in range(n)]
    elif mode == 3:
        # One rare grade + one common (adversarial min-freq pattern)
        common = random.randint(1, 10**5)
        rare = common
        while rare == common:
            rare = random.randint(1, 10**5)
        rare_cnt = random.randint(1, max(1, min(5, n // 10)))
        vals = [rare] * rare_cnt + [common] * (n - rare_cnt)
        random.shuffle(vals)
    elif mode == 4:
        # Many grades with frequencies near a shared base size
        s = random.randint(2, max(2, min(20, n // 3)))
        vals = []
        g = 1
        while len(vals) < n:
            cnt = s + random.randint(0, 1)
            cnt = min(cnt, n - len(vals))
            vals.extend([g] * cnt)
            g += 1
            if g > 10**5:
                g = 1
    elif mode == 5:
        # Sorted ascending grades
        vals = sorted(random.randint(1, min(n, 10**5)) for _ in range(n))
    elif mode == 6:
        # Reverse-sorted
        vals = sorted((random.randint(1, min(n, 10**5)) for _ in range(n)), reverse=True)
    else:
        # Uniform random in full range
        vals = [random.randint(1, 10**5) for _ in range(n)]

    print(n)
    for x in vals:
        print(x)


if __name__ == "__main__":
    main()
