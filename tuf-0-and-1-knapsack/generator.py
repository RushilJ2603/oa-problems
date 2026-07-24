import sys,random
seed=int(sys.argv[1]) if len(sys.argv)>1 else random.randrange(1<<30)
size=int(sys.argv[2]) if len(sys.argv)>2 else 6
random.seed(seed)
N=random.randint(1,max(1,size))
W=random.randint(1,30)
print(N,W)
print(' '.join(str(random.randint(1,20)) for _ in range(N)))
print(' '.join(str(random.randint(1,10)) for _ in range(N)))
