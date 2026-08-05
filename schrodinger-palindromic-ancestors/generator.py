"""One random valid input for Palindromic Paths to the Root.

usage: python3 generator.py [seed] [size]

Two knobs matter for how hard the instance is:
  * the SHAPE — a path makes every query walk the whole tree, a star makes every walk length 2;
  * the ALPHABET — over 26 random letters almost no path is a palindrome, so small alphabets are
    what actually exercise the counting.
Edge endpoints are emitted in a random order, because the pairs are unordered by definition.
"""
import random
import sys

seed = int(sys.argv[1]) if len(sys.argv) > 1 else None
size = int(sys.argv[2]) if len(sys.argv) > 2 else 10
rng = random.Random(seed)

n = max(1, min(200000, size))
shape = rng.choice(["random", "random", "path", "star", "caterpillar"])
edges = []
for v in range(1, n):
    if shape == "path":
        p = v - 1
    elif shape == "star":
        p = 0
    elif shape == "caterpillar":
        p = v - 1 if v % 2 else max(0, v - 2)
    else:
        p = rng.randrange(v)
    edges.append((p, v) if rng.random() < 0.5 else (v, p))
rng.shuffle(edges)

k = rng.choice([1, 2, 2, 3, 5, 26])
alphabet = "abcdefghijklmnopqrstuvwxyz"[:k]
letters = "".join(rng.choice(alphabet) for _ in range(n))
q = max(1, min(200000, rng.randint(1, max(1, n))))
queries = [rng.randrange(n) for _ in range(q)]

out = [str(n),
       " ".join(str(a) for a, _ in edges),
       " ".join(str(b) for _, b in edges),
       letters,
       str(q)]
out += [str(x) for x in queries]
print("\n".join(out))
