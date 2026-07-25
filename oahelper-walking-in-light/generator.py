#!/usr/bin/env python3
"""Deterministic generator: python3 generator.py <seed> <size>"""
import random
import sys


def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    rng = random.Random(seed)

    # Map size -> N; large size hits constraint max N=1000
    if size <= 3:
        n = rng.randint(1, 3)
    elif size <= 10:
        n = rng.randint(4, 12)
    elif size <= 40:
        n = rng.randint(20, 60)
    elif size <= 150:
        n = rng.randint(100, 250)
    else:
        n = 1000  # max-scale

    mode = seed % 5
    lamps = []
    if mode == 0:
        # chain of touching disks along x-axis
        x = 0.0
        for _ in range(n):
            r = rng.uniform(1.0, 5.0) if n < 100 else 1.0
            lamps.append((x, 0.0, r))
            x += 2.0 * r
    elif mode == 1:
        # two distant clusters (often NO)
        for i in range(n):
            if i < n // 2:
                lamps.append((rng.uniform(-20, 20), rng.uniform(-20, 20), rng.uniform(1, 8)))
            else:
                lamps.append((rng.uniform(500, 600), rng.uniform(500, 600), rng.uniform(1, 8)))
    elif mode == 2:
        # random mid-range
        span = 50.0 if n < 100 else 200.0
        for _ in range(n):
            lamps.append((rng.uniform(-span, span), rng.uniform(-span, span),
                          rng.uniform(1.0, span / 5)))
    elif mode == 3:
        # nested / concentric-ish
        for i in range(n):
            lamps.append((0.0, 0.0, float(i + 1) * (10.0 if n < 50 else 0.05)))
    else:
        # large-coordinate stress
        for _ in range(n):
            lamps.append((rng.uniform(-1e8, 1e8), rng.uniform(-1e8, 1e8),
                          rng.uniform(1.0, 1e7)))

    # Place S and T inside some lamps (guarantee)
    si = rng.randrange(n)
    ti = rng.randrange(n)
    # point inside disk: center + small offset within radius
    def pt_in(i):
        xi, yi, ri = lamps[i]
        ang = rng.random() * 6.283185307179586
        rad = rng.random() * ri * 0.5
        return xi + rad * __import__("math").cos(ang), yi + rad * __import__("math").sin(ang)

    xs, ys = pt_in(si)
    xt, yt = pt_in(ti)

    print(n)
    for xi, yi, ri in lamps:
        print(f"{xi:.10g} {yi:.10g} {ri:.10g}")
    print(f"{xs:.10g} {ys:.10g} {xt:.10g} {yt:.10g}")


if __name__ == "__main__":
    main()
