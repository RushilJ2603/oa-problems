#!/usr/bin/env python3
"""Deterministic generator: python3 generator.py <seed> <size>"""
import random
import sys


def one_case(n, m, t, k):
    # Generate n non-overlapping breaks inside [0, k]
    # Leave gaps so r_i < l_{i+1}
    breaks = []
    # Partition day into alternating break/gap pieces
    if k < 2 or n == 0:
        return []
    # Create n intervals with positive length
    # Use random points
    pts = sorted(random.sample(range(0, k + 1), min(2 * n, k + 1)))
    # Ensure we can form n intervals
    i = 0
    while len(breaks) < n and i + 1 < len(pts):
        l, r = pts[i], pts[i + 1]
        if r > l:
            breaks.append((l, r))
        i += 2
    # If not enough, fill greedily
    pos = 0
    while len(breaks) < n and pos < k:
        length = max(1, (k - pos) // (n - len(breaks) + 1))
        length = min(length, k - pos)
        if length <= 0:
            break
        # leave a gap of 0 or 1 if possible for next
        r = pos + length
        if breaks and pos <= breaks[-1][1]:
            pos = breaks[-1][1] + 1
            continue
        if r > pos:
            breaks.append((pos, r))
        pos = r + 1
    # Trim/pad
    breaks = breaks[:n]
    if not breaks:
        # fallback single break
        breaks = [(0, max(1, k // 2))]
    # Ensure strictly increasing with gaps: r_i < l_{i+1}
    fixed = [breaks[0]]
    for l, r in breaks[1:]:
        prev_r = fixed[-1][1]
        if l <= prev_r:
            l = prev_r + 1
        if l >= k:
            break
        r = max(l + 1, min(r, k))
        if r > l:
            fixed.append((l, r))
    return fixed


def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)

    if size >= 2000:
        # MAX-SCALE near constraint bounds (n=1e5, m/t/k up to 1e9)
        T = 1
        t = 1
        k = 10**9
        m = 10**9
        gap = 1
        blen = 2
        n = min(100000, k // (blen + gap))
        breaks = []
        pos = 0
        for i in range(n):
            breaks.append((pos, pos + blen))
            pos += blen + gap
        cases = [(n, m, t, k, breaks)]
    elif size >= 800:
        T = 1
        n = 20000
        t = 1
        k = 10**9
        m = 10**7
        gap = 1
        blen = 2
        breaks = []
        pos = 0
        for i in range(n):
            breaks.append((pos, pos + blen))
            pos += blen + gap
        cases = [(n, m, t, k, breaks)]
    elif size >= 200:
        T = 3
        cases = []
        for _ in range(T):
            n = random.randint(1, min(500, size))
            t = random.randint(1, 20)
            k = random.randint(t * n + n + 10, t * n + n + 5000)
            m = random.randint(1, 10**6)
            breaks = one_case(n, m, t, k)
            n = len(breaks)
            cases.append((n, m, t, k, breaks))
    else:
        T = 1
        n = max(1, min(size, 30))
        t = random.randint(1, 10)
        k = random.randint(max(t + 1, 5), max(t + 1, 5) + n * (t + 3) + 50)
        m = random.randint(1, max(1, size * 3))
        breaks = one_case(n, m, t, k)
        n = len(breaks)
        cases = [(n, m, t, k, breaks)]

    lines = [str(len(cases))]
    for n, m, t, k, breaks in cases:
        lines.append(f"{n} {m} {t} {k}")
        for l, r in breaks:
            lines.append(f"{l} {r}")
    sys.stdout.write("\n".join(lines) + "\n")


if __name__ == "__main__":
    main()
