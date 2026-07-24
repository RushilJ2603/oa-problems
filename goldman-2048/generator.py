#!/usr/bin/env python3
import random, sys
seed=int(sys.argv[1]) if len(sys.argv)>1 else 0
size=int(sys.argv[2]) if len(sys.argv)>2 else 12
random.seed(seed)
vals=[0]+[2**k for k in range(1,12)]
grid=[[random.choice(vals) for _ in range(4)] for _ in range(4)]
for row in grid: print(" ".join(map(str,row)))
N=random.randint(1, max(1, min(size, 30)))
print(N)
for _ in range(N): print(random.choice(list("UDLRudlr")))
