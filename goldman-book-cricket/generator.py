#!/usr/bin/env python3
import random, sys
seed=int(sys.argv[1]) if len(sys.argv)>1 else 0
size=int(sys.argv[2]) if len(sys.argv)>2 else 12
random.seed(seed)
# keep N bounded so the count stays within 64-bit
print(random.randint(0, max(1, min(size*8, 120))))
