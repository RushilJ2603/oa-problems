#!/usr/bin/env python3
import random
import sys


def main():
    random.seed(int(sys.argv[1]))
    size = int(sys.argv[2])

    # Brute is O(n^3); gate cross-checks sizes up to 120 — keep N<=40 there.
    # At large size emit max-scale N=3000.
    if size <= 120:
        n = max(1, min(40, size if size >= 3 else random.randint(1, 3)))
        if size <= 3:
            n = random.randint(1, 3)
        elif size <= 12:
            n = random.randint(2, 12)
        elif size <= 25:
            n = random.randint(8, 25)
        elif size <= 60:
            n = random.randint(15, 35)
        else:
            n = random.randint(25, 40)
        coord_max = 100
    elif size < 400:
        n = random.randint(80, min(200, max(80, size)))
        coord_max = 1000
    else:
        n = 3000
        coord_max = 10000

    kind = random.randrange(6)
    pts = []

    if kind == 0:
        # random cloud
        for _ in range(n):
            pts.append((random.randint(0, coord_max), random.randint(0, coord_max)))
    elif kind == 1:
        # axis-aligned rectangle with interior + edge midpoints
        x0, y0 = 0, 0
        x1 = max(2, coord_max // 2)
        y1 = max(2, coord_max // 2)
        corners = [(x0, y0), (x0, y1), (x1, y0), (x1, y1)]
        for p in corners:
            pts.append(p)
        for _ in range(max(0, n - 4)):
            if random.random() < 0.4:
                # on boundary
                side = random.randrange(4)
                if side == 0:
                    pts.append((random.randint(x0, x1), y0))
                elif side == 1:
                    pts.append((random.randint(x0, x1), y1))
                elif side == 2:
                    pts.append((x0, random.randint(y0, y1)))
                else:
                    pts.append((x1, random.randint(y0, y1)))
            else:
                pts.append((random.randint(x0, x1), random.randint(y0, y1)))
    elif kind == 2:
        # all collinear (diagonal or horizontal)
        if random.random() < 0.5:
            y = random.randint(0, coord_max)
            xs = sorted(random.sample(range(coord_max + 1), min(n, coord_max + 1)))
            while len(xs) < n:
                xs.append(random.choice(xs))
            pts = [(x, y) for x in xs[:n]]
        else:
            for i in range(n):
                t = random.randint(0, coord_max)
                pts.append((t, t))
    elif kind == 3:
        # vertical line
        x = random.randint(0, coord_max)
        for _ in range(n):
            pts.append((x, random.randint(0, coord_max)))
    elif kind == 4:
        # many duplicates
        base = [(random.randint(0, coord_max), random.randint(0, coord_max))
                for _ in range(max(1, n // 5))]
        for _ in range(n):
            pts.append(random.choice(base))
    else:
        # convex polygon vertices + interior junk
        h = max(3, min(n, 20))
        cx = cy = coord_max // 2
        r = max(1, coord_max // 3)
        import math
        for i in range(h):
            ang = 2 * math.pi * i / h
            pts.append((int(cx + r * math.cos(ang)), int(cy + r * math.sin(ang))))
            pts[-1] = (max(0, min(coord_max, pts[-1][0])),
                       max(0, min(coord_max, pts[-1][1])))
        while len(pts) < n:
            pts.append((random.randint(0, coord_max), random.randint(0, coord_max)))

    # clamp & ensure length n
    pts = [(max(0, min(coord_max, x)), max(0, min(coord_max, y))) for x, y in pts]
    while len(pts) < n:
        pts.append((random.randint(0, coord_max), random.randint(0, coord_max)))
    pts = pts[:n]

    print(n)
    for x, y in pts:
        print(x, y)


if __name__ == "__main__":
    main()
