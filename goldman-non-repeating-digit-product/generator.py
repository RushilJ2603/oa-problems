#!/usr/bin/env python3
import random, sys
seed=int(sys.argv[1]) if len(sys.argv)>1 else 0
size=int(sys.argv[2]) if len(sys.argv)>2 else 12
random.seed(seed)
cap=max(10,min(size*50,99999))
x=random.randint(1,cap); y=random.randint(1,cap); z=min(99999, y+random.randint(0,cap))
print(x); print(y); print(z)
