#!/usr/bin/env python3
import random
import string
import sys

def main():
    seed = int(sys.argv[1])
    size = int(sys.argv[2])
    random.seed(seed)
    # size drives length; large size hits constraint bound 500
    n = max(1, min(500, size))
    m = max(1, min(500, size if size < 100 else random.randint(max(1, n // 2), n)))
    if size >= 400:
        n = m = 500
    alphabet = string.ascii_lowercase
    if size >= 50:
        # sometimes use larger alphabets / digits for variety
        alphabet = string.ascii_letters + string.digits
    mode = seed % 5
    if mode == 0:
        # identical / near-identical
        w1 = "".join(random.choice(alphabet) for _ in range(n))
        w2 = w1 if seed % 2 == 0 else (w1[: m] if m <= n else w1 + "".join(random.choice(alphabet) for _ in range(m - n)))
        if len(w2) != m:
            w2 = "".join(random.choice(alphabet) for _ in range(m))
    elif mode == 1:
        # completely different alphabet subsets
        w1 = "".join(random.choice(alphabet[:13]) for _ in range(n))
        w2 = "".join(random.choice(alphabet[13:]) for _ in range(m))
    elif mode == 2:
        # one much shorter
        w1 = "".join(random.choice(alphabet) for _ in range(n))
        short = max(1, n // 10)
        w2 = "".join(random.choice(alphabet) for _ in range(short))
    elif mode == 3:
        # sorted / reverse-ish patterns
        w1 = "".join(sorted(random.choice(alphabet) for _ in range(n)))
        w2 = "".join(reversed(sorted(random.choice(alphabet) for _ in range(m))))
    else:
        w1 = "".join(random.choice(alphabet) for _ in range(n))
        w2 = "".join(random.choice(alphabet) for _ in range(m))
    print(w1, w2)

if __name__ == "__main__":
    main()
