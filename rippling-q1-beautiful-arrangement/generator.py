#!/usr/bin/env python3
"""Random n for Beautiful Arrangement. argv[1]=seed, argv[2]=size hint (caps n)."""
import random, sys
seed = int(sys.argv[1]) if len(sys.argv) > 1 else 0
size = int(sys.argv[2]) if len(sys.argv) > 2 else 12
random.seed(seed)
n = random.randint(1, max(1, min(size, 15)))
print(n)
