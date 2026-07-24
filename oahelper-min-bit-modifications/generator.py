import sys,random
seed=int(sys.argv[1]) if len(sys.argv)>1 else random.randrange(1<<30)
size=int(sys.argv[2]) if len(sys.argv)>2 else 10
random.seed(seed)
n=random.randint(1,max(1,size))
print(n)
hi=random.choice([3,255,10**18])
print(' '.join(str(random.randint(0,hi)) for _ in range(n)))
