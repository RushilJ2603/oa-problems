#!/usr/bin/env python3
import random
import sys

seed = int(sys.argv[1]) if len(sys.argv) > 1 else None
size = int(sys.argv[2]) if len(sys.argv) > 2 else 8
random.seed(seed)

n = max(1, size)
# Mix value ranges so both tiny (many ties -> zero scores) and huge (64-bit overflow) inputs appear.
hi = random.choice([1, 5, 40, 1000, 10 ** 9])
a = [random.randint(0, hi) for _ in range(n)]
total_windows = n * (n + 1) // 2
k = random.randint(1, total_windows)   # anywhere from "just the best window" to "every window"

print(f"{n} {k}")
print(' '.join(map(str, a)))
