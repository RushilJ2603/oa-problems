import sys,random
seed=int(sys.argv[1]) if len(sys.argv)>1 else random.randrange(1<<30)
size=int(sys.argv[2]) if len(sys.argv)>2 else 12
random.seed(seed)
n=random.randint(1,max(1,size))
print(n)
vals=['0']+[str(random.randint(-50,50)) for _ in range(n-1)]
print(' '.join(vals))
