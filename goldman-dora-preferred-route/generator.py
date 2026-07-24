#!/usr/bin/env python3
"""Random small graph for Dora. Kept small so backtracking stays fast. argv[1]=seed, argv[2]=size."""
import random, sys
seed=int(sys.argv[1]) if len(sys.argv)>1 else 0
size=int(sys.argv[2]) if len(sys.argv)>2 else 12
random.seed(seed)
n=random.randint(2, max(2, min(size, 10)))
g=[[0]*n for _ in range(n)]
p=random.choice([0.3,0.5,0.7])
for i in range(n):
    for j in range(i+1,n):
        if random.random()<p: g[i][j]=g[j][i]=1
S=random.randint(0,n-1); D=random.randint(0,n-1)
print(n)
for row in g: print(" ".join(map(str,row)))
print(S,D)
