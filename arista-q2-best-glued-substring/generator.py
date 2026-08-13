"""One random valid input for Best Glued Substring.

usage: python3 generator.py [seed] [size]

Three independent random strings is the trap. Over a 26-letter alphabet almost no overlap happens by
chance, so every substring scores 0 or 1, the answer is just the smallest letter present, and a
suite built that way is passed by `return the minimum character`.

So most instances are PLANTED: a piece of s is chosen, p is built to end with that piece's opening
characters and q to start with its closing characters, which makes a specific substring win by a
real margin. The alphabet is also squeezed (2-4 letters) on many instances, because accidental
overlaps are where the length caps and the tie-break actually get exercised:

  planted     - a designed winner, with p/q overlapping it by a controlled amount
  tiny_alpha  - 1-2 letters: overlaps everywhere, huge ties, the lexicographic rule decides
  all_same    - every character identical; every score is capped by the piece's length
  engulf      - p ends with ALL of s and q starts with ALL of s, so caps bind everywhere
  disjoint    - deliberately no overlap: the answer must be the smallest single character
"""
import random
import string
import sys

seed = int(sys.argv[1]) if len(sys.argv) > 1 else None
size = int(sys.argv[2]) if len(sys.argv) > 2 else 8
rng = random.Random(seed)

n = max(1, min(2000, size))
shape = rng.choice(["planted", "planted", "planted", "tiny_alpha", "all_same", "engulf",
                    "disjoint", "random"])

if shape == "all_same":
    ch = rng.choice("ab")
    s = ch * n
    p = ch * rng.randint(1, min(2000, n + 5))
    q = ch * rng.randint(1, min(2000, n + 5))
elif shape == "tiny_alpha":
    alpha = "ab" if rng.random() < 0.7 else "a"
    s = "".join(rng.choice(alpha) for _ in range(n))
    p = "".join(rng.choice(alpha) for _ in range(rng.randint(1, min(2000, max(1, n)))))
    q = "".join(rng.choice(alpha) for _ in range(rng.randint(1, min(2000, max(1, n)))))
elif shape == "engulf":
    alpha = "abc"
    s = "".join(rng.choice(alpha) for _ in range(n))
    p = "".join(rng.choice(alpha) for _ in range(rng.randint(0, 5))) + s
    q = s + "".join(rng.choice(alpha) for _ in range(rng.randint(0, 5)))
    p, q = p[-2000:], q[:2000]
elif shape == "disjoint":
    # s over one alphabet, p and q over another: every overlap is 0 by construction.
    s = "".join(rng.choice("abc") for _ in range(n))
    p = "".join(rng.choice("xyz") for _ in range(rng.randint(1, min(2000, max(1, n)))))
    q = "".join(rng.choice("xyz") for _ in range(rng.randint(1, min(2000, max(1, n)))))
elif shape == "random":
    k = rng.choice([2, 3, 5, 26])
    alpha = string.ascii_lowercase[:k]
    s = "".join(rng.choice(alpha) for _ in range(n))
    p = "".join(rng.choice(alpha) for _ in range(rng.randint(1, min(2000, max(1, n)))))
    q = "".join(rng.choice(alpha) for _ in range(rng.randint(1, min(2000, max(1, n)))))
else:   # planted
    k = rng.choice([2, 3, 4, 6, 26])
    alpha = string.ascii_lowercase[:k]
    s = "".join(rng.choice(alpha) for _ in range(n))
    i = rng.randrange(n)
    j = rng.randint(i + 1, n)
    piece = s[i:j]
    a = rng.randint(1, len(piece))          # how much of the piece's head p ends with
    b = rng.randint(1, len(piece))          # how much of the piece's tail q starts with
    pad_p = "".join(rng.choice(alpha) for _ in range(rng.randint(0, 6)))
    pad_q = "".join(rng.choice(alpha) for _ in range(rng.randint(0, 6)))
    p = (pad_p + piece[:a])[-2000:]
    q = (piece[len(piece) - b:] + pad_q)[:2000]

if not p:
    p = "a"
if not q:
    q = "a"

print(s)
print(p)
print(q)
