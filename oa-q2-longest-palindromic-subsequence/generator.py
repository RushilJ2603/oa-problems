#!/usr/bin/env python3
"""Random lowercase string for LPS. argv[1]=seed, argv[2]=size hint (length)."""
import random, sys, string
seed = int(sys.argv[1]) if len(sys.argv) > 1 else 0
size = int(sys.argv[2]) if len(sys.argv) > 2 else 12
random.seed(seed)
n = max(1, min(size, 1000))
alpha = random.choice([2, 3, 4, 26])   # small alphabets make longer palindromes -> better coverage
letters = string.ascii_lowercase[:alpha]
print("".join(random.choice(letters) for _ in range(random.randint(1, n))))
