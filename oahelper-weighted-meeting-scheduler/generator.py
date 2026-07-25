#!/usr/bin/env python3
import random
import sys


def main():
    random.seed(int(sys.argv[1]))
    size = int(sys.argv[2])

    if size <= 3:
        n = random.randint(1, 4)
    elif size <= 10:
        n = random.randint(3, 12)
    elif size <= 40:
        n = random.randint(10, 40)
    elif size <= 120:
        n = random.randint(20, 80)  # keep O(n^2) brute feasible
    elif size <= 400:
        n = random.randint(200, 2000)
    else:
        n = 100000  # MAX-SCALE

    mode = random.randrange(5)
    meetings = []
    if mode == 0:
        # chain of back-to-back
        t = 0
        for i in range(n):
            s = t
            e = t + random.randint(1, 10)
            p = random.randint(1, 10**6)
            meetings.append((s, e, p))
            t = e
    elif mode == 1:
        # all overlap same window
        s0 = random.randint(0, 10**6)
        e0 = s0 + random.randint(1, 10**6)
        for _ in range(n):
            meetings.append((s0, e0, random.randint(1, 10**6)))
    elif mode == 2:
        # nested / overlapping random
        for _ in range(n):
            s = random.randint(0, 10**9 - 1)
            e = s + random.randint(1, min(10**6, 10**9 - s))
            p = random.randint(1, 10**6)
            meetings.append((s, e, p))
    elif mode == 3:
        # prefer many small vs one large
        for i in range(n - 1):
            s = i * 10
            meetings.append((s, s + 5, random.randint(1, 100)))
        meetings.append((0, n * 10, random.randint(1, 10**6)))
    else:
        for _ in range(n):
            s = random.randint(0, 10**9 - 1)
            e = s + random.randint(1, min(10**9, 10**9 - s))
            p = random.randint(1, 10**6)
            meetings.append((s, e, p))

    print(n)
    for s, e, p in meetings:
        print(s, e, p)


if __name__ == "__main__":
    main()
