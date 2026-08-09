"""One random valid input for The Toll You Only Pay Once.

usage: python3 generator.py [seed] [size]

Two things this generator deliberately does:

* it often builds a graph with a cheap SHARED TRUNK (a spanning tree of light edges plus heavier
  random chords), because that is the shape where paying for a road once beats paying twice — a
  uniformly random weighted graph almost never rewards the reuse and would let the naive
  "d(a,c) + d(c,b)" solution pass;
* it sometimes emits a graph split into two components, so the -1 answer shows up in random testing
  and not only in the curated edges.
"""
import random
import sys

seed = int(sys.argv[1]) if len(sys.argv) > 1 else None
size = int(sys.argv[2]) if len(sys.argv) > 2 else 8
rng = random.Random(seed)

n = max(1, min(100000, size))

# "split" is deliberately rare. It has to appear at all — -1 is a real answer and needs random
# coverage — but a suite where a quarter of the cases answer -1 both under-tests the interesting
# path and hands an untouched stub (which returns -1) a fat slice of partial credit in OA mode.
shape = rng.choice(["tree_plus_chords", "tree_plus_chords", "tree_plus_chords",
                    "sparse", "dense_small", "dense_small", "split"])
maxw = rng.choice([1, 3, 10, 1000, 10**9])

edges = []


def add(u, v, w):
    if u != v:
        edges.append((u, v, w))


if n == 1:
    shape = "sparse"

if shape == "split" and n >= 4:
    # Two components; a, b, c are scattered across them so -1 is likely but not guaranteed.
    cut = rng.randint(2, n - 1)
    for v in range(2, cut + 1):
        add(rng.randint(1, v - 1), v, rng.randint(1, maxw))
    for v in range(cut + 2, n + 1):
        add(rng.randint(cut + 1, v - 1), v, rng.randint(1, maxw))
elif shape == "tree_plus_chords":
    # A light spanning tree is the trunk the two legs will want to share.
    trunk_w = max(1, maxw // 100)
    for v in range(2, n + 1):
        parent = rng.randint(max(1, v - rng.choice([1, 2, 5, v])), v - 1)
        add(parent, v, rng.randint(1, trunk_w))
    extra = rng.randint(0, min(2 * n, 200000 - len(edges)))
    for _ in range(extra):
        add(rng.randint(1, n), rng.randint(1, n), rng.randint(1, maxw))
elif shape == "dense_small" and n <= 60:
    for u in range(1, n + 1):
        for v in range(u + 1, n + 1):
            if rng.random() < 0.5 and len(edges) < 200000:
                add(u, v, rng.randint(1, maxw))
else:
    # Purely random edges disconnect small graphs most of the time, so usually lay a spanning tree
    # first and let the random edges be chords on top of it.
    if rng.random() < 0.7:
        for v in range(2, n + 1):
            add(rng.randint(1, v - 1), v, rng.randint(1, maxw))
    m_target = rng.randint(0, min(2 * n, 200000 - len(edges)))
    for _ in range(m_target):
        add(rng.randint(1, n), rng.randint(1, n), rng.randint(1, maxw))

if len(edges) > 200000:
    edges = edges[:200000]

# Terminals: usually distinct, sometimes deliberately coincident to hit the degenerate readings.
if rng.random() < 0.15 and n >= 1:
    a = b = c = rng.randint(1, n)
elif rng.random() < 0.2 and n >= 2:
    a = rng.randint(1, n)
    c = a
    b = rng.randint(1, n)
else:
    a = rng.randint(1, n)
    b = rng.randint(1, n)
    c = rng.randint(1, n)

out = ["%d %d" % (n, len(edges))]
out.extend("%d %d %d" % e for e in edges)
out.append("%d %d %d" % (a, b, c))
sys.stdout.write("\n".join(out) + "\n")
